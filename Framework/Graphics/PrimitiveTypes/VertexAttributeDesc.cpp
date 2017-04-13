#include "VertexAttributeDesc.h"

namespace Graphics
{
    VertexAttributeDesc::VertexAttributeDesc(
        VertexAttributeUsage usage, int usageIndex, VertexAttributeType type, int offset)
        : mUsage(usage), mUsageIndex(usageIndex), mType(type), mOffset(offset)
    {
    }

    Graphics::VertexAttributeUsage VertexAttributeDesc::getUsage() const
    {
        return mUsage;
    }

    int VertexAttributeDesc::getUsageIndex() const
    {
        return mUsageIndex;
    }

    Graphics::VertexAttributeType VertexAttributeDesc::getType() const
    {
        return mType;
    }

    int VertexAttributeDesc::getOffset() const
    {
        return mOffset;
    }
}