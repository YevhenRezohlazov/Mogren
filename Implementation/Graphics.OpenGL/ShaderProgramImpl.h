#pragma once

#include "GLProgram.h"

#include <Mogren/Framework/Graphics/NativeInterface/NativeShaderProgram.h>
#include <Mogren/Framework/Graphics/PrimitiveTypes/VertexAttributeUsage.h>
#include <string>

namespace IO
{
    class InputStream;
}

namespace Graphics
{
    class ShaderProgramImpl : public NativeShaderProgram
    {
    public:
        explicit ShaderProgramImpl(IO::InputStream & shaderInputStream);

        const GLProgram& getGLProgram() const;

        const GLint getAttributeLocation(Graphics::VertexAttributeUsage attribUsage, int attribUsageIndex) const;

        virtual std::unique_ptr<NativeShaderParameterSet> createParameterSet() const override;

        virtual void finalize() override;

    private:
        static const int VertexAttributeUsageCount = 8;
        static const int VertexAttributeUsageIndexCount = 16;
        static const std::string VertexAttributeUsageNames[VertexAttributeUsageCount];

        GLProgram mGLProgram;
        GLint mAttributeMatrix[VertexAttributeUsageCount][VertexAttributeUsageIndexCount];

        std::string mVertexShader;
        std::string mFragmentShader;
    };
}

