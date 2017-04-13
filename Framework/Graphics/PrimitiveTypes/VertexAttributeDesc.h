#pragma once

#include "VertexAttributeType.h"
#include "VertexAttributeUsage.h"

namespace Graphics
{
    ///
    /// Vertex attribute description
    ///
    class VertexAttributeDesc
    {
    private:
        VertexAttributeUsage mUsage;
        int mUsageIndex;
        VertexAttributeType mType;
        int mOffset;

    public:
        ///
        /// Initializes a new instance of VertexAttributeDesc class.
        /// \param usage Vertex attribute usage
        /// \param usageIndex Vertex attribute usage index (such as 2 for POSITION2 or 0 for COLOR0 or just COLOR)
        /// \param type Vertex attribute type
        /// \param offset Offset of the attribute data in the vertex structure
        ///
        VertexAttributeDesc(VertexAttributeUsage usage, int usageIndex, VertexAttributeType type, int offset);

        ///
        /// Gets the vertex attribute usage
        ///
        VertexAttributeUsage getUsage() const;

        ///
        /// Gets the vertex attribute usage index (such as 2 for POSITION2 or 0 for COLOR0 or just COLOR)
        ///
        int getUsageIndex() const;

        ///
        /// Gets the vertex attribute type
        ///
        VertexAttributeType getType() const;

        ///
        /// Gets the offset of the attribute data in the vertex structure
        ///
        int getOffset() const;
    };
}

