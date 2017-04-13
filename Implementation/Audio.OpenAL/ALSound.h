#pragma once

#include "ALInclude.h"
#include <Mogren/Framework/Audio/NativeInterface/NativeSound.h>
#include <memory>
#include <vector>

namespace IO
{
    class InputStream;
}

namespace Audio
{
    class ALSound : public Audio::NativeSound
    {
    private:
        ALSound();

    public:
        static std::unique_ptr<ALSound> load(IO::InputStream &stream);

        virtual std::unique_ptr<NativeSoundPlayer> createSoundPlayer() const override;

        virtual float getDuration() const override;

        ALuint getBuffer() const;

        virtual void finalize() override;

        ~ALSound();

    private:
        static std::unique_ptr<ALSound> loadWAV(IO::InputStream &stream);
        static std::unique_ptr<ALSound> loadOgg(IO::InputStream &stream);

    private:
        ALuint mBuffer;
        float mDuration;

        ALenum mSourceFormat;
        std::vector<char> mSourceBuffer;
        ALsizei mSampleRate;
    };
}

