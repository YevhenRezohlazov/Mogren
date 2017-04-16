#include "VertexAttributeDesc.h"

namespace Graphics
{
    VertexAttributeDesc::VertexAttributeDesc(
        const std::string& attributeName, VertexAttributeType type, int offset)
        : mAttributeName(attributeName), mType(type), mOffset(offset)
    {
    }

    const std::string & VertexAttributeDesc::getAttributeName() const
    {
        return mAttributeName;
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