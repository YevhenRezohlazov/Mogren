#include "PerspectiveCameraProjection.h"
#include <Mogren/Framework/Math/Functions.h>

namespace Graphics
{
    PerspectiveCameraProjection::PerspectiveCameraProjection()
        : mProjectionMatrix(Math::Matrix4x4::Identity), mAspectRatio(1.0f)
        , mAngleOfView(Math::PI / 4.0f), mNearPlane(0.1f), mFarPlane(10.0f)
        , mDataChnaged(true)
    {
    }

    const Math::Matrix4x4& PerspectiveCameraProjection::getProjectionMatrix() const
    {
        if (mDataChnaged)
        {
            auto self = const_cast<PerspectiveCameraProjection*>(this);
            self->updateMatrix();
        }

        return mProjectionMatrix;
    }

    void PerspectiveCameraProjection::updateViewport(const Viewport & newViewport)
    {
        mAspectRatio = newViewport.mWidth / float(newViewport.mHeight);
        mDataChnaged = true;
    }

    PerspectiveCameraProjection& PerspectiveCameraProjection::setAngleOfView(float angleRadians)
    {
        mAngleOfView = angleRadians;
        mDataChnaged = true;
        return *this;
    }

    PerspectiveCameraProjection& PerspectiveCameraProjection::setNearPlane(float nearPlane)
    {
        mNearPlane = nearPlane;
        mDataChnaged = true;
        return *this;
    }

    PerspectiveCameraProjection& PerspectiveCameraProjection::setFarPlane(float farPlane)
    {
        mFarPlane = farPlane;
        mDataChnaged = true;
        return *this;
    }

    float PerspectiveCameraProjection::getAngleOfView() const
    {
        return mAngleOfView;
    }

    float PerspectiveCameraProjection::getAspectRatio( ) const
    {
        return mAspectRatio;
    }

    void PerspectiveCameraProjection::updateMatrix()
    {
        const float f = 1.0f / Math::tan(mAngleOfView * 0.5f);

        mProjectionMatrix[0][0] = f / mAspectRatio;
        mProjectionMatrix[1][1] = f;
        mProjectionMatrix[2][2] = (mFarPlane + mNearPlane) / (mNearPlane - mFarPlane);
        mProjectionMatrix[3][2] = (2.0f * mFarPlane * mNearPlane) / (mNearPlane - mFarPlane);
        mProjectionMatrix[2][3] = -1.0f;
        mProjectionMatrix[3][3] = 0.0f;
    }
}