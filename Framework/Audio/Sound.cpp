#include "Sound.h"
#include "SoundPlayer.h"
#include "NativeInterface/NativeSound.h"
#include "NativeInterface/NativeSoundPlayer.h"

namespace Audio
{
    Sound::Sound(std::unique_ptr<NativeSound> nativeSound)
        : mNativeSound(std::move(nativeSound))
    {
    }

    float Sound::getDuration() const
    {
        return mNativeSound->getDuration();
    }

    void Sound::finalize()
    {
        mNativeSound->finalize();
    }

    Sound::~Sound() = default;
}