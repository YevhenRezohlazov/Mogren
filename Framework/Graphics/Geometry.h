#pragma once

#include "PrimitiveTypes/GeometryType.h"
#include "VertexBuffer.h"
#include <memory>
#include <assert.h>

namespace Graphics
{
    class NativeGeometry;
    class IndexBuffer;
    ///
    /// Class for storing drawable geometry.
    ///
    class Geometry final
    {
    public:
        ///
        /// Initializes a new instance of the Geometry class.
        ///
        /// \param type The geometry type.
        /// \param indexBuffer The index buffer.
        /// \param vertexBuffer The vertex buffer.
        Geometry(
            GeometryType type, 
            std::unique_ptr<IndexBuffer> indexBuffer,
            std::unique_ptr<VertexBufferBase> vertexBuffer);

        ///
        /// Gets the geometry type.
        ///
        GeometryType getType() const;

        ///
        /// Gets the index buffer.
        ///
        const IndexBuffer& getIndexBuffer() const;
        IndexBuffer& getIndexBuffer();

        ///
        /// Gets the vertex buffer.
        ///
        const VertexBufferBase& getVertexBuffer() const;
        VertexBufferBase& getVertexBuffer();

        ///
        /// Gets the vertex buffer.
        ///
        template <typename TVertex>
        const VertexBuffer<TVertex>& getVertexBuffer() const;
        template <typename TVertex>
        VertexBuffer<TVertex>& getVertexBuffer();

        ///
        /// Returns the index of the first element in the index buffer that is to be drawn.
        ///
        int getIndexOffset() const;

        ///
        /// Sets the index of the first element in the index buffer that is to be drawn.
        ///
        void setIndexOffset(int indexOffset);

        ///
        /// Returns the count of the elements in the index buffer that are to be drawn.
        ///
        int getIndexCount() const;

        ///
        /// Sets the count of the elements in the index buffer that are to be drawn.
        ///
        void setIndexCount(int indexCount);

        ///
        /// Gets the native geometry implementation.
        ///
        const NativeGeometry& getNativeGeometry() const;

        ~Geometry();

    private:
        GeometryType mType;
        std::unique_ptr<NativeGeometry> mNativeGeometry;
        std::unique_ptr<IndexBuffer> mIndexBuffer;
        std::unique_ptr<VertexBufferBase> mVertexBuffer;
        int mIndexOffset;
        int mIndexCount;
    };

    template<typename TVertex>
    inline VertexBuffer<TVertex>& Geometry::getVertexBuffer()
    {
        assert(dynamic_cast<VertexBuffer<TVertex>*>(mVertexBuffer.get()) != nullptr);
        return *static_cast<VertexBuffer<TVertex>*>(mVertexBuffer.get());
    }

    template<typename TVertex>
    inline const VertexBuffer<TVertex>& Geometry::getVertexBuffer() const
    {
        assert(dynamic_cast<const VertexBuffer<TVertex>*>(mVertexBuffer.get()) != nullptr);
        return *static_cast<const VertexBuffer<TVertex>*>(mVertexBuffer.get());
    }
}

