#include "GLBuffer.h"

namespace Graphics
{
    void GLBuffer::init(bool isDynamic, bool suppressDeletion)
    {
        GLResource::init(suppressDeletion);
        glGenBuffers(1, &mId);
        CHECK_GL_ERROR();
        mIsDynamic = isDynamic;
    }

    void GLBuffer::init(GLuint id, bool isDynamic, bool suppressDeletion)
    {
        GLResource::init(id, suppressDeletion);
        mIsDynamic = isDynamic;
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

    void GLBuffer::reload()
    {
        glDeleteBuffers(1, &mId);
        glGetError(); // Ignore error
        mId = -1;
        mInited = false;

        init(mIsDynamic, false);
        bind(GL_ELEMENT_ARRAY_BUFFER);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            mData.size(),
            mData.empty() ? nullptr : &mData.front(),
            mIsDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        CHECK_GL_ERROR();
    }

    std::vector<uint8_t>& GLBuffer::getData()
    {
        return mData;
    }

    void GLBuffer::deleteResource()
    {
        glDeleteBuffers(1, &mId);
        mId = -1;
        CHECK_GL_ERROR();
    }
}