#pragma once

#include "GLProgram.h"

#include <Mogren/Framework/Graphics/NativeInterface/NativeShaderProgram.h>
#include <string>
#include <unordered_map>

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

        GLint getAttributeLocation(const std::string & attribName) const;

        virtual std::unique_ptr<NativeShaderParameterSet> createParameterSet() const override;

        virtual void finalize() override;

    private:
        GLProgram mGLProgram;
        std::unordered_map<std::string, GLint> mAttributesMap;

        std::string mVertexShader;
        std::string mFragmentShader;
    };
}

