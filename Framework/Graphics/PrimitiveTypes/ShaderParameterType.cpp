#include "ShaderParameterType.h"

namespace Graphics
{
    ShaderParameterType::ShaderParameterType(BaseShaderParameterType baseType, int8_t nDimension, int8_t mDimension, int8_t arraySize) : mBaseType(baseType), mNDimension(nDimension), mMDimension(mDimension), mArraySize(arraySize)
    {
    }

    ShaderParameterType::ShaderParameterType()
    {
    }

    BaseShaderParameterType ShaderParameterType::getBaseType() const
    {
        return mBaseType;
    }

    int8_t ShaderParameterType::getNDimension() const
    {
        return mNDimension;
    }

    int8_t ShaderParameterType::getMDimension() const
    {
        return mMDimension;
    }

    int8_t ShaderParameterType::getArraySize() const
    {
        return mArraySize;
    }
}