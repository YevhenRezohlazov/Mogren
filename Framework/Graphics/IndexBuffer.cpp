#include "IndexBuffer.h"
#include <Mogren/Framework/Common/ImplementationProvider.h>
#include "NativeInterface/NativeGraphicsInterface.h"
#include "NativeInterface/NativeIndexBuffer.h"

namespace Graphics
{
    IndexBuffer::IndexBuffer(uint32_t itemCount, bool isDynamic /*= false*/)
    {
        mItemCount = itemCount;
        mIsDynamic = isDynamic;
        mNativeBuffer = Common::getImpl<NativeGraphicsInterface>().createIndexBuffer(itemCount, isDynamic);
    }

    const NativeIndexBuffer& IndexBuffer::getNativeBuffer() const
    {
        return *mNativeBuffer;
    }

    int IndexBuffer::getItemCount() const
    {
        return mItemCount;
    }

    bool IndexBuffer::isDynamic() const
    {
        return mIsDynamic;
    }

    void IndexBuffer::setData(const uint16_t *items, uint32_t countItems, uint32_t bufferOffset /*= 0*/)
    {
        const uint32_t totalSize = sizeof(uint16_t) * mItemCount;
        const uint32_t dataSize = countItems * sizeof(uint16_t);
        const uint32_t offset = bufferOffset * sizeof(uint16_t);

        mNativeBuffer->setData(items, Math::minimum(offset + dataSize, totalSize) - offset, offset);
    }

    IndexBuffer::~IndexBuffer() = default;
}