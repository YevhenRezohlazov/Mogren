#pragma once

#include "GLResource.h"
#include <unordered_map>
#include <string>

namespace Graphics
{
    ///
    /// OpenGL shader wrapper
    ///
    class GLProgram : public GLResource
    {
    public:
        GLProgram();

        // disallow copying
        GLProgram(const GLProgram&) = delete;
        GLProgram& operator=(const GLProgram&) = delete;

        bool init(
            const std::string &vertexShaderCode,
            const std::string &fragmentShaderCode);

        void use() const;

        GLint getUniformLocation(const std::string &uniformName) const;

        ///
        /// Gets map of the vertex attributes (location -> name)
        ///
        std::unordered_map<std::string, GLint> getVertexAttributes() const;

        virtual void reload() override;

    protected:
        void deleteResource();

    private:
        std::string mVertexShaderCode;
        std::string mFragmentShaderCode;
    };
}

