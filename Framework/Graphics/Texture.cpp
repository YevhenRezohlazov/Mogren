#include "Texture.h"
#include "NativeInterface/NativeTexture.h"
#include <Mogren/Framework/Common/ImplementationProvider.h>
#include <Mogren/Framework/Graphics/NativeInterface/NativeGraphicsInterface.h>

namespace Graphics
{
    Texture::Texture(std::unique_ptr<NativeTexture> nativeTexture)
        : Texture(std::move(nativeTexture),
            Math::Size2DI(mNativeTexture->getWidth(), mNativeTexture->getHeight()))
    {
    }
    
    Texture::Texture(std::unique_ptr<NativeTexture> nativeTexture, const Math::Size2DI & size)
        : mNativeTexture(std::move(nativeTexture)), mSize(size)
    {
    }

    Texture::Texture(const Math::Size2DI & size, const uint8_t * data, bool autoFinalize)
        : Texture(Common::getImpl<NativeGraphicsInterface>().createTexture(size, data))
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

    Texture::~Texture() = default;
}