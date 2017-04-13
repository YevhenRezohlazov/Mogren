#include "Geometry.h"
#include "NativeInterface/NativeGeometry.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace Graphics
{
    namespace
    {
        ///
        /// Native geometry interface implementation
        ///
        class NativeGeometryImpl : public NativeGeometry
        {
        private:
            const Geometry &mGeometry;

        public:
            NativeGeometryImpl(const Geometry &geometry) : mGeometry(geometry)
            {
            }

            virtual const NativeIndexBuffer& getIndexBuffer() const override
            {
                return mGeometry.getIndexBuffer().getNativeBuffer();
            }

            virtual const NativeVertexBuffer& getVertexBuffer() const override
            {
                return mGeometry.getVertexBuffer().getNativeBuffer();
            }

            virtual Graphics::GeometryType getType() const override
            {
                return mGeometry.getType();
            }

            virtual int getIndexOffset() const override
            {
                return mGeometry.getIndexOffset();
            }

            virtual int getIndexCount() const override
            {
                return mGeometry.getIndexCount();
            }
        };
    }

    Geometry::Geometry(
        GeometryType type,
        std::unique_ptr<IndexBuffer> indexBuffer,
        std::unique_ptr<VertexBufferBase> vertexBuffer)
    {
        assert(indexBuffer);
        assert(vertexBuffer);

        mType = type;
        mNativeGeometry = std::make_unique<NativeGeometryImpl>(*this);
        mIndexBuffer = std::move(indexBuffer);
        mVertexBuffer = std::move(vertexBuffer);

        mIndexOffset = 0;
        mIndexCount = mIndexBuffer->getItemCount();
    }

    GeometryType Geometry::getType() const
    {
        return mType;
    }

    const IndexBuffer & Geometry::getIndexBuffer() const
    {
        return *mIndexBuffer;
    }

    IndexBuffer & Geometry::getIndexBuffer()
    {
        return *mIndexBuffer;
    }

    const VertexBufferBase& Geometry::getVertexBuffer() const
    {
        return *mVertexBuffer;
    }

    VertexBufferBase& Geometry::getVertexBuffer()
    {
        return *mVertexBuffer;
    }

    const NativeGeometry & Geometry::getNativeGeometry() const
    {
        return *mNativeGeometry;
    }

    Geometry::~Geometry() = default;

    int Geometry::getIndexOffset() const
    {
        return mIndexOffset;
    }

    void Geometry::setIndexOffset(int indexOffset)
    {
        mIndexOffset = indexOffset;
        if (mIndexOffset + mIndexCount > mIndexBuffer->getItemCount())
        {
            mIndexCount = mIndexBuffer->getItemCount() - mIndexOffset;
        }
    }

    int Geometry::getIndexCount() const
    {
        return mIndexCount;
    }

    void Geometry::setIndexCount(int indexCount)
    {
        mIndexCount = indexCount;
        if (mIndexOffset + mIndexCount > mIndexBuffer->getItemCount())
        {
            mIndexCount = mIndexBuffer->getItemCount() - mIndexOffset;
        }
    }
}