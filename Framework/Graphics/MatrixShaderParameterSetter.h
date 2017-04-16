#pragma once

#include "ShaderParameterSetter.h"
#include "PrimitiveTypes/ShaderParameterType.h"
#include <Mogren/Framework/Math/Matrix.h>

namespace Graphics
{
    template <uint8_t NDimension>
    class MatrixShaderParameterSetter : public ShaderParameterSetter
    {
    public:
        ///
        /// Initializes a new instance of the MatrixShaderParameterSetter class.
        ///
        /// \param nativeParameterSetter The native shader parameter setter.
        explicit MatrixShaderParameterSetter(std::unique_ptr<NativeShaderParameterSetter> nativeParameterSetter);

        ///
        /// Sets the given matrix as the shader parameter value
        /// \param value The matrix value
        ///
        void setValue(const Math::Matrix<NDimension, NDimension> &value);

        static ShaderParameterType getType();
    };

    typedef MatrixShaderParameterSetter<2> Matrix2x2ShaderParameterSetter;
    typedef MatrixShaderParameterSetter<3> Matrix3x3ShaderParameterSetter;
    typedef MatrixShaderParameterSetter<4> Matrix4x4ShaderParameterSetter;

    template<uint8_t NDimension>
    inline MatrixShaderParameterSetter<NDimension>::MatrixShaderParameterSetter(std::unique_ptr<NativeShaderParameterSetter> nativeParameterSetter)
        : ShaderParameterSetter(std::move(nativeParameterSetter))
    {
    }

    template<uint8_t NDimension>
    inline void MatrixShaderParameterSetter<NDimension>::setValue(const Math::Matrix<NDimension, NDimension>& value)
    {
        setValues(&value[0][0]);
    }

    template<uint8_t NDimension>
    inline ShaderParameterType MatrixShaderParameterSetter<NDimension>::getType()
    {
        return ShaderParameterType(BaseShaderParameterType::Float, NDimension, NDimension, -1);
    }
}

