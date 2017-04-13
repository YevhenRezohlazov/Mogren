#pragma once

#include "VertexAttributeDesc.h"
#include <vector>

namespace Graphics
{
    ///
    /// Vertex structure description
    ///
    class VertexStructureDesc
    {
    private:
        std::vector<VertexAttributeDesc> mAttributeDescs;

    public:
        ///
        /// Initializes a new empty instance of the VertexStructureDesc class.
        ///
        VertexStructureDesc();

        ///
        /// Initializes a new instance of the VertexStructureDesc class.
        /// \param attrib0 The first vertex attribute description
        ///
        VertexStructureDesc(
            const VertexAttributeDesc& attrib0);

        ///
        /// Initializes a new instance of the VertexStructureDesc class.
        /// \param attrib0 The first vertex attribute description
        /// \param attrib1 The second vertex attribute description
        ///
        VertexStructureDesc(
            const VertexAttributeDesc& attrib0,
            const VertexAttributeDesc& attrib1);

        ///
        /// Initializes a new instance of the VertexStructureDesc class.
        /// \param attrib0 The first vertex attribute description
        /// \param attrib1 The second vertex attribute description
        /// \param attrib2 The third vertex attribute description
        ///
        VertexStructureDesc(
            const VertexAttributeDesc& attrib0,
            const VertexAttributeDesc& attrib1,
            const VertexAttributeDesc& attrib2);

        ///
        /// Initializes a new instance of the VertexStructureDesc class.
        /// \param attrib0 The first vertex attribute description
        /// \param attrib1 The second vertex attribute description
        /// \param attrib2 The third vertex attribute description
        /// \param attrib3 The fourth vertex attribute description
        ///
        VertexStructureDesc(
            const VertexAttributeDesc& attrib0,
            const VertexAttributeDesc& attrib1,
            const VertexAttributeDesc& attrib2,
            const VertexAttributeDesc& attrib3);

        ///
        /// Initializes a new instance of the VertexStructureDesc class.
        /// \param attrib0 The first vertex attribute description
        /// \param attrib1 The second vertex attribute description
        /// \param attrib2 The third vertex attribute description
        /// \param attrib3 The fourth vertex attribute description
        /// \param attrib4 The fifth vertex attribute description
        ///
        VertexStructureDesc(
            const VertexAttributeDesc& attrib0,
            const VertexAttributeDesc& attrib1,
            const VertexAttributeDesc& attrib2,
            const VertexAttributeDesc& attrib3,
            const VertexAttributeDesc& attrib4);

        ///
        /// Initializes a new instance of the VertexStructureDesc class.
        /// \param attribs The vertex attribute descriptions
        ///
        VertexStructureDesc(
            const std::vector<VertexAttributeDesc>& attribs);

        ///
        /// Gets the vertex attribute descriptions
        ///
        const std::vector<VertexAttributeDesc>& getAttributeDescs() const;
    };
}

