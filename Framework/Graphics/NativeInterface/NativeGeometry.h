#pragma once

#include "NativeIndexBuffer.h"
#include "NativeVertexBuffer.h"

#include "../PrimitiveTypes/GeometryType.h"

namespace Graphics
{
    class NativeGeometry
    {
    public:
        virtual const NativeIndexBuffer& getIndexBuffer() const = 0;

        virtual const NativeVertexBuffer& getVertexBuffer() const = 0;

        virtual GeometryType getType() const = 0;

        ///
        /// Returns the index of the first element in the index buffer that is to be drawn.
        ///
        virtual int getIndexOffset() const = 0;

        ///
        /// Returns the count of the elements in the index buffer that are to be drawn.
        ///
        virtual int getIndexCount() const = 0;

        virtual ~NativeGeometry() = default;
    };
}
