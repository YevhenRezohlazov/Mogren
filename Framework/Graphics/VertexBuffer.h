#pragma once

#include "VertexBufferBase.h"
#include <Mogren/Framework/Math/Functions.h>

namespace Graphics
{
    ///
    /// Vertex data buffer.
    ///
    template <typename TVertex>
    class VertexBuffer final : public VertexBufferBase
    {
    public:
        ///
        /// Initializes a new instance of the VertexBuffer class.
        ///
        /// \param vertexCount The count of vertices in this buffer.
        /// \param isDynamic Set to true if buffer data will be updated frequently.
        explicit VertexBuffer(uint32_t vertexCount, bool isDynamic = false);

        ///
        /// Sets the data to the buffer.
        ///
        /// \param vertices The array of the vertices to be written to the buffer.
        /// \param countVertices Count of the vertices to be written to the buffer.
        /// \param bufferOffset Index of the vertex in the buffer where the data should be written.
        void setData(const TVertex * const vertices, uint32_t countVertices, uint32_t bufferOffset = 0);

        ///
        /// Gets the vertex structure description
        ///
        virtual const VertexStructureDesc& getVertexStructureDesc() const;

        ///
        /// Gets the vertex structure size in bytes
        ///
        virtual uint32_t getVertexStructureSize() const;
    };

    template<typename TVertex>
    inline VertexBuffer<TVertex>::VertexBuffer(uint32_t vertexCount, bool isDynamic)
        : VertexBufferBase(getVertexStructureSize(), vertexCount, getVertexStructureDesc(), isDynamic)
    {
    }

    template<typename TVertex>
    inline void VertexBuffer<TVertex>::setData(const TVertex * const vertices, uint32_t countVertices, uint32_t bufferOffset)
    {
        setRawData(
            vertices,
            (Math::minimum(bufferOffset + countVertices, getVertexCount()) - bufferOffset) * getVertexStructureSize(),
            bufferOffset * getVertexStructureSize());
    }

    template<typename TVertex>
    inline const VertexStructureDesc & VertexBuffer<TVertex>::getVertexStructureDesc() const
    {
        return TVertex::getStructureDesc();
    }

    template<typename TVertex>
    inline uint32_t VertexBuffer<TVertex>::getVertexStructureSize() const
    {
        return sizeof(TVertex);
    }
}
