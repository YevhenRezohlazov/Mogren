#include "GLProgram.h"
#include <Mogren/Framework/Logging/Logger.h>

#ifdef __ANDROID__
#define SHADERS_VERSION_STRING ""
#else
#define SHADERS_VERSION_STRING "#version 400\n"
#endif

namespace Graphics
{
    bool GLProgram::init(
        const std::string &vertexShaderCode,
        const std::string &fragmentShaderCode)
    {
        GLResource::init(false);

        GLuint vertexShader, fragmentShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        CHECK_GL_ERROR();

        auto vertexShaderCodeWithVersion = SHADERS_VERSION_STRING + vertexShaderCode;
        const GLchar *shaderCodeStr = reinterpret_cast<const GLchar*>(
                    vertexShaderCodeWithVersion.c_str());
        GLint shaderCodeLen = vertexShaderCodeWithVersion.size();
        glShaderSource(vertexShader, 1, &shaderCodeStr, &shaderCodeLen);
        CHECK_GL_ERROR();

        auto fragmentShaderCodeWithVersion = SHADERS_VERSION_STRING + fragmentShaderCode;
        shaderCodeStr = reinterpret_cast<const GLchar*>(fragmentShaderCodeWithVersion.c_str());
        shaderCodeLen = fragmentShaderCodeWithVersion.size();
        glShaderSource(fragmentShader, 1, &shaderCodeStr, &shaderCodeLen);
        CHECK_GL_ERROR();

        // compile vertex shader
        {
            GLint compiled = GL_FALSE;
            int logLength;

            glCompileShader(vertexShader);
            CHECK_GL_ERROR();
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);

            std::string logMessages;

            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);

            if (logLength > 0)
            {
                logMessages.resize(logLength);
                glGetShaderInfoLog(vertexShader, logLength, nullptr, const_cast<char*>(logMessages.c_str()));
            }

            Logging::Logger::writeInfo("Compiling vertex shader:\n%s", logMessages.c_str());

            if (!compiled)
            {
                Logging::Logger::writeError("Can't compile vertex shader.");
                glDeleteShader(vertexShader);
                glDeleteShader(fragmentShader);
                return false;
            }
        }

        // compile fragment shader
        {
            GLint compiled = GL_FALSE;
            int logLength;

            glCompileShader(fragmentShader);
            CHECK_GL_ERROR();
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);

            std::string logMessages;

            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);

            if (logLength > 0)
            {
                logMessages.resize(logLength);
                glGetShaderInfoLog(fragmentShader, logLength, NULL, const_cast<char*>(logMessages.c_str()));
            }

            Logging::Logger::writeInfo("Compiling fragment shader:\n%s", logMessages.c_str());

            if (!compiled)
            {
                Logging::Logger::writeError("Can't compile fragment shader.");
                glDeleteShader(vertexShader);
                glDeleteShader(fragmentShader);
                return false;
            }
        }

        mId = glCreateProgram();
        CHECK_GL_ERROR();

        glAttachShader(mId, vertexShader);
        glAttachShader(mId, fragmentShader);
        CHECK_GL_ERROR();

        // link program
        {
            glLinkProgram(mId);
            CHECK_GL_ERROR();

            GLint linked = GL_FALSE;
            int logLength;

            glGetProgramiv(mId, GL_LINK_STATUS, &linked);

            std::string logMessages;

            glGetProgramiv(mId, GL_INFO_LOG_LENGTH, &logLength);

            if (logLength > 0)
            {
                logMessages.resize(logLength);
                glGetProgramInfoLog(mId, logLength, NULL, const_cast<char*>(logMessages.c_str()));
            }

            Logging::Logger::writeInfo("Linking shader:\n%s", logMessages.c_str());

            if (!linked)
            {
                Logging::Logger::writeError("Can't link shader.");
                glDeleteShader(vertexShader);
                glDeleteShader(fragmentShader);
                return false;
            }
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return true;
    }

    void GLProgram::init(GLuint id, bool suppressDeletion)
    {
        GLResource::init(id, suppressDeletion);
    }

    GLProgram::GLProgram()
    {
    }

    void GLProgram::use() const
    {
        checkInited();
        glUseProgram(mId);
        CHECK_GL_ERROR();
    }

    void GLProgram::deleteResource()
    {
        glDeleteProgram(mId);
        CHECK_GL_ERROR();
        mId = (GLuint)-1;
    }

    GLint GLProgram::getUniformLocation(const std::string &uniformName) const
    {
        checkInited();
        const auto result = glGetUniformLocation(mId, uniformName.c_str());
        CHECK_GL_ERROR();
        return result;
    }

    std::unordered_map<std::string, GLint> GLProgram::getVertexAttributes() const
    {
        std::unordered_map<std::string, GLint> res;

        GLint countAttributes;
        glGetProgramiv(mId, GL_ACTIVE_ATTRIBUTES, &countAttributes);

        GLchar nameBuf[101];

        for (GLint i = 0; i < countAttributes; ++i)
        {
            GLsizei bufLen;
            GLint size;
            GLenum type;
            glGetActiveAttrib(mId, i, 100, &bufLen, &size, &type, nameBuf);
            CHECK_GL_ERROR();

            nameBuf[bufLen] = 0;

            GLint location = glGetAttribLocation(mId, nameBuf);
            CHECK_GL_ERROR();

            res[nameBuf] = location;
        }

        return res;
    }
}
