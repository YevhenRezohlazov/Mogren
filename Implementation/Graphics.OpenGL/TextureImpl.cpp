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
        auto sourcePixels = stbi_load_from_memory(dataVector.data(), dataLength, &mWidth, &mHeight, &mChannelsCount, 0);
        mSourcePixels.insert(mSourcePixels.begin(), (uint8_t*)sourcePixels, (uint8_t*)sourcePixels + (mWidth * mHeight * mChannelsCount));
        assert(sourcePixels);
        stbi_image_free(sourcePixels);
    }

    TextureImpl::TextureImpl(const Math::Size2DI & size, const uint8_t * data)
        : mGLTexture(GL_TEXTURE_2D)
        , mWidth(size.width)
        , mHeight(size.height)
        , mChannelsCount(4)
    {
        mSourcePixels.insert(mSourcePixels.begin(), data, data + (mWidth * mHeight * 4));
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
        mGLTexture.init(mWidth, mHeight, mSourcePixels.data(), mChannelsCount);
        mSourcePixels.clear();
        mSourcePixels.shrink_to_fit();
    }
}