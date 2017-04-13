#pragma once

#include "GLTexture.h"

#include <Mogren/Framework/Graphics/NativeInterface/NativeTexture.h>
#include <Mogren/Framework/IO/InputStream.h>

namespace Graphics
{
    class TextureImpl : public NativeTexture
    {
    public:
        TextureImpl(IO::InputStream & stream, uint32_t dataLength);

        const GLTexture& getGLTexture() const;

        virtual int getWidth() const override;

        virtual int getHeight() const override;

        virtual void finalize() override;

    private:
        GLTexture mGLTexture;
        int mWidth;
        int mHeight;

        void * mSourcePixels;
        int mChannelsCount;
    };
}

