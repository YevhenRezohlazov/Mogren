#include "ScalarShaderParameterSetter.h"
#include "NativeInterface/NativeTextureShaderParameterData.h"

namespace Graphics
{
    ScalarShaderParameterSetter<Texture>::ScalarShaderParameterSetter(
        std::unique_ptr<NativeShaderParameterSetter> nativeParameterSetter)
        : ShaderParameterSetter(std::move(nativeParameterSetter))
    {
    }

    void ScalarShaderParameterSetter<Texture>::setValue(const std::shared_ptr<const Texture> & value,
        TextureFilter minFilter /*= TextureFilter::Linear*/, TextureFilter magFilter /*= TextureFilter::Linear*/,
        TextureWrapMode wrapU /*= TextureWrapMode::Clamp*/, TextureWrapMode wrapV /*= TextureWrapMode::Clamp*/)
    {
        mTexture = value;
        const NativeTextureShaderParameterData data(value->getNativeTexture(), minFilter, magFilter, wrapU, wrapV);
        setValues(&data);
    }
}