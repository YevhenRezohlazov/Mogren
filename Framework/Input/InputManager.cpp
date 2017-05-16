#include "InputManager.h"
#include <Mogren/Framework/Graphics/RenderTarget.h>
#include <Mogren/Framework/Graphics/Camera.h>

namespace Input
{
    using namespace Common;

    std::mutex InputManager::mTouchQueueMutex;
    std::vector<InputManager::TouchQueueElement> InputManager::mTouchQueue;

    void InputManager::touchRenderTarget(
        std::shared_ptr<Graphics::RenderTarget> renderTarget,
        TouchAction action,
        const Math::Point2DI &position,
        int pointerId, double touchTime)
    {
        std::lock_guard<std::mutex> lock(mTouchQueueMutex);

        TouchQueueElement elem;
        elem.mRenderTarget = renderTarget;
        elem.mAction = action;
        elem.mPosition = position;
        elem.mPointerId = pointerId;
        elem.mTouchTime = touchTime;
        mTouchQueue.push_back(elem);
    }

    void InputManager::dispatchTouches()
    {
        std::lock_guard<std::mutex> lock(mTouchQueueMutex);

        for (auto& elem : mTouchQueue)
        {
            // ignore Move and Up events if no input box is focused
            if (mFocusedTouchCount == 0 && elem.mAction != TouchAction::Down) continue;

            auto& cameras = elem.mRenderTarget->getAttachedCameras();

            if (mFocusedRenderTarget && mFocusedRenderTarget != elem.mRenderTarget.get()) continue;

            for (Graphics::Camera & camera : cameras)
            {
                if (mFocusedCamera && mFocusedCamera != &camera) continue;
                
                const Math::Point3DF nearScreenPosition(
                    (elem.mPosition.x - camera.getViewport().mLeft) / float(camera.getViewport().mWidth) * 2.0f - 1.0f,
                    -(elem.mPosition.y - camera.getViewport().mTop) / float(camera.getViewport().mHeight) * 2.0f + 1.0f,
                    1.0f);

                const Math::Point3DF farScreenPosition(nearScreenPosition.x, nearScreenPosition.y, -1.0f);

                // check if touch is inside the viewport
                if (elem.mAction == TouchAction::Down &&
                    (nearScreenPosition.x < -1.0f || nearScreenPosition.x > 1.0f || nearScreenPosition.y < -1.0f || nearScreenPosition.y > 1.0f))
                {
                    continue;
                }

                Common::SceneItem *rootItem = &camera;
                while (rootItem->hasParent())
                {
                    rootItem = &rootItem->getParent();
                }

                auto viewProjMatrix = camera.getViewProjectionMatrix();
                if (dispatchTouch(*elem.mRenderTarget, camera, *rootItem, elem, viewProjMatrix, nearScreenPosition, farScreenPosition))
                {
                    // stop dispatching
                    break;
                }
            }
        }

        mTouchQueue.clear();
    }

