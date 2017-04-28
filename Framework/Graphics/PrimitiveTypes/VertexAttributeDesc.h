#pragma once

#include "VertexAttributeType.h"
#include <string>
#include <Mogren/Framework/Math/Vector.h>
#include <Mogren/Framework/Math/Vector2D.h>
#include <Mogren/Framework/Math/Vector3D.h>
#include <Mogren/Framework/Math/Vector4D.h>
#include <Mogren/Framework/Graphics/PrimitiveTypes/Color.h>

namespace Graphics
{
    ///
    /// Vertex attribute description
    ///
    class VertexAttributeDesc
    {
    private:
        std::string mAttributeName;
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

    template <typename TAttrType> VertexAttributeType getVertexAttributeType();

    template <> inline VertexAttributeType getVertexAttributeType<int8_t>() { return VertexAttributeType::Byte; }
    template <> inline VertexAttributeType getVertexAttributeType<Math::Vector<int8_t, 2>>() { return VertexAttributeType::ByteVector2; }
    template <> inline VertexAttributeType getVertexAttributeType<Math::Vector<int8_t, 3>>() { return VertexAttributeType::ByteVector3; }
    template <> inline VertexAttributeType getVertexAttributeType<Math::Vector<int8_t, 4>>() { return VertexAttributeType::ByteVector4; }

    template <> inline VertexAttributeType getVertexAttributeType<uint8_t>() { return VertexAttributeType::UByte; }
    template <> inline VertexAttributeType getVertexAttributeType<Math::Vector<uint8_t, 2>>() { return VertexAttributeType::UByteVector2; }
    template <> inline VertexAttributeType getVertexAttributeType<Math::Vector<uint8_t, 3>>() { return VertexAttributeType::UByteVector3; }
    template <> inline VertexAttributeType getVertexAttributeType<Math::Vector<uint8_t, 4>>() { return VertexAttributeType::UByteVector4; }

    template <> inline VertexAttributeType getVertexAttributeType<int16_t>() { return VertexAttributeType::Short; }
    template <> inline VertexAttributeType getVertexAttributeType<Math::Vector<int16_t, 2>>() { return VertexAttributeType::ShortVector2; }
    template <> inline VertexAttributeType getVertexAttributeType<Math::Vector<int16_t, 3>>() { return VertexAttributeType::ShortVector3; }
    template <> inline VertexAttributeType getVertexAttributeType<Math::Vector<int16_t, 4>>() { return VertexAttributeType::ShortVector4; }

    template <> inline VertexAttributeType getVertexAttributeType<uint16_t>() { return VertexAttributeType::UShort; }
    template <> inline VertexAttributeType getVertexAttributeType<Math::Vector<uint16_t, 2>>() { return VertexAttributeType::UShortVector2; }
    template <> inline VertexAttributeType getVertexAttributeType<Math::Vector<uint16_t, 3>>() { return VertexAttributeType::UShortVector3; }
    template <> inline VertexAttributeType getVertexAttributeType<Math::Vector<uint16_t, 4>>() { return VertexAttributeType::UShortVector4; }

    template <> inline VertexAttributeType getVertexAttributeType<float>() { return VertexAttributeType::Float; }
    template <> inline VertexAttributeType getVertexAttributeType<Math::Vector2DF>() { return VertexAttributeType::FloatVector2; }
    template <> inline VertexAttributeType getVertexAttributeType<Math::Vector3DF>() { return VertexAttributeType::FloatVector3; }
    template <> inline VertexAttributeType getVertexAttributeType<Math::Vector4DF>() { return VertexAttributeType::FloatVector4; }

    template <> inline VertexAttributeType getVertexAttributeType<Graphics::Color>() { return VertexAttributeType::Color; }
}

#define FIELD_TYPE_AND_OFFSET(VertexType, FieldName) getVertexAttributeType<decltype(((VertexType*)(nullptr))->FieldName)>(), (int)&((VertexType*)(nullptr))->FieldName

