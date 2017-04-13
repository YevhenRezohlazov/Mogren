#include "ShaderParameterSetterImpl.h"
#include "ShaderProgramImpl.h"
#include <Mogren/Framework/Graphics/NativeInterface/NativeTextureShaderParameterData.h>

namespace Graphics
{
    ShaderParameterSetterImpl::ShaderParameterSetterImpl(
        const ShaderProgramImpl &shaderProgram, const std::string& name, ShaderParameterType type)
    {
        mUniformLocation = shaderProgram.getGLProgram().getUniformLocation(name);
        mDataSize = 0;

        switch (type.getBaseType())
        {
        case BaseShaderParameterType::Boolean:// bool is int
        case BaseShaderParameterType::Float:
        case BaseShaderParameterType::Integer:
            mDataSize = 4;
            break;
        case BaseShaderParameterType::Texture:
            mDataSize = sizeof(NativeTextureShaderParameterData);
            break;
        default: break;
        }

        if (type.getNDimension() != -1)
        {
            mDataSize *= type.getNDimension();
        }

        if (type.getMDimension() != -1)
        {
            mDataSize *= type.getMDimension();
        }

        if (type.getArraySize() != -1)
        {
            mDataSize *= type.getArraySize();
        }

        mData = new char[mDataSize];
        memset(mData, 0, mDataSize);

        if (type.getBaseType() == BaseShaderParameterType::Float)
        {
            if (type.getMDimension() != -1) // matrix
            {
                if (type.getNDimension() == 2 && type.getMDimension() == 2) mUniformSetterType = UniformSetterType::Matrix2x2;
                else if (type.getNDimension() == 3 && type.getMDimension() == 3) mUniformSetterType = UniformSetterType::Matrix3x3;
                else if (type.getNDimension() == 4 && type.getMDimension() == 4) mUniformSetterType = UniformSetterType::Matrix4x4;
            }
            else if (type.getNDimension() != -1) // vector
            {
                if (type.getNDimension() == 2) mUniformSetterType = UniformSetterType::Float2Array;
                if (type.getNDimension() == 3) mUniformSetterType = UniformSetterType::Float3Array;
                if (type.getNDimension() == 4) mUniformSetterType = UniformSetterType::Float4Array;
            }
            else // scalar
            {
                mUniformSetterType = UniformSetterType::Float1Array;
            }
        }
        else if (type.getBaseType() == BaseShaderParameterType::Integer || type.getBaseType() == BaseShaderParameterType::Boolean)
        {
            if (type.getNDimension() != -1) // vector
            {
                if (type.getNDimension() == 2) mUniformSetterType = UniformSetterType::Int2Array;
                if (type.getNDimension() == 3) mUniformSetterType = UniformSetterType::Int3Array;
                if (type.getNDimension() == 4) mUniformSetterType = UniformSetterType::Int4Array;
            }
            else // scalar
            {
                mUniformSetterType = UniformSetterType::Int1Array;
            }
        }
        else
        {
            mUniformSetterType = UniformSetterType::TextureArray;
        }
    }

    void ShaderParameterSetterImpl::setValues(const bool *bools)
    {
        for (size_t i = 0; i < mDataSize / 4; ++i)
        {
            mDataI[i] = bools[i];
        }
    }

    void ShaderParameterSetterImpl::setValues(const float *floats)
    {
        memcpy(mData, floats, mDataSize);
    }

    void ShaderParameterSetterImpl::setValues(const int32_t *ints)
    {
        memcpy(mData, ints, mDataSize);
    }

    void ShaderParameterSetterImpl::setValues(const NativeTextureShaderParameterData *textures)
    {
        for (size_t i = 0; i < mDataSize / sizeof(NativeTextureShaderParameterData); ++i)
        {
            mDataT[i] = textures[i];
        }
    }

    ShaderParameterSetterImpl::~ShaderParameterSetterImpl()
    {
        if (mUniformSetterType == UniformSetterType::TextureArray)
        {
            for (size_t i = 0; i < mDataSize / sizeof(NativeTextureShaderParameterData); ++i)
            {
                mDataT[i].~NativeTextureShaderParameterData();
            }
        }

        delete [] mData;
    }
    
    ShaderParameterSetterWrapper::ShaderParameterSetterWrapper(
        const ShaderProgramImpl & shaderProgram, const std::string & name, Graphics::ShaderParameterType type)
        : mImpl(new ShaderParameterSetterImpl(shaderProgram, name, type))
    {
    }

    void ShaderParameterSetterWrapper::setValues(const bool * bools)
    {
        mImpl->setValues(bools);
    }

    void ShaderParameterSetterWrapper::setValues(const float * floats)
    {
        mImpl->setValues(floats);
    }

    void ShaderParameterSetterWrapper::setValues(const int32_t * ints)
    {
        mImpl->setValues(ints);
    }
    
    void ShaderParameterSetterWrapper::setValues(const NativeTextureShaderParameterData * textures)
    {
        mImpl->setValues(textures);
    }
}