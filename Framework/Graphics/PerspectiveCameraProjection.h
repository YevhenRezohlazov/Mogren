#pragma once

#include "CameraProjection.h"

namespace Graphics
{
    ///
    /// Perspective camera projection implementation.
    ///
    class PerspectiveCameraProjection : public CameraProjection
    {
    public:
        ///
        /// Creates a new instance of PerspectiveCameraProjection class.
        ///
        PerspectiveCameraProjection();

        virtual const Math::Matrix4x4& getProjectionMatrix() const;

        virtual void updateViewport(const Viewport & newViewport);

        PerspectiveCameraProjection& setAngleOfView(float angleRadians);

        PerspectiveCameraProjection& setNearPlane(float nearPlane);

        PerspectiveCameraProjection& setFarPlane(float farPlane);

    private:
        void updateMatrix();

    private:
        Math::Matrix4x4 mProjectionMatrix;
        float mAspectRatio;
        float mAngleOfView;
        float mNearPlane;
        float mFarPlane;
        bool mDataChnaged;
    };
}


