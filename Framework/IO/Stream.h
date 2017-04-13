#pragma once

#include <stdint.h>

namespace IO
{
    class Stream
    {
    public:
        ///
        /// Sets current position in the stream
        ///
        virtual void setPosition(uint32_t position) = 0;

        ///
        /// Gets the current position in the stream
        ///
        virtual uint32_t getPosition() const = 0;

        ///
        /// Gets the stream length
        ///
        virtual uint32_t getLength() const = 0;

        virtual ~Stream() = default;
    };
}
