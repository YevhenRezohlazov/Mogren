#include "VertexBufferBase.h"
#include <Mogren/Framework/Common/ImplementationProvider.h>
#include "NativeInterface/NativeGraphicsInterface.h"
#include "NativeInterface/NativeVertexBuffer.h"
#include <assert.h>

namespace Graphics
{
    VertexBufferBase::VertexBufferBase(
        uint32_t itemSize, uint32_t itemCount, 
        const VertexStructureDesc& vertexStructureDesc, bool isDynamic /*= false*/)
    {
        mVertexCount = itemCount;
        mIsDynamic = isDynamic;
        mNativeBuffer = Common::getImpl<NativeGraphicsInterface>().createVertexBuffer(
            vertexStructureDesc, itemSize, itemCount, isDynamic);
        assert(mNativeBuffer != nullptr);
    }

    const NativeVertexBuffer& VertexBufferBase::getNativeBuffer() const
    {
        return *mNativeBuffer;
    }

    uint32_t VertexBufferBase::getVertexCount() const
    {
        return mVertexCount;
    }

    bool VertexBufferBase::isDynamic() const
    {
        return mIsDynamic;
    }

    void VertexBufferBase::setRawData(const void * data, uint32_t dataSize, uint32_t offset)
    {
        mNativeBuffer->setData(data, dataSize, offset);
    }

    VertexBufferBase::~VertexBufferBase() = default;
}