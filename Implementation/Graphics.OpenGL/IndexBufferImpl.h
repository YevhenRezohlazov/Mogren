#pragma once

#include <Mogren/Framework/Graphics/NativeInterface/NativeIndexBuffer.h>
#include "GLBuffer.h"
#include <stdint.h>
#include <vector>

namespace Graphics
{
    class IndexBufferImpl : public NativeIndexBuffer
    {
    public:
        IndexBufferImpl(uint32_t countElems, bool isDynamic);

        const GLBuffer& getGLBuffer() const;

        const uint32_t& getIndexCount() const;

        virtual void setData(const uint16_t *data, uint32_t dataSize, uint32_t offset);

        void bind() const;

    private:
        GLBuffer mGLBuffer;
        uint32_t mCountElems;
    };
}

