#include "GLTexture.h"

namespace Graphics
{
    namespace
    {
        GLenum convertFilterToGLFilter(TextureFilter filter)
        {
            switch (filter)
            {
            case TextureFilter::Nearest: return GL_NEAREST;
            case TextureFilter::Linear: return GL_LINEAR;
            default: return 0;
            }
        }

        GLenum convertWrapModeToGLWrapMode(TextureWrapMode mode)
        {
            switch (mode)
            {
            case TextureWrapMode::Clamp: return GL_CLAMP_TO_EDGE; break;
            case TextureWrapMode::Repeat: return GL_REPEAT; break;
            case TextureWrapMode::Mirror: return GL_MIRRORED_REPEAT; break;
            default: return 0;
            }
        }
    }

    void GLTexture::init(bool suppressDeletion)
    {
        GLResource::init(suppressDeletion);
        glGenTextures(1, &mId);
        CHECK_GL_ERROR();
    }

    void GLTexture::init(GLuint id, bool suppressDeletion)
    {
        GLResource::init(id, suppressDeletion);
    }

    GLTexture::GLTexture(GLenum target)
        : mBindTarget(target)
    {
    }

    void GLTexture::bind() const
    {
        checkInited();
        glBindTexture(mBindTarget, mId);
        CHECK_GL_ERROR();
    }

    void GLTexture::deleteResource()
    {
        glDeleteTextures(1, &mId);
        CHECK_GL_ERROR();
        mId = -1;
    }

    void GLTexture::setParameters(
        TextureFilter minFilter,
        TextureFilter magFilter,
        TextureWrapMode wrapU,
        TextureWrapMode wrapV) const
    {
        glTexParameteri(mBindTarget, GL_TEXTURE_MIN_FILTER, convertFilterToGLFilter(minFilter));
        glTexParameteri(mBindTarget, GL_TEXTURE_MAG_FILTER, convertFilterToGLFilter(magFilter));

        glTexParameteri(mBindTarget, GL_TEXTURE_WRAP_S, convertWrapModeToGLWrapMode(wrapU));
        glTexParameteri(mBindTarget, GL_TEXTURE_WRAP_T, convertWrapModeToGLWrapMode(wrapV));
    }
}