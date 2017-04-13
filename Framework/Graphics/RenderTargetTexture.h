#pragma once

#include "Texture.h"
#include "RenderTarget.h"

namespace Graphics
{
    class NativeRenderTarget;
    class NativeTexture;

    ///
    /// Texture that can be set as render target.
    ///
    class RenderTargetTexture : public Texture, public RenderTarget
    {
    public:
        ///
        /// Initializes a new instance of the RenderTargetTexture class.
        ///
        /// \param nativeRenderTarget The native render target instance.
        /// \param nativeTexture The native render target texture instance.
        RenderTargetTexture(
            std::unique_ptr<NativeRenderTarget> nativeRenderTarget,
            std::unique_ptr<NativeTexture> nativeTexture);

        ///
        /// Initializes a new instance of the RenderTargetTexture class with given width and height.
        ///
        /// \param nativeRenderTargetTexture The native render target texture.
        RenderTargetTexture(int width, int height);

        ///
        /// Gets the render target texture size.
        ///
        Math::Size2DI getSize() const;
    };
}

