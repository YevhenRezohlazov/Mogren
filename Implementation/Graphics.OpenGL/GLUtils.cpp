#include "GLUtils.h"
#include "GLInclude.h"

#include <Mogren/Framework/Logging/Logger.h>
#include <assert.h>

namespace Graphics
{
    void checkGLError(const char *fileName, int line)
    {
        GLenum errCode;
        std::string errString;
        errCode = glGetError();

        if (errCode != GL_NO_ERROR)
        {
            switch (errCode)
            {
            case GL_INVALID_ENUM: errString = "Invalid enum"; break;
            case GL_INVALID_VALUE: errString = "Invalid value"; break;
            case GL_INVALID_OPERATION: errString = "Invalid operation"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: errString = "Invalid framebuffer operation"; break;
            case GL_OUT_OF_MEMORY: errString = "Out of memory"; break;
            }

            Logging::Logger::writeWarning("OpenGL error at %s:%d: %s", fileName, line, errString.c_str());
            assert(false && "OpenGL error. See log for details.");
        }
    }
}