#pragma once

#include "ShaderParameterSetter.h"
#include "Texture.h"
#include "PrimitiveTypes/TextureFilter.h"
#include "PrimitiveTypes/TextureWrapMode.h"

namespace Graphics
{
    template <typename TScalar>
    class ScalarShaderParameterSetter : public ShaderParameterSetter
    {
    public:
        ///
        /// Initializes a new instance of the ShaderParameter class.
        ///
        /// \param nativeParameter The native shader parameter.
        explicit ScalarShaderParameterSetter(std::unique_ptr<NativeShaderParameterSetter> nativeParameterSetter);

        void setValue(TScalar value)
        {
            setValues(&value);
        }
    };

    typedef ScalarShaderParameterSetter<bool> BoolShaderParameterSetter;
    typedef ScalarShaderParameterSetter<float> FloatShaderParameterSetter;
    typedef ScalarShaderParameterSetter<int32_t> IntShaderParameterSetter;

    template<>
    class ScalarShaderParameterSetter<Texture> : public ShaderParameterSetter
    {
    public:
        explicit ScalarShaderParameterSetter(std::unique_ptr<NativeShaderParameterSetter> nativeParameterSetter);

        void setValue(
            const std::shared_ptr<const Texture> & value,
            TextureFilter minFilter = TextureFilter::Linear,
            TextureFilter magFilter = TextureFilter::Linear,
            TextureWrapMode wrapU = TextureWrapMode::Clamp,
            TextureWrapMode wrapV = TextureWrapMode::Clamp);

    private:
        ///
        /// Need to store texture to prevent texture instance from deletion
        /// (as only the native texture is passed to the setter).
        ///
        std::shared_ptr<const Texture> mTexture;
    };

    typedef ScalarShaderParameterSetter<Texture> TextureShaderParameterSetter;

    ///
    /// Initializes a new instance of the ShaderParameter class.
    ///
    /// \param nativeParameter The native shader parameter.
    template<typename TScalar>
    inline ScalarShaderParameterSetter<TScalar>::ScalarShaderParameterSetter(
        std::unique_ptr<NativeShaderParameterSetter> nativeParameterSetter)
        : ShaderParameterSetter(std::move(nativeParameterSetter))
    {
    }
}

