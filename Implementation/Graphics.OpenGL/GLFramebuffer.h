#pragma once

#include "GLResource.h"

namespace Graphics
{
    ///
    /// OpenGL framebuffer wrapper
    ///
    class GLFramebuffer : public GLResource
    {
    private:
        // disallow copying
        GLFramebuffer(const GLFramebuffer&);
        GLFramebuffer& operator=(const GLFramebuffer&);

    public:
        GLFramebuffer();

        void init(bool suppressDeletion = false);

        void init(GLuint id, bool suppressDeletion = false);

        void bind(GLenum target = GL_FRAMEBUFFER) const;

        virtual void reload() override;

    protected:
        void deleteResource();
    };
}

