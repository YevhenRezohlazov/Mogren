#pragma once

#include "PrimitiveTypes/VertexStructureDesc.h"
#include <memory>

namespace Graphics
{
    class NativeVertexBuffer;

    ///
    /// Vertex data buffer.
    ///
    class VertexBufferBase
    {
    public:
        ///
        /// Initializes a new instance of the VertexBuffer class.
        ///
        /// \param itemsType Type of the buffer elements.
        /// \param itemCount The count of elements in this buffer.
        /// \param isDynamic Set to true if buffer data will be updated frequently.
        VertexBufferBase(
            uint32_t itemSize, uint32_t itemCount,
            const VertexStructureDesc& vertexStructureDesc, bool isDynamic = false);

        ///
        /// Gets the NativeVertexBuffer instance.
        ///
        const NativeVertexBuffer& getNativeBuffer() const;

        ///
        /// Gets the buffer item count.
        ///
        uint32_t getVertexCount() const;

        ///
        /// Gets a value indicating whether this buffer is dynamic.
        ///
        bool isDynamic() const;

        ///
        /// Gets the vertex structure description
        ///
        virtual const VertexStructureDesc& getVertexStructureDesc() const = 0;

        ///
        /// Gets the vertex structure size in bytes
        ///
        virtual uint32_t getVertexStructureSize() const = 0;

        void setRawData(const void *data, uint32_t dataSize, uint32_t offset);

        virtual ~VertexBufferBase();

    private:
        std::unique_ptr<NativeVertexBuffer> mNativeBuffer;
        uint32_t mVertexCount;
        bool mIsDynamic;
    };
}

