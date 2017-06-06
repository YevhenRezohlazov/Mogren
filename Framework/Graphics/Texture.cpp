#include "Texture.h"
#include "NativeInterface/NativeTexture.h"
#include <Mogren/Framework/Common/ImplementationProvider.h>
#include <Mogren/Framework/Graphics/NativeInterface/NativeGraphicsInterface.h>

namespace Graphics
{
    Texture::Texture(std::unique_ptr<NativeTexture> nativeTexture)
        : mNativeTexture(std::move(nativeTexture))
    {
        mSize = Math::Size2DI(nativeTexture->getWidth(), nativeTexture->getHeight());
    }
    
    Texture::Texture(
        std::unique_ptr<NativeTexture> nativeTexture,
        const Math::Size2DI & size,
        const Math::RectangleF & originalTextureRect)
        : mNativeTexture(std::move(nativeTexture)), mSize(size), mOriginalTextureRect(originalTextureRect)
    {
    }

    Texture::Texture(const Math::Size2DI & size, const uint8_t * data, bool autoFinalize)
        : Texture(Common::getImpl<NativeGraphicsInterface>().createTexture(size, data), size, Math::RectangleF(0.0f, 0.0f, 1.0f, 1.0f))
    {
        if (autoFinalize)
        {
            finalize();
        }
    }

    const NativeTexture& Texture::getNativeTexture() const
    {
        return *mNativeTexture;
    }

    const Math::Size2DI& Texture::getSize() const
    {
        return mSize;
    }

    void Texture::finalize()
    {
        mNativeTexture->finalize();
    }

    const Math::RectangleF Texture::getOriginalTextureRect() const
    {
        return mOriginalTextureRect;
    }

    Texture::~Texture() = default;
}