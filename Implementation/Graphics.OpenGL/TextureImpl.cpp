#include "TextureImpl.h"
#include <Mogren/ThirdParty/stb_image/stb_image.h>
#include <vector>
#include <assert.h>

namespace Graphics
{
    TextureImpl::TextureImpl(IO::InputStream & stream, uint32_t dataLength)
        : mGLTexture(GL_TEXTURE_2D)
    {
        std::vector<stbi_uc> dataVector(dataLength);
        stream.read(dataVector.data(), dataLength);
        mSourcePixels = stbi_load_from_memory(dataVector.data(), dataLength, &mWidth, &mHeight, &mChannelsCount, 0);
        assert(mSourcePixels);

    }

    const GLTexture& TextureImpl::getGLTexture() const
    {
        return mGLTexture;
    }

    int TextureImpl::getWidth() const
    {
        return mWidth;
    }

    int TextureImpl::getHeight() const
    {
        return mHeight;
    }

    void TextureImpl::finalize()
    {
        GLuint textureId;
        glGenTextures(1, &textureId);
        CHECK_GL_ERROR();

        GLenum format;

        switch (mChannelsCount)
        {
        case 2: format = GL_LUMINANCE_ALPHA; break;
        case 3: format = GL_RGB; break;
        case 4: format = GL_RGBA; break;
        default: format = GL_ALPHA; break;
        }

        glBindTexture(GL_TEXTURE_2D, textureId);
        CHECK_GL_ERROR();
        glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, mSourcePixels);
        CHECK_GL_ERROR();

        stbi_image_free(mSourcePixels);

        mGLTexture.init(textureId);
    }
}