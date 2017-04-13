#pragma once

#include "Stream.h"

namespace IO
{
    ///
    /// Stream with data that can be read
    ///
    class InputStream : public Stream
    {
    public:
        ///
        /// Returns true, if we can read from the stream
        ///
        virtual bool canRead() const = 0;

        ///
        /// Reads the data from the stream to the buffer
        /// \param buffer The buffer where the data will be stored
        /// \count Data size to be read (in bytes)
        /// \returns Count of bytes actually read.
        virtual uint32_t read(void *buffer, uint32_t size) = 0;
    };
}
