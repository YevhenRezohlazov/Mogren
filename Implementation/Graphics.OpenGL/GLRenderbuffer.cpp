#include "GLRenderbuffer.h"
#include <Mogren/Framework/Logging/Logger.h>

namespace Graphics
{
    void GLRenderbuffer::init(bool suppressDeletion)
    {
        GLResource::init(suppressDeletion);
        glGenRenderbuffers(1, &mId);
        CHECK_GL_ERROR();
    }

    void GLRenderbuffer::init(GLuint id, bool suppressDeletion)
    {
        GLResource::init(id, suppressDeletion);
    }

    GLRenderbuffer::GLRenderbuffer()
    {
    }

    void GLRenderbuffer::bind(GLenum target /*= GL_RENDERBUFFER */) const
    {
        checkInited();
        glBindRenderbuffer(target, mId);
        CHECK_GL_ERROR();
    }

    void GLRenderbuffer::reload()
    {
        Logging::Logger::writeError("Cannot reload renderbuffers");
    }

    void GLRenderbuffer::deleteResource()
    {
        glDeleteRenderbuffers(1, &mId);
        mId = -1;
        CHECK_GL_ERROR();
    }
}