#include "SoundPlayer.h"
#include "Sound.h"
#include "NativeInterface/NativeSoundPlayer.h"
#include "NativeInterface/NativeSound.h"

namespace Audio
{
    SoundPlayer::SoundPlayer(const std::shared_ptr<const Sound> & sound)
        : mLooping(false), mVolume(1.0f), mSpeedMultiplier(1.0f)
        , mSound(sound)
        , mNativeSoundPlayer(sound->mNativeSound->createSoundPlayer())
    {
    }

    void SoundPlayer::play()
    {
        mNativeSoundPlayer->play();
    }

    void SoundPlayer::pause()
    {
        mNativeSoundPlayer->pause();
    }

    void SoundPlayer::stop()
    {
        mNativeSoundPlayer->stop();
    }

    void SoundPlayer::setPosition(float position)
    {
        mNativeSoundPlayer->setPosition(position);
    }

    float SoundPlayer::getPosition()
    {
        return mNativeSoundPlayer->getPosition();
    }

    void SoundPlayer::setLooping(bool isLooping)
    {
        mLooping = isLooping;
        return mNativeSoundPlayer->setLooping(isLooping);
    }

    bool SoundPlayer::isLooping()
    {
        return mLooping;
    }

    bool SoundPlayer::isPlaying() const
    {
        return mNativeSoundPlayer->isPlaying();
    }

    void SoundPlayer::setVolume(float volume)
    {
        mVolume = volume;

        if (mVolume < 0.0f) mVolume = 0.0f;
        if (mVolume > 1.0f) mVolume = 1.0f;

        mNativeSoundPlayer->setVolume(mVolume);
    }

    float SoundPlayer::getVolume()
    {
        return mVolume;
    }

    void SoundPlayer::setSpeedMultiplier(float multiplier)
    {
        mSpeedMultiplier = multiplier;
        mNativeSoundPlayer->setSpeedMultiplier(multiplier);
    }

    float SoundPlayer::getSpeedMultiplier()
    {
        return mSpeedMultiplier;
    }

    SoundPlayer::~SoundPlayer() = default;
}