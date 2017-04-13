#include "IndexBufferImpl.h"

namespace Graphics
{
    void IndexBufferImpl::setData(const uint16_t *data, uint32_t dataSize, uint32_t offset)
    {
        mGLBuffer.bind(GL_ELEMENT_ARRAY_BUFFER);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, dataSize, data);
        CHECK_GL_ERROR();
    }

    IndexBufferImpl::IndexBufferImpl(uint32_t countElems, bool isDynamic)
    {
        mCountElems = countElems;

        mGLBuffer.init();
        mGLBuffer.bind(GL_ELEMENT_ARRAY_BUFFER);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * countElems, nullptr, isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        CHECK_GL_ERROR();
    }

    const GLBuffer& IndexBufferImpl::getGLBuffer() const
    {
        return mGLBuffer;
    }

    const uint32_t& IndexBufferImpl::getIndexCount() const
    {
        return mCountElems;
    }

    void IndexBufferImpl::bind() const
    {
        mGLBuffer.bind(GL_ELEMENT_ARRAY_BUFFER);
    }
}