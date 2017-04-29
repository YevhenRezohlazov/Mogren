#pragma once

#include <memory>
#include <tuple>
#include <stdint.h>
#include <Mogren/Framework/Math/Vector2D.h>
#include "../PrimitiveTypes/VertexStructureDesc.h"

namespace IO
{
    class InputStream;
}

namespace Graphics
{
    class NativeVertexBuffer;
    class NativeIndexBuffer;
    class NativeRenderer;
    class NativeTexture;
    class NativeShaderProgram;
    class NativeRenderTarget;

    class NativeGraphicsInterface
    {
    public:
        ///
        /// Called after graphics context is created to initialize context-dependent resources
        ///
        virtual void initialize() = 0;

        ///
        /// Creates new vertex buffer instance
        ///
        virtual std::unique_ptr<NativeVertexBuffer> createVertexBuffer(
            const VertexStructureDesc &vertexStructureDesc,
            uint32_t vertexStructSize,
            uint32_t countElems,
            bool isDynamic) = 0;

        ///
        /// Creates new index buffer instance
        ///
        virtual std::unique_ptr<NativeIndexBuffer> createIndexBuffer(uint32_t countElems, bool isDynamic) = 0;

        ///
        /// Returns native renderer instance
        ///
        virtual NativeRenderer& getRenderer() = 0;

        ///
        /// Loads the texture from specified stream.
        ///
        /// \param stream The stream with texture data.
        /// \param dataLength The texture data length in the stream
        /// \returns Native texture instance.
        virtual std::unique_ptr<NativeTexture> loadTexture(IO::InputStream &stream, uint32_t dataLength) = 0;

        ///
        /// Creates testure with dirty data to be filled by user
        /// \param data Texture data. width * height * 4 bytes, RGBA
        ///
        virtual std::unique_ptr<NativeTexture> createTexture(const Math::Size2DI & size, const uint8_t * data) = 0;

        ///
        /// Compiles the shader from specified shader stream.
        ///
        /// \param stream The shader data stream.
        /// \returns Native shader instance.
        virtual std::unique_ptr<NativeShaderProgram> compileShaderProgram(IO::InputStream &stream, uint32_t dataLength) = 0;

        ///
        /// Creates new render target texture.
        ///
        /// \param width The texture width.
        /// \param height The texture height.
        /// \param renderTarget [out] The render target part of the render target texture
        /// \param texture [out] The render target texture part of the render target texture
        virtual std::tuple< std::unique_ptr<NativeRenderTarget>, std::unique_ptr<NativeTexture> >
            createRenderTargetTexture(int width, int height) = 0;

        ///
        /// Gets the render target for main device display.
        ///
        virtual std::unique_ptr<NativeRenderTarget> createDisplayRenderTarget() = 0;

        ///
        /// Returns the maximal size of a texture that can be loaded.
        ///
        virtual Math::Size2DI getMaxTextureSize() const = 0;

        ///
        /// Called when current grame is finished drawing
        ///
        virtual void onFrameDrawingFinished() {}

        virtual ~NativeGraphicsInterface() = default;
    };
}

