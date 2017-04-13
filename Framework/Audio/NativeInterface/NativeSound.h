#pragma once

#include <memory>
#include <Mogren/Framework/ResourceManagement/NativeInterface/NativeResource.h>

namespace Audio
{
    class NativeSoundPlayer;

    class NativeSound : public ResourceManagement::NativeResource
    {
    public:
        ///
        /// Returns the sound duration in seconds
        ///
        virtual std::unique_ptr<NativeSoundPlayer> createSoundPlayer() const = 0;

        virtual float getDuration() const = 0;

        virtual ~NativeSound() = default;
    };
}

