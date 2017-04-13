#include "GLBuffer.h"

namespace Graphics
{
    void GLBuffer::init(bool suppressDeletion)
    {
        GLResource::init(suppressDeletion);
        glGenBuffers(1, &mId);
        CHECK_GL_ERROR();
    }

    void GLBuffer::init(GLuint id, bool suppressDeletion)
    {
        GLResource::init(id, suppressDeletion);
    }

    GLBuffer::GLBuffer()
    {
    }

    void GLBuffer::bind(GLenum target) const
    {
        checkInited();
        glBindBuffer(target, mId);
        CHECK_GL_ERROR();
    }

    void GLBuffer::deleteResource()
    {
        glDeleteBuffers(1, &mId);
        mId = -1;
        CHECK_GL_ERROR();
    }
}