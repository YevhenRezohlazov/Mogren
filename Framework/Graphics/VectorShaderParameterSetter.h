#pragma once

#include "ShaderParameterSetter.h"

#include <Mogren/Framework/Math/Vector.h>
#include <Mogren/Framework/Math/Vector2D.h>
#include <Mogren/Framework/Math/Vector3D.h>
#include <Mogren/Framework/Math/Vector4D.h>

#include "PrimitiveTypes/ShaderParameterType.h"

#include <type_traits>
#include <assert.h>

namespace Graphics
{
    template <typename TVector>
    class VectorShaderParameterSetter : public ShaderParameterSetter
    {
    public:
        ///
        /// Initializes a new instance of the VectorShaderParameterSetter class.
        ///
        /// \param nativeParameterSetter The native shader parameter setter.
        explicit VectorShaderParameterSetter(std::unique_ptr<NativeShaderParameterSetter> nativeParameterSetter);

        void setValue(const TVector &value);

        static ShaderParameterType getType();

    private:
        template <typename TValue, uint8_t Dimension>
        static TValue getValueType(Math::Vector<TValue, Dimension>);

        template <typename TValue, uint8_t Dimension>
        static uint8_t getVectorDimenstion(const Math::Vector<TValue, Dimension>&)
        {
            return Dimension;
        }
    };

    typedef VectorShaderParameterSetter<Math::Vector2DB> Vector2DBShaderParameterSetter;
    typedef VectorShaderParameterSetter<Math::Vector2DF> Vector2DFShaderParameterSetter;
    typedef VectorShaderParameterSetter<Math::Vector2DI> Vector2DIShaderParameterSetter;

    typedef VectorShaderParameterSetter<Math::Vector3DB> Vector3DBShaderParameterSetter;
    typedef VectorShaderParameterSetter<Math::Vector3DF> Vector3DFShaderParameterSetter;
    typedef VectorShaderParameterSetter<Math::Vector3DI> Vector3DIShaderParameterSetter;

    typedef VectorShaderParameterSetter<Math::Vector4DB> Vector4DBShaderParameterSetter;
    typedef VectorShaderParameterSetter<Math::Vector4DF> Vector4DFShaderParameterSetter;
    typedef VectorShaderParameterSetter<Math::Vector4DI> Vector4DIShaderParameterSetter;

    template<typename TVector>
    inline VectorShaderParameterSetter<TVector>::VectorShaderParameterSetter(std::unique_ptr<NativeShaderParameterSetter> nativeParameterSetter)
        : ShaderParameterSetter(std::move(nativeParameterSetter))
    {
    }

    template<typename TVector>
    inline void VectorShaderParameterSetter<TVector>::setValue(const TVector & value)
    {
        mNativeParameterSetter->setValues(&value[0]);
    }

    template<typename TVector>
    inline ShaderParameterType VectorShaderParameterSetter<TVector>::getType()
    {
        auto baseParamType = BaseShaderParameterType::None;
        if (std::is_floating_point<decltype(getValueType(TVector()))>::value)
        {
            baseParamType = BaseShaderParameterType::Float;
        }
        else if (std::is_same<decltype(getValueType(TVector())), bool>::value)
        {
            baseParamType = BaseShaderParameterType::Boolean;
        }
        else if (std::is_integral<decltype(getValueType(TVector()))>::value)
        {
            baseParamType = BaseShaderParameterType::Integer;
        }
        else
        {
            assert("Unsupported vector value type.");
        }

        return ShaderParameterType(baseParamType, getVectorDimenstion(TVector()), -1, -1);
    }
}

