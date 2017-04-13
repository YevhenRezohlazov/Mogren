#include "RenderTarget.h"
#include "Camera.h"
#include "NativeInterface/NativeRenderTarget.h"
#include <assert.h>
#include <algorithm>

namespace Graphics
{
    RenderTarget::RenderTarget(std::unique_ptr<NativeRenderTarget> nativeRenderTarget)
        : mNativeRenderTarget(std::move(nativeRenderTarget))
    {
    }

    const NativeRenderTarget& RenderTarget::getNativeRenderTarget() const
    {
        return *mNativeRenderTarget;
    }

    Math::Size2DI RenderTarget::getSize() const
    {
        return Math::Size2DI(mNativeRenderTarget->getWidth(), mNativeRenderTarget->getHeight());
    }

    void RenderTarget::attachCamera(Camera &camera)
    {
        mAttachedCameras.push_back(camera);
    }

    void RenderTarget::detachCamera(Camera &camera)
    {
        auto camIter = std::find_if(
            mAttachedCameras.cbegin(),
            mAttachedCameras.cend(),
            [&camera](const Camera & item) { return &item == &camera; });
        assert(camIter != mAttachedCameras.cend());
        mAttachedCameras.erase(camIter);
    }

    const std::vector<std::reference_wrapper<Camera>>& RenderTarget::getAttachedCameras() const
    {
        return mAttachedCameras;
    }
    RenderTarget::~RenderTarget() = default;
}