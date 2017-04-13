#pragma once

#include "../PrimitiveTypes/TextureFilter.h"
#include "../PrimitiveTypes/TextureWrapMode.h"

namespace Graphics
{
    class NativeTexture;
    class NativeTextureShaderParameterData final
    {
    public:
        const NativeTexture* mNativeTexture;
        TextureFilter mMinFilter;
        TextureFilter mMagFilter;
        TextureWrapMode mWrapModeU;
        TextureWrapMode mWrapModeV;

        NativeTextureShaderParameterData(
            const NativeTexture& nativeTexture,
            TextureFilter minFilter,
            TextureFilter magFilter,
            TextureWrapMode wrapModeU,
            TextureWrapMode wrapModeV)
            : mNativeTexture(&nativeTexture),
            mMinFilter(minFilter), mMagFilter(magFilter),
            mWrapModeU(wrapModeU), mWrapModeV(wrapModeV)
        {
        }
    };
}