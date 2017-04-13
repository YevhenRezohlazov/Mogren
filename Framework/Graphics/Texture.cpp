#include "Texture.h"
#include "NativeInterface/NativeTexture.h"

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