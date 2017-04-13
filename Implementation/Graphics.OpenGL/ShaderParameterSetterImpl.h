#pragma once

#include "GLInclude.h"
#include <Mogren/Framework/Graphics/NativeInterface/NativeShaderParameterSetter.h>
#include <Mogren/Framework/Graphics/PrimitiveTypes/ShaderParameterType.h>
#include <memory>
#include <string>

namespace Graphics
{
    enum class UniformSetterType
    {
        Float1Array,
        Float2Array,
        Float3Array,
        Float4Array,

        Int1Array,
        Int2Array,
        Int3Array,
        Int4Array,

        Matrix2x2,
        Matrix3x3,
        Matrix4x4,

        TextureArray
    };

    class ShaderParameterSetterImpl;
    class NativeTextureShaderParameterData;
    class ShaderProgramImpl;

    class ShaderParameterSetterWrapper : public NativeShaderParameterSetter
    {
    public:
        ShaderParameterSetterWrapper(
            const ShaderProgramImpl &shaderProgram, const std::string& name, Graphics::ShaderParameterType type);

        virtual void setValues(const bool *bools) override;

        virtual void setValues(const float *floats) override;

        virtual void setValues(const int32_t *ints) override;

        virtual void setValues(const NativeTextureShaderParameterData *textures) override;

        std::shared_ptr<ShaderParameterSetterImpl> mImpl;
    };

    class ShaderParameterSetterImpl
    {
    public:
        ShaderParameterSetterImpl(
            const ShaderProgramImpl &shaderProgram, const std::string& name, Graphics::ShaderParameterType type);

        virtual void setValues(const bool *bools);

        virtual void setValues(const float *floats);

        virtual void setValues(const int32_t *ints);

        virtual void setValues(const NativeTextureShaderParameterData *textures);

        ~ShaderParameterSetterImpl();

    public:
        GLint mUniformLocation;

        uint32_t mDataSize;

        union
        {
            char *mData;
            float *mDataF;
            int32_t *mDataI;
            NativeTextureShaderParameterData *mDataT;
        };

        UniformSetterType mUniformSetterType;
    };
}