    bool InputManager::dispatchTouch(
        Graphics::RenderTarget &renderTarget,
        Graphics::Camera &camera,
        Common::SceneItem &sceneItem,
        const TouchQueueElement &touchElem,
        const Math::Matrix4x4 &viewProjectionMatrix,
        const Math::Point3DF &nearScreenPosition,
        const Math::Point3DF &farScreenPosition)
    {
        InputBox* inputBox;
        bool dispatchToChildren;

        if (mFocusedInputBox)
        {
            if (mFocusedInputBox == &sceneItem)
            {
                inputBox = mFocusedInputBox;
                dispatchToChildren = false;
            }
            else
            {
                inputBox = nullptr;
                dispatchToChildren = true;
            }
        }
        else
        {
            inputBox = dynamic_cast<InputBox*>(&sceneItem);
            dispatchToChildren = true;
        }

        TouchData touchData;
        bool touchIsInsideBox = false;

        if (inputBox)
        {
            switch (inputBox->getState())
            {
            case InputBoxState::Enabled:
                if (inputBox->isProcessingTouchPreviews())
                {
                    initTouchData(touchData, sceneItem, touchElem, viewProjectionMatrix, nearScreenPosition, farScreenPosition);
                    touchIsInsideBox = inputBox == mFocusedInputBox || inputBox->checkTouch(touchData.getTouchRayStartPoint(), touchData.getTouchRayEndPoint());

                    // if the event is handled
                    if (touchIsInsideBox && inputBox->processTouchPreview(touchData))
                    {
                        // stop dispatching
                        return true;
                    }
                }
                break;
            default: break;
            }
        }

        if (dispatchToChildren)
        {
            for (auto child : sceneItem.getChildren())
            {
                // if the event is handled
                if (dispatchTouch(renderTarget, camera, *child, touchElem, viewProjectionMatrix, nearScreenPosition, farScreenPosition))
                {
                    // stop dispatching
                    return true;
                }
            }
        }

        if (inputBox)
        {
            switch (inputBox->getState())
            {
            case InputBoxState::Enabled:
                if (!touchData.isValid())
                {
                    initTouchData(touchData, sceneItem, touchElem, viewProjectionMatrix, nearScreenPosition, farScreenPosition);
                    touchIsInsideBox = inputBox == mFocusedInputBox || inputBox->checkTouch(touchData.getTouchRayStartPoint(), touchData.getTouchRayEndPoint());
                }

                // if the event is handled
                if (touchIsInsideBox && inputBox->processTouch(touchData))
                {
                    if (touchData.getAction() == TouchAction::Down)
                    {
                        if (!mFocusedInputBox)
                        {
                            mFocusedRenderTarget = &renderTarget;
                            mFocusedCamera = &camera;
                            mFocusedInputBox = inputBox;
                            mFocusedTouchCount = 0;
                        }

                        mFocusedTouchCount += 1;
                    }
                    else if (touchData.getAction() == TouchAction::Up && mFocusedInputBox)
                    {
                        mFocusedTouchCount -= 1;

                        if (mFocusedTouchCount == 0)
                        {
                            mFocusedRenderTarget = nullptr;
                            mFocusedCamera = nullptr;
                            mFocusedInputBox = nullptr;
                        }
                    }

                    // stop dispatching
                    return true;
                }
                break;
            case InputBoxState::Disabled:
                if (!touchData.isValid())
                {
                    initTouchData(touchData, sceneItem, touchElem, viewProjectionMatrix, nearScreenPosition, farScreenPosition);
                    touchIsInsideBox = inputBox == mFocusedInputBox || inputBox->checkTouch(touchData.getTouchRayStartPoint(), touchData.getTouchRayEndPoint());
                }

                if (touchIsInsideBox)
                {
                    // stop dispatching
                    return true;
                }
                break;
            default: break;
            }
        }

        return false;
    }

    void InputManager::initTouchData(
        TouchData &data,
        Common::SceneItem &sceneItem,
        const TouchQueueElement &touchElem,
        const Math::Matrix4x4 &viewProjectionMatrix,
        const Math::Point3DF &nearScreenPosition,
        const Math::Point3DF &farScreenPosition)
    {
        auto invTransform = (sceneItem.getGlobalTransformationMatrix() * viewProjectionMatrix).getInverted();

        Math::Point3DF touchRayStartPoint = invTransform.transformVector(nearScreenPosition);
        Math::Point3DF touchRayEndPoint = invTransform.transformVector(farScreenPosition);

        data = TouchData(touchElem.mAction, touchRayStartPoint, touchRayEndPoint, touchElem.mPointerId, touchElem.mTouchTime);
    }

    void InputManager::clearQueue()
    {
        std::lock_guard<std::mutex> lock(mTouchQueueMutex);
        mTouchQueue.clear();
    }

    void InputManager::clearCapture()
    {
        mFocusedInputBox = nullptr;
        mFocusedCamera = nullptr;
        mFocusedRenderTarget = nullptr;
        mFocusedTouchCount = 0;
    }

    Graphics::RenderTarget* InputManager::mFocusedRenderTarget;
    Graphics::Camera* InputManager::mFocusedCamera;
    uint32_t InputManager::mFocusedTouchCount(0);
    InputBox* InputManager::mFocusedInputBox;
}