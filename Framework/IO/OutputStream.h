#pragma once

#include "Stream.h"

namespace IO
{
    ///
    /// Writable stream
    ///
    class OutputStream : public Stream
    {
    public:
        ///
        /// Returns true, if we can write to the stream
        ///
        virtual bool canWrite() const = 0;

        ///
        /// Writes the data to the stream
        /// \param buffer The buffer with the data to be written
        /// \count Data size (in bytes)
        /// \returns Count of bytes actually written.
        virtual uint32_t write(const void *buffer, uint32_t count) = 0;
    };
}
