#pragma once

#include "GLResource.h"

namespace Graphics
{
    ///
    /// OpenGL buffer wrapper
    ///
    class GLBuffer : public GLResource
    {
    private:
        // disallow copying
        GLBuffer(const GLBuffer&);
        GLBuffer& operator=(const GLBuffer&);

    public:
        GLBuffer();

        void init(bool suppressDeletion = false);

        void init(GLuint id, bool suppressDeletion = false);

        void bind(GLenum target) const;

    protected:
        void deleteResource();
    };
}

