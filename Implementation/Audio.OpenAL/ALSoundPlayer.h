#pragma once

#include "ALInclude.h"
#include <Mogren/Framework/Audio/NativeInterface/NativeSoundPlayer.h>
#include <memory>

namespace Audio
{
    class ALSound;

    class ALSoundPlayer : public Audio::NativeSoundPlayer
    {
    public:
        explicit ALSoundPlayer(const ALSound & alSound);

        virtual void play() override;

        virtual void pause() override;

        virtual void stop() override;

        virtual void setPosition(float position) override;

        virtual float getPosition() override;

        virtual void setLooping(bool isLooping) override;

        virtual bool isPlaying() const override;

        virtual void setVolume(float volume) override;

        virtual void setSpeedMultiplier(float multiplier) override;

        ~ALSoundPlayer();

    private:
        const ALSound & mAlSound;
        ALuint mSource;
    };
}

