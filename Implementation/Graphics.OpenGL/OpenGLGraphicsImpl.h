#pragma once

#include <Mogren/Framework/Graphics/NativeInterface/NativeGraphicsInterface.h>

#include "RendererImpl.h"
#include "RenderTargetImpl.h"
#include <memory>

namespace Graphics
{
    class RendererImpl;
    class RenderTargetImpl;

    class OpenGLGraphicsImpl : public NativeGraphicsInterface
    {
    public:
        OpenGLGraphicsImpl();

        virtual void initialize() override;

        virtual std::unique_ptr<NativeVertexBuffer> createVertexBuffer(
            const VertexStructureDesc &vertexStructureDesc,
            uint32_t vertexStructSize,
            uint32_t countElems,
            bool isDynamic) override;

        virtual std::unique_ptr<NativeIndexBuffer> createIndexBuffer(uint32_t countElems, bool isDynamic) override;

        virtual NativeRenderer& getRenderer() override;

        virtual std::unique_ptr<NativeTexture> loadTexture(IO::InputStream &stream, uint32_t dataLength) override;

        virtual std::unique_ptr<NativeShaderProgram> compileShaderProgram(IO::InputStream &stream, uint32_t dataLength) override;

        virtual std::tuple< std::unique_ptr<NativeRenderTarget>, std::unique_ptr<NativeTexture> >
            createRenderTargetTexture(int width, int height) override;

        virtual std::unique_ptr<NativeRenderTarget> createDisplayRenderTarget() override;

        virtual Math::Size2DI getMaxTextureSize() const override;

    private:
        std::unique_ptr<RendererImpl> mRenderer;
        Math::Size2DI mMaxTextureSize;
    };
}
