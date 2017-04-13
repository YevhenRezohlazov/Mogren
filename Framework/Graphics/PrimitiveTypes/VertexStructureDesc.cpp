#include "VertexStructureDesc.h"

namespace Graphics
{
    VertexStructureDesc::VertexStructureDesc(const VertexAttributeDesc& attrib0)
    {
        mAttributeDescs.push_back(attrib0);
    }

    VertexStructureDesc::VertexStructureDesc(const VertexAttributeDesc& attrib0, const VertexAttributeDesc& attrib1)
    {
        mAttributeDescs.push_back(attrib0);
        mAttributeDescs.push_back(attrib1);
    }

    VertexStructureDesc::VertexStructureDesc(const VertexAttributeDesc& attrib0, const VertexAttributeDesc& attrib1, const VertexAttributeDesc& attrib2)
    {
        mAttributeDescs.push_back(attrib0);
        mAttributeDescs.push_back(attrib1);
        mAttributeDescs.push_back(attrib2);
    }

    VertexStructureDesc::VertexStructureDesc(const VertexAttributeDesc& attrib0, const VertexAttributeDesc& attrib1, const VertexAttributeDesc& attrib2, const VertexAttributeDesc& attrib3)
    {
        mAttributeDescs.push_back(attrib0);
        mAttributeDescs.push_back(attrib1);
        mAttributeDescs.push_back(attrib2);
        mAttributeDescs.push_back(attrib3);
    }

    VertexStructureDesc::VertexStructureDesc(const VertexAttributeDesc& attrib0, const VertexAttributeDesc& attrib1, const VertexAttributeDesc& attrib2, const VertexAttributeDesc& attrib3, const VertexAttributeDesc& attrib4)
    {
        mAttributeDescs.push_back(attrib0);
        mAttributeDescs.push_back(attrib1);
        mAttributeDescs.push_back(attrib2);
        mAttributeDescs.push_back(attrib3);
        mAttributeDescs.push_back(attrib4);
    }

    VertexStructureDesc::VertexStructureDesc(const std::vector<VertexAttributeDesc>& attribs)
        : mAttributeDescs(attribs)
    {
    }

    VertexStructureDesc::VertexStructureDesc()
    {
    }

    const std::vector<VertexAttributeDesc>& VertexStructureDesc::getAttributeDescs() const
    {
        return mAttributeDescs;
    }
}