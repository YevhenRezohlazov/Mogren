#pragma once

#include "NativeSound.h"
#include <Mogren/Framework/IO/InputStream.h>
#include <memory>

namespace Audio
{
    class NativeAudioInterface
    {
    public:
        ///
        /// Creates new sound player for given sound data
        /// \param stream The stream with sound data.
        /// \param dataLength The sound data length in the stream
        /// \returns Native sound player instance
        ///
        virtual std::unique_ptr<NativeSound> createSound(IO::InputStream & stream) = 0;

        virtual ~NativeAudioInterface() = default;
    };
}

