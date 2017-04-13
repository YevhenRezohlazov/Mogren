#include "CameraProjection.h"

namespace Graphics
{
    CameraProjection::CameraProjection()
        : mProjectionMatrix(Math::Matrix4x4::Identity), mVersion(0)
    {
    }

    const Math::Matrix4x4 & CameraProjection::getProjectionMatrix() const
    {
        return mProjectionMatrix;
    }

    void CameraProjection::updateViewport(Viewport newViewport)
    {
    }

    uint64_t CameraProjection::getVersion() const
    {
        return mVersion;
    }

    void CameraProjection::incrementVersion()
    {
        mVersion += 1;
    }
}