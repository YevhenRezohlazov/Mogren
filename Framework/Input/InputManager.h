#pragma once

#include <Mogren/Framework/Math/Vector2D.h>

#include "InputBox.h"
#include "TouchData.h"

#include <memory>
#include <mutex>
#include <vector>

namespace Graphics
{
    class RenderTarget;
    class Camera;
}

namespace Input
{
    class InputManager
    {
    private:
        struct TouchQueueElement
        {
            std::shared_ptr<Graphics::RenderTarget> mRenderTarget;
            Common::TouchAction mAction;
            Math::Point2DI mPosition;
            int mPointerId;
            double mTouchTime;
        };

        static std::mutex mTouchQueueMutex;
        static std::vector<TouchQueueElement> mTouchQueue;
        static InputBox* mFocusedInputBox;
        static Graphics::Camera* mFocusedCamera;
        static Graphics::RenderTarget* mFocusedRenderTarget;
        static uint32_t mFocusedTouchCount;

    private:
        // disallow creating instance
        InputManager();

    public:
        ///
        /// Adds touch event with given parameters to the touch queue.
        /// Can be called from any thread
        /// \param renderTarget Render target to be touched
        /// \param action Touch action (Up/Down/Move)
        /// \param position The touch position
        /// \param pointerId Id of the pointer that touches the render target
        /// \param touchTime Absolute time of the touch event
        ///
        static void touchRenderTarget(
            std::shared_ptr<Graphics::RenderTarget> renderTarget,
            Common::TouchAction action,
            const Math::Point2DI &position,
            int pointerId,
            double touchTime);

        ///
        /// Dispatches all the touch events from touch queue to the appropriate input boxes
        ///
        static void dispatchTouches();

        ///
        /// Clears event queue.
        ///
        static void clearQueue();

        ///
        /// Clears current pointer capture.
        ///
        static void clearCapture();

    private:
        static bool dispatchTouch(
            Graphics::RenderTarget &renderTarget,
            Graphics::Camera& camera,
            Common::SceneItem& sceneItem,
            const TouchQueueElement &touchElem,
            const Math::Matrix4x4 &viewProjectionMatrix,
            const Math::Point3DF &nearScreenPosition,
            const Math::Point3DF &farScreenPosition);

        static void initTouchData(
            TouchData &data,
            Common::SceneItem& sceneItem,
            const TouchQueueElement &touchElem,
            const Math::Matrix4x4 &viewProjectionMatrix,
            const Math::Point3DF &nearScreenPosition,
            const Math::Point3DF &farScreenPosition);
    };
}

