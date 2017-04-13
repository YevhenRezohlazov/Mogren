#pragma once

#include "GLResource.h"
#include <unordered_map>

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

        void init(GLuint id, bool suppressDeletion = false);

        bool init(
            const std::string &vertexShaderCode,
            const std::string &fragmentShaderCode);

        void use() const;

        GLint getUniformLocation(const std::string &uniformName) const;

        ///
        /// Gets map of the vertex attributes (location -> name)
        ///
        std::unordered_map<std::string, GLint> getVertexAttributes() const;

    protected:
        void deleteResource();
    };
}

