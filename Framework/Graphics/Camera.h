#pragma once

#include <Mogren/Framework/Common/SceneItem.h>
#include "PrimitiveTypes/Viewport.h"
#include "PrimitiveTypes/Color.h"
#include "CameraProjection.h"

#include <vector>
#include <memory>

namespace Graphics
{
    class RenderTarget;
    ///
    /// Camera class
    ///
    class Camera : public Common::SceneItem
    {
    public:
        ///
        /// Initializes a new instance of the Camera class.
        /// Camera is not attached to any scene. Set Scene property to attach camera.
        ///
        Camera();
        Camera(const Camera&) = delete;
        Camera& operator=(const Camera&) = delete;

        ///
        /// Gets the camera projection.
        ///
        const CameraProjection& getProjection() const;
        template <typename TCameraProjection>
        TCameraProjection& projection();

        ///
        /// Gets the camera projection matrix.
        ///
        const Math::Matrix4x4& getProjectionMatrix() const;

        ///
        /// Gets the camera view*projection matrix.
        ///
        const Math::Matrix4x4& getViewProjectionMatrix() const;

        ///
        /// Returns camera view matrix (inverted global transformation matrix)
        ///
        const Math::Matrix4x4& getViewMatrix() const;

        ///
        /// Gets a value indicating whether the camera should clear render target before rendering.
        ///
        bool shouldClearTarget() const;

        ///
        /// Sets a value indicating whether the camera should clear render target before rendering.
        ///
        void setShouldClearTarget(bool clear);

        ///
        /// Gets the render target clear.
        ///
        const Color& getClearColor() const;

        ///
        /// Sets the render target clear.
        ///
        void setClearColor(const Color& color);

        ///
        /// Gets the camera viewport.
        ///
        const Viewport& getViewport() const;

        ///
        /// Sets the camera viewport.
        ///
        void setViewport(const Viewport& viewport);

        ///
        /// Gets the camera's render target.
        ///
        std::shared_ptr<const RenderTarget> getRenderTarget() const;
        std::shared_ptr<RenderTarget> getRenderTarget();

        ///
        /// Sets the camera's render target.
        ///
        void setRenderTarget(std::shared_ptr<RenderTarget> renderTarget);

        ///
        /// The higher is the priority - the earlier the camera view is drawn
        ///
        void setRenderPriority(float renderPriority);
        float getRenderPriority() const;

        ///
        /// Updates the global transformation matrix, if needed
        ///
        virtual bool updateGlobalTransformationMatrix() override;

        ///
        /// Draws the scene from this camera view to the camera's attached render target
        ///
        virtual void render();

        static const std::vector<Camera*>& getCameras();

        ~Camera();

    protected:
        virtual void onTransformationChanged() override;

    private:
        ///
        /// The camera projection
        ///
        std::unique_ptr<CameraProjection> mProjection;

        ///
        /// The render target
        ///
        std::shared_ptr<RenderTarget> mRenderTarget;

        ///
        /// The viewport
        ///
        Viewport mViewport;

        ///
        /// The value indicating whether the camera should clear render target before rendering.
        ///
        bool mShouldClearTarget;

        ///
        /// The render target clear color.
        ///
        Color mClearColor;

        ///
        /// The camera view matrix
        ///
        Math::Matrix4x4 mViewMatrix;

        ///
        /// The camera view*projection matrix
        ///
        Math::Matrix4x4 mViewProjectionMatrix;

        ///
        /// True, if view*projection matrix should be updated
        ///
        bool mIsViewProjectionMatrixDirty;

        ///
        /// Version of the view matrix that was last used in
        /// view*projection matrix calculation
        ///
        uint64_t mLastViewMatrixVersion;

        ///
        /// Version of the projection matrix that was last used in
        /// view*projection matrix calculation
        ///
        uint64_t mLastProjectionMatrixVersion;

        float mRenderPriority = 0.0f;

        static std::vector<Camera*> sCameras;
    };

    template<typename TCameraProjection>
    TCameraProjection & Camera::projection()
    {
        auto result = dynamic_cast<TCameraProjection*>(mProjection.get());

        if (result == nullptr)
        {
            mProjection = std::make_unique<TCameraProjection>();
            mProjection->updateViewport(mViewport);
            mIsViewProjectionMatrixDirty = true;
        }

        return static_cast<TCameraProjection&>(*mProjection);
    }
}

