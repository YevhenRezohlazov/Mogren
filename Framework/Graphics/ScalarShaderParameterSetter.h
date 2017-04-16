#pragma once

#include "ShaderParameterSetter.h"
#include "Texture.h"
#include "PrimitiveTypes/TextureFilter.h"
#include "PrimitiveTypes/TextureWrapMode.h"
#include "PrimitiveTypes/ShaderParameterType.h"
#include <type_traits>
#include <assert.h>

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

        static ShaderParameterType getType();
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

        static ShaderParameterType getType();
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

    template<typename TScalar>
    inline ShaderParameterType ScalarShaderParameterSetter<TScalar>::getType()
    {
        auto baseParamType = BaseShaderParameterType::None;
        if (std::is_floating_point<TScalar>::value)
        {
            baseParamType = BaseShaderParameterType::Float;
        }
        else if (std::is_same<TScalar, bool>::value)
        {
            baseParamType = BaseShaderParameterType::Boolean;
        }
        else if (std::is_integral<TScalar>::value)
        {
            baseParamType = BaseShaderParameterType::Integer;
        }
        else
        {
            assert("Unsupported vector value type.");
        }

        return ShaderParameterType(baseParamType, -1, -1, -1);
    }
}

