#pragma once

#include "VertexAttributeType.h"
#include <string>

namespace Graphics
{
    ///
    /// Vertex attribute description
    ///
    class VertexAttributeDesc
    {
    private:
        std::string mAttributeName;
        int mUsageIndex;
        VertexAttributeType mType;
        int mOffset;

    public:
        ///
        /// Initializes a new instance of VertexAttributeDesc class.
        /// \param attributeName Vertex attribute name
        /// \param type Vertex attribute type
        /// \param offset Offset of the attribute data in the vertex structure
        ///
        VertexAttributeDesc(const std::string& attributeName, VertexAttributeType type, int offset);

        ///
        /// Gets the vertex attribute name
        ///
        const std::string& getAttributeName() const;
        
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

