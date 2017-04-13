#pragma once

#include <stdint.h>

namespace Graphics
{
    enum class BaseShaderParameterType : int8_t
    {
        None = 0,
        Boolean = 1,
        Integer = 2,
        Float = 3,
        Texture = 4
    };

    class ShaderParameterType
    {
    private:
        BaseShaderParameterType mBaseType;
        int8_t mNDimension;
        int8_t mMDimension;
        int8_t mArraySize;

    public:
        ShaderParameterType();

        ShaderParameterType(
            BaseShaderParameterType baseType,
            int8_t nDimension,
            int8_t mDimension,
            int8_t arraySize);

        BaseShaderParameterType getBaseType() const;

        int8_t getNDimension() const;

        int8_t getMDimension() const;

        int8_t getArraySize() const;
    };
}
