#include "GLFramebuffer.h"
#include <Mogren/Framework/Logging/Logger.h>

namespace Graphics
{
    void GLFramebuffer::init(bool suppressDeletion)
    {
        GLResource::init(suppressDeletion);
        glGenFramebuffers(1, &mId);
        CHECK_GL_ERROR();
    }

    void GLFramebuffer::init(GLuint id, bool suppressDeletion)
    {
        GLResource::init(id, suppressDeletion);
    }

    GLFramebuffer::GLFramebuffer()
    {
    }

    void GLFramebuffer::bind(GLenum target /*= GL_FRAMEBUFFER*/) const
    {
        checkInited();
        glBindFramebuffer(target, mId);
        CHECK_GL_ERROR();
    }

    void GLFramebuffer::reload()
    {
        if (mId != 0)
            Logging::Logger::writeError("Cannot reload ramebuffer");
    }

    void GLFramebuffer::deleteResource()
    {
        glDeleteFramebuffers(1, &mId);
        mId = -1;
        CHECK_GL_ERROR();
    }
}