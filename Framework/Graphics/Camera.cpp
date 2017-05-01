#include "Camera.h"
#include "RenderTarget.h"
#include "CameraProjection.h"
#include "NativeInterface/NativeGraphicsInterface.h"
#include "NativeInterface/NativeRenderer.h"
#include <Mogren/Framework/Common/ImplementationProvider.h>
#include "VisualSceneItem.h"
#include <algorithm>

namespace Graphics
{
    std::vector<Camera*> Camera::sCameras;

    Camera::Camera()
        : mProjection(std::make_unique<CameraProjection>())
        , mShouldClearTarget(true), mViewMatrix(Math::Matrix4x4::Identity), mViewProjectionMatrix(Math::Matrix4x4::Identity)
        , mIsViewProjectionMatrixDirty(false), mLastViewMatrixVersion(0), mLastProjectionMatrixVersion(0)
    {
        sCameras.push_back(this);
        setRenderPriority(0.0f);
    }

    const CameraProjection & Camera::getProjection() const
    {
        return *mProjection;
    }

    bool Camera::shouldClearTarget() const
    {
        return mShouldClearTarget;
    }

    const Color& Camera::getClearColor() const
    {
        return mClearColor;
    }

    void Camera::setClearColor(const Color& color)
    {
        mClearColor = color;
    }

    const Viewport& Camera::getViewport() const
    {
        return mViewport;
    }

    void Camera::setViewport(const Viewport& viewport)
    {
        if (mViewport != viewport)
        {
            mViewport = viewport;

            if (mProjection)
            {
                mProjection->updateViewport(mViewport);
            }
        }
    }

    std::shared_ptr<const RenderTarget> Camera::getRenderTarget() const
    {
        return mRenderTarget;
    }

    std::shared_ptr<RenderTarget> Camera::getRenderTarget()
    {
        return mRenderTarget;
    }

    void Camera::setRenderTarget(std::shared_ptr<RenderTarget> renderTarget)
    {
        if (mRenderTarget)
        {
            mRenderTarget->detachCamera(*this);
        }

        mRenderTarget = renderTarget;

        if (mRenderTarget)
        {
            mRenderTarget->attachCamera(*this);
            setViewport(Viewport(0, 0, mRenderTarget->getSize().width, mRenderTarget->getSize().height));
        }
    }

    void Camera::setRenderPriority(float renderPriority)
    {
        mRenderPriority = renderPriority;
        std::sort(
            sCameras.begin(),
            sCameras.end(),
            [](const Camera* cam1, const Camera* cam2) { return cam1->getRenderPriority() > cam2->getRenderPriority(); });
    }

    float Camera::getRenderPriority() const
    {
        return mRenderPriority;
    }

    bool Camera::updateGlobalTransformationMatrix()
    {
        bool res = Common::SceneItem::updateGlobalTransformationMatrix();

        if (res)
        {
            mViewMatrix = getGlobalTransformationMatrix().convertToCameraViewMatrix();
        }

        return res;
    }

    void Camera::render()
    {
        if (getRenderTarget() == nullptr)
        {
            return;
        }

        auto& renderer = Common::getImpl<NativeGraphicsInterface>().getRenderer();

        renderer.prepareRender(getRenderTarget()->getNativeRenderTarget(), getViewport(), shouldClearTarget(), getClearColor());

        Common::SceneItem *rootItem = this;
        while (rootItem->hasParent())
        {
            rootItem = &rootItem->getParent();
        }

        std::function<void(Common::SceneItem * item)> renderSceneItem; 
        renderSceneItem = [this, &renderSceneItem](Common::SceneItem * item)
        {
            auto visualItem = dynamic_cast<VisualSceneItem*>(item);

            if (visualItem && visualItem->isEnabled())
            {
                visualItem->render(*this);
            }

            if (!visualItem || visualItem->isEnabled())
            {
                auto& children = item->getChildren();

                for (auto child : children)
                {
                    renderSceneItem(child.get());
                }
            }
        };
        
        renderSceneItem(rootItem);
    }

    const std::vector<Camera*>& Camera::getCameras()
    {
        return sCameras;
    }

    const Math::Matrix4x4& Camera::getViewMatrix() const
    {
        // needed to keep logical consistency
        Camera *_this = const_cast<Camera*>(this);
        _this->updateGlobalTransformationMatrix();
        return mViewMatrix;
    }

    const Math::Matrix4x4& Camera::getProjectionMatrix() const
    {
        return getProjection().getProjectionMatrix();
    }

    const Math::Matrix4x4& Camera::getViewProjectionMatrix() const
    {
        if (mIsViewProjectionMatrixDirty
            || (getTransformation().getVersion() != mLastViewMatrixVersion)
            || (getProjection().getVersion() != mLastProjectionMatrixVersion))
        {
            Camera *_this = const_cast<Camera*>(this);
            _this->mViewProjectionMatrix = getViewMatrix() * getProjectionMatrix();
            _this->mIsViewProjectionMatrixDirty = false;
            _this->mLastViewMatrixVersion = getTransformation().getVersion();
            _this->mLastProjectionMatrixVersion = getProjection().getVersion();
        }

        return mViewProjectionMatrix;
    }

    Camera::~Camera()
    {
        setRenderTarget(nullptr);
        sCameras.erase(std::find(sCameras.cbegin(), sCameras.cend(), this));
    }

    void Camera::onTransformationChanged()
    {
        SceneItem::onTransformationChanged();
        mIsViewProjectionMatrixDirty = true;
    }

    void Camera::setShouldClearTarget(bool clear)
    {
        mShouldClearTarget = clear;
    }
}