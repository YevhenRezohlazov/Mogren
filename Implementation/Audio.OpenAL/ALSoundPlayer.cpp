#include "ALSoundPlayer.h"
#include "ALSound.h"
#include <Mogren/Framework/App/App.h>
#include <Mogren/Framework/IO/InputStream.h>
#include <Mogren/Framework/IO/StreamUtils.h>
#include <Mogren/Framework/IO/MemoryStream.h>
#include <Mogren/Framework/IO/BinaryReader.h>
#include <Mogren/Framework/Logging/Logger.h>
#include <Mogren/Framework/Math/Functions.h>
#include <Mogren/ThirdParty/stb_vorbis/stb_vorbis.h>
#include <assert.h>

namespace Audio
{
    namespace
    {
        ALenum to_al_format(short channels, short samples)
        {
            bool stereo = (channels > 1);

            switch (samples) {
            case 16:
                if (stereo)
                    return AL_FORMAT_STEREO16;
                else
                    return AL_FORMAT_MONO16;
            case 8:
                if (stereo)
                    return AL_FORMAT_STEREO8;
                else
                    return AL_FORMAT_MONO8;
            default:
                return -1;
            }
        }
    }

    ALSoundPlayer::ALSoundPlayer(const ALSound & alSound)
        : mAlSound(alSound)
    {
        alGenSources(1, &mSource);
        alSourcei(mSource, AL_BUFFER, alSound.getBuffer());
    }

    void ALSoundPlayer::play()
    {
        alSourcePlay(mSource);
    }

    void ALSoundPlayer::pause()
    {
        alSourcePause(mSource);
    }

    void ALSoundPlayer::stop()
    {
        alSourceStop(mSource);
    }

    void ALSoundPlayer::setPosition(float position)
    {
        float realPos = Math::fmod(position, mAlSound.getDuration());
        alSourcef(mSource, AL_SEC_OFFSET, realPos);
    }

    float ALSoundPlayer::getPosition()
    {
        float position;
        alGetSourcef(mSource, AL_SEC_OFFSET, &position);
        return position;
    }

    void ALSoundPlayer::setLooping(bool isLooping)
    {
        alSourcei(mSource, AL_LOOPING, isLooping ? AL_TRUE : AL_FALSE);
    }

    bool ALSoundPlayer::isPlaying() const
    {
        ALint state;
        alGetSourcei(mSource, AL_SOURCE_STATE, &state);
        return state == AL_PLAYING;
    }

    void ALSoundPlayer::setVolume(float volume)
    {
        alSourcef(mSource, AL_GAIN, volume);
    }

    void ALSoundPlayer::setSpeedMultiplier(float multiplier)
    {
        alSourcef(mSource, AL_PITCH, multiplier);
    }

    ALSoundPlayer::~ALSoundPlayer()
    {
        alDeleteSources(1, &mSource);
    }
}