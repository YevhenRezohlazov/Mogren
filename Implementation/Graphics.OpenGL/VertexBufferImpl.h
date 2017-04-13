#pragma once

#include <Mogren/Framework/Graphics/NativeInterface/NativeVertexBuffer.h>
#include <Mogren/Framework/Graphics/PrimitiveTypes/VertexStructureDesc.h>
#include "GLBuffer.h"

namespace Graphics
{
    class VertexBufferImpl : public NativeVertexBuffer
    {
    public:
        VertexBufferImpl(
            const Graphics::VertexStructureDesc &vertexStructureDesc,
            uint32_t vertexStructureSize,
            uint32_t countElems,
            bool isDynamic);
        
        const GLBuffer& getGLBuffer() const;

        const Graphics::VertexStructureDesc& getVertexStructureDesc() const;

        uint32_t getVertexStructureSize() const;

        virtual void setData(const void *data, uint32_t dataSize, uint32_t offset);

        void bind() const;

    private:
        GLBuffer mGLBuffer;
        uint32_t mVertexStructureSize;
        VertexStructureDesc mVertexStructureDesc;
    };
}

