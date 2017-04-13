#include "VertexBufferImpl.h"

namespace Graphics
{
    void VertexBufferImpl::setData(const void *data, uint32_t dataSize, uint32_t offset)
    {
        mGLBuffer.bind(GL_ARRAY_BUFFER);
        glBufferSubData(GL_ARRAY_BUFFER, offset, dataSize, data);
        CHECK_GL_ERROR();
    }

    VertexBufferImpl::VertexBufferImpl(
        const Graphics::VertexStructureDesc &vertexStructureDesc,
        uint32_t vertexStructureSize,
        uint32_t countElems,
        bool isDynamic)
    {
        mVertexStructureSize = vertexStructureSize;
        mVertexStructureDesc = vertexStructureDesc;

        mGLBuffer.init();
        mGLBuffer.bind(GL_ARRAY_BUFFER);
        glBufferData(GL_ARRAY_BUFFER, vertexStructureSize * countElems, nullptr, isDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        CHECK_GL_ERROR();
    }

    const GLBuffer& VertexBufferImpl::getGLBuffer() const
    {
        return mGLBuffer;
    }

    void VertexBufferImpl::bind() const
    {
        mGLBuffer.bind(GL_ARRAY_BUFFER);
    }

    const Graphics::VertexStructureDesc& VertexBufferImpl::getVertexStructureDesc() const
    {
        return mVertexStructureDesc;
    }

    uint32_t VertexBufferImpl::getVertexStructureSize() const
    {
        return mVertexStructureSize;
    }
}