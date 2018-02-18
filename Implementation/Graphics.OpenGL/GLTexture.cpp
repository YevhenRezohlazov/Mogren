#include "GLTexture.h"
#include <memory>
#include <cstring>

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

    void GLTexture::init(int width, int height, const uint8_t * sourcePixels, int channelsCount)
    {
        GLuint textureId;
        glGenTextures(1, &textureId);
        CHECK_GL_ERROR();

        GLenum format;

        if (mSourcePixels.empty())
        {
            mSourcePixels.resize(width * height * channelsCount);
            std::memcpy(&mSourcePixels.front(), sourcePixels, mSourcePixels.size());
        }

        switch (channelsCount)
        {
        case 2: format = GL_LUMINANCE_ALPHA; break;
        case 3: format = GL_RGB; break;
        case 4: format = GL_RGBA; break;
        default: format = GL_ALPHA; break;
        }

        glBindTexture(GL_TEXTURE_2D, textureId);
        CHECK_GL_ERROR();
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, mSourcePixels.data());
        CHECK_GL_ERROR();

        GLResource::init(textureId, false);
        mWidth = width;
        mHeight = height;
        mChannelsCount = channelsCount;
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

    void GLTexture::reload()
    {
        glDeleteTextures(1, &mId);
        glGetError(); //Ignore error if any
        mId = -1;
        mInited = false;
        init(mWidth, mHeight, &mSourcePixels.front(), mChannelsCount);
    }
}