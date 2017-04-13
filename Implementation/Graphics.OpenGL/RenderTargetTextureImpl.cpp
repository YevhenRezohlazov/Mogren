/*#include "PrecompiledHeader.h"
#include "RenderTargetTextureImpl.h"

namespace Graphics
{
    int RenderTargetTextureImpl::getWidth() const
    {
        return TextureImpl::getWidth();
    }

    int RenderTargetTextureImpl::getHeight() const
    {
        return TextureImpl::getHeight();
    }

    RenderTargetTextureImpl::Ptr RenderTargetTextureImpl::create(int width, int height)
    {
        INSERT_CREATION_CODE(RenderTargetTextureImpl, width, height);
    }

    RenderTargetTextureImpl::RenderTargetTextureImpl()
    {
    }

    void RenderTargetTextureImpl::init(int width, int height)
    {
        GLuint textureId, frameBufferId;

        Threading::runInMainThread(
            [width, height, &textureId, &frameBufferId, this]()
        {
            mRenderbuffer.init();

            glGenTextures(1, &textureId);
            CHECK_GL_ERROR();
            glBindTexture(GL_TEXTURE_2D, textureId);
            CHECK_GL_ERROR();
            char *buffer = new char[width * height * 4];
            memset(buffer, 0, width * height * 4);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
            CHECK_GL_ERROR();
            delete [] buffer;

            glGenFramebuffers(1, &frameBufferId);
            CHECK_GL_ERROR();
            glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
            CHECK_GL_ERROR();
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);
            CHECK_GL_ERROR();

            mRenderbuffer.bind();
            CHECK_GL_ERROR();
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
            CHECK_GL_ERROR();
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mRenderbuffer.getId());
            CHECK_GL_ERROR();
        }, false);

        TextureImpl::init(textureId, width, height);
        RenderTargetImpl::init(frameBufferId, width, height);
    }
}*/