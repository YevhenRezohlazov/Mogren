#include "OrthogonalCameraProjection.h"

namespace Graphics
{
    OrthogonalCameraProjection::OrthogonalCameraProjection()
        : mProjectionMatrix(Math::Matrix4x4::Identity), mMaintainAspectRatio(false), mAspectRatio(1.0f),
        mViewAreaWidth(2.0f), mUseWidth(true), mViewAreaHeight(2.0f), mUseHeight(true), mViewAreaDepth(2.0f),
        mDataChnaged(false)
    {
    }

    const Math::Matrix4x4& OrthogonalCameraProjection::getProjectionMatrix() const
    {
        if (mDataChnaged)
        {
            auto self = const_cast<OrthogonalCameraProjection*>(this);
            self->updateMatrix();
        }

        return mProjectionMatrix;
    }

    void OrthogonalCameraProjection::updateViewport(const Viewport & newViewport)
    {
        mAspectRatio = newViewport.mWidth / float(newViewport.mHeight);
        mDataChnaged = true;
    }

    bool OrthogonalCameraProjection::isMaintainingAspectRatio() const
    {
        return mMaintainAspectRatio;
    }

    OrthogonalCameraProjection& OrthogonalCameraProjection::setMaintainingAspectRatio(bool value)
    {
        mMaintainAspectRatio = value;
        mDataChnaged = true;
        return *this;
    }

    void OrthogonalCameraProjection::updateMatrix()
    {
        auto width = getViewAreaWidth();
        auto height = getViewAreaHeight();
        auto depth = getViewAreaDepth();

        mProjectionMatrix.m00 = 2.0f / width;
        mProjectionMatrix.m11 = 2.0f / height;
        mProjectionMatrix.m22 = 2.0f / depth;
    }

    float OrthogonalCameraProjection::getViewAreaWidth() const
    {
        return (mUseWidth | !mMaintainAspectRatio) ? mViewAreaWidth : mViewAreaHeight * mAspectRatio;
    }

    float OrthogonalCameraProjection::getViewAreaHeight() const
    {
        return (mUseHeight | !mMaintainAspectRatio) ? mViewAreaHeight : mViewAreaWidth / mAspectRatio;
    }

    float OrthogonalCameraProjection::getViewAreaDepth() const
    {
        return mViewAreaDepth;
    }

    OrthogonalCameraProjection& OrthogonalCameraProjection::setViewAreaWidth(float width)
    {
        mUseHeight = false;
        mUseWidth = true;
        mViewAreaWidth = width;
        mDataChnaged = true;
        return *this;
    }

    OrthogonalCameraProjection& OrthogonalCameraProjection::setViewAreaHeight(float height)
    {
        mUseHeight = true;
        mUseWidth = false;
        mViewAreaHeight = height;
        mDataChnaged = true;
        return *this;
    }

    OrthogonalCameraProjection& OrthogonalCameraProjection::setViewAreaDepth(float depth)
    {
        mViewAreaDepth = depth;
        mDataChnaged = true;
        return *this;
    }
}