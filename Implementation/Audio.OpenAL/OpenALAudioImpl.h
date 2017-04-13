#pragma once

#include <Mogren/Framework/Audio/NativeInterface/NativeAudioInterface.h>

namespace Audio
{
    class OpenALAudioImpl : public Audio::NativeAudioInterface
    {
    public:
        OpenALAudioImpl();

        virtual std::unique_ptr<NativeSound> createSound(IO::InputStream & stream) override;

        ~OpenALAudioImpl();
    };
}

