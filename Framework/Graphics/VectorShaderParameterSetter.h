#pragma once

#include "ShaderParameterSetter.h"

#include <Mogren/Framework/Math/Vector.h>
#include <Mogren/Framework/Math/Vector2D.h>
#include <Mogren/Framework/Math/Vector3D.h>
#include <Mogren/Framework/Math/Vector4D.h>

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
}

