#pragma once

#include <stdint.h>

namespace Graphics
{
    ///
    /// Native graphical data buffer interface.
    ///
    class NativeVertexBuffer
    {
    public:
        ///
        /// Sets the data to the buffer.
        ///
        /// \param data The pointer to the data to be written to the buffer.
        /// \param dataSize The size of the data (in bytes).
        /// \param offset Offset in the buffer where the data should be written.
        virtual void setData(const void *data, uint32_t dataSize, uint32_t offset) = 0;

        virtual ~NativeVertexBuffer() = default;
    };
}

