#pragma once

#include "GLResource.h"

namespace Graphics
{
    ///
    /// OpenGL renderbuffer wrapper
    ///
    class GLRenderbuffer : public GLResource
    {
    private:
        // disallow copying
        GLRenderbuffer(const GLRenderbuffer&);
        GLRenderbuffer& operator=(const GLRenderbuffer&);

    public:
        GLRenderbuffer();

        void init(bool suppressDeletion = false);

        void init(GLuint id, bool suppressDeletion = false);

        void bind(GLenum target = GL_RENDERBUFFER) const;

        virtual void reload();

    protected:
        void deleteResource();
    };
}

