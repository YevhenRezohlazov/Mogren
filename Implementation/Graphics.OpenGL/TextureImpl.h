#pragma once

#include "GLTexture.h"

#include <Mogren/Framework/Graphics/NativeInterface/NativeTexture.h>
#include <Mogren/Framework/IO/InputStream.h>
#include <Mogren/Framework/Math/Vector2D.h>
#include <vector>

namespace Graphics
{
    class TextureImpl : public NativeTexture
    {
    public:
        TextureImpl(IO::InputStream & stream, uint32_t dataLength);
        TextureImpl(const Math::Size2DI & size, const uint8_t * data);

        const GLTexture& getGLTexture() const;

        virtual int getWidth() const override;

        virtual int getHeight() const override;

        virtual void finalize() override;

    private:
        GLTexture mGLTexture;
        int mWidth;
        int mHeight;

        std::vector<uint8_t> mSourcePixels;
        int mChannelsCount;
    };
}

