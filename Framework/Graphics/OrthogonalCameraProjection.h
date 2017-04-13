#pragma once

#include "CameraProjection.h"

namespace Graphics
{
    ///
    /// Orthogonal camera projection implementation.
    ///
    class OrthogonalCameraProjection : public CameraProjection
    {
    public:
        ///
        /// Creates a new instance of OrthogonalCameraProjection class.
        ///
        OrthogonalCameraProjection();

        ///
        /// Returns true if the projection should maintain the aspect ratio.
        ///
        bool isMaintainingAspectRatio() const;

        ///
        /// Set to true if the projection should maintain the aspect ratio.
        ///
        OrthogonalCameraProjection& setMaintainingAspectRatio(bool value);

        ///
        /// Returns the view area width.
        ///
        float getViewAreaWidth() const;

        ///
        /// Sets the view area width.
        ///
        OrthogonalCameraProjection& setViewAreaWidth(float width);

        ///
        /// Returns the view area height.
        ///
        float getViewAreaHeight() const;

        ///
        /// Sets the view area height.
        ///
        OrthogonalCameraProjection& setViewAreaHeight(float height);

        ///
        /// Returns the view area width.
        ///
        float getViewAreaDepth() const;

        ///
        /// Sets the view area depth.
        ///
        OrthogonalCameraProjection& setViewAreaDepth(float depth);

        virtual const Math::Matrix4x4& getProjectionMatrix() const;

        virtual void updateViewport(Viewport newViewport);

    private:
        void updateMatrix();

    private:
        Math::Matrix4x4 mProjectionMatrix;
        bool mMaintainAspectRatio;
        float mAspectRatio;

        float mViewAreaWidth;
        bool mUseWidth;

        float mViewAreaHeight;
        bool mUseHeight;

        float mViewAreaDepth;

        bool mDataChnaged;
    };
}


