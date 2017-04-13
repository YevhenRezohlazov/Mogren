#include "RenderTargetTexture.h"
#include "NativeInterface/NativeGraphicsInterface.h"
#include "NativeInterface/NativeRenderTarget.h"
#include "NativeInterface/NativeTexture.h"
#include <Mogren/Framework/Common/ImplementationProvider.h>

namespace Graphics
{
    namespace
    {
        thread_local std::unique_ptr<NativeRenderTarget> createdRenderTarget;

        std::unique_ptr<NativeTexture> createRenderTargetTexture(int width, int height)
        {
            auto nativeInts = Common::getImpl<NativeGraphicsInterface>().createRenderTargetTexture(width, height);
            createdRenderTarget = std::move(std::get<0>(nativeInts));
            std::unique_ptr<NativeTexture> texture = std::move(std::get<1>(nativeInts));
            return texture;
        }
    }

    RenderTargetTexture::RenderTargetTexture(
        std::unique_ptr<NativeRenderTarget> nativeRenderTarget,
        std::unique_ptr<NativeTexture> nativeTexture)
        : Texture(std::move(nativeTexture)), RenderTarget(std::move(nativeRenderTarget))
    {
    }

    RenderTargetTexture::RenderTargetTexture(int width, int height)
        : Texture(createRenderTargetTexture(width, height))
        , RenderTarget(std::move(createdRenderTarget))
    {
    }

    Math::Size2DI RenderTargetTexture::getSize() const
    {
        return Texture::getSize();
    }
}