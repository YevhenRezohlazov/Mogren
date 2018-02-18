#include "OpenGLGraphicsImpl.h"
#include "VertexBufferImpl.h"
#include "IndexBufferImpl.h"
#include "TextureImpl.h"
#include "ShaderProgramImpl.h"
#include "ResourcesReloader.h"

#include <Mogren/Framework/Common/ImplementationProvider.h>
#include <Mogren/Framework/Common/NativeInterface/NativeCoreInterface.h>
#include <Mogren/Framework/App/App.h>
#include <Mogren/Framework/IO/MemoryStream.h>
#include <Mogren/Framework/IO/StreamUtils.h>

namespace Graphics
{
    OpenGLGraphicsImpl * OpenGLGraphicsImpl::mInstance = nullptr;

    OpenGLGraphicsImpl::OpenGLGraphicsImpl()
    {
        mInstance = this;
    }

    OpenGLGraphicsImpl::~OpenGLGraphicsImpl()
    {
        mInstance = nullptr;
    }

    std::unique_ptr<NativeVertexBuffer> OpenGLGraphicsImpl::createVertexBuffer(
        const VertexStructureDesc &vertexStructureDesc, uint32_t vertexStructureSize, uint32_t countElems, bool isDynamic)
    {
        return std::make_unique<VertexBufferImpl>(vertexStructureDesc, vertexStructureSize, countElems, isDynamic);
    }

    std::unique_ptr<NativeIndexBuffer> OpenGLGraphicsImpl::createIndexBuffer(uint32_t countElems, bool isDynamic)
    {
        return std::make_unique<IndexBufferImpl>(countElems, isDynamic);
    }

    NativeRenderer& OpenGLGraphicsImpl::getRenderer()
    {
        return *mRenderer;
    }

    std::unique_ptr<NativeTexture> OpenGLGraphicsImpl::loadTexture(IO::InputStream & stream, uint32_t dataLength)
    {
        return std::make_unique<TextureImpl>(stream, dataLength);
    }

    std::unique_ptr<NativeTexture> OpenGLGraphicsImpl::createTexture(const Math::Size2DI & size, const uint8_t * data)
    {
        return std::make_unique<TextureImpl>(size, data);
    }

    std::unique_ptr<NativeShaderProgram> OpenGLGraphicsImpl::compileShaderProgram(IO::InputStream & stream, uint32_t dataLength)
    {
        return std::make_unique<ShaderProgramImpl>(stream);
    }

    std::tuple<std::unique_ptr<NativeRenderTarget>, std::unique_ptr<NativeTexture>>
        OpenGLGraphicsImpl::createRenderTargetTexture(int width, int height)
    {
        //auto res = RenderTargetTextureImpl::create(width, height);
        return{};
    }

    std::unique_ptr<NativeRenderTarget> OpenGLGraphicsImpl::createDisplayRenderTarget()
    {
        const auto screenSize = Common::getImpl<Common::NativeCoreInterface>().getScreenSize();
        return std::make_unique<RenderTargetImpl>(0, screenSize.width, screenSize.height, true);
    }

    Math::Size2DI OpenGLGraphicsImpl::getMaxTextureSize() const
    {
        return mMaxTextureSize;
    }

    void OpenGLGraphicsImpl::reloadResources()
    {
        mInstance->initialize();
        ResourcesReloader::reloadResources();
    }

    void OpenGLGraphicsImpl::initialize()
    {
        mRenderer = std::make_unique<RendererImpl>();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        CHECK_GL_ERROR();

        GLint maxTexSize;
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexSize);
        CHECK_GL_ERROR();

        mMaxTextureSize = Math::Size2DI(maxTexSize);
    }
}