#pragma once

#include <Mogren/Framework/ResourceManagement/Resource.h>
#include <memory>

namespace Audio
{
    class Sound;
    class NativeSoundPlayer;

    ///
    /// The sound player class
    ///
    class SoundPlayer
    {
    public:
        ///
        /// Initializes a new instance of SoundPlayer class.
        ///
        explicit SoundPlayer(const std::shared_ptr<const Sound> & sound);

        ///
        /// Starts playing the sound
        ///
        void play();

        ///
        /// Pauses playing the sound
        ///
        void pause();

        ///
        /// Stops playing the sound
        ///
        void stop();

        ///
        /// Sets current playing position in seconds.
        /// If position is larger then sound duration or less then zero,
        /// position is set as if the sound were looping infinitely
        /// \param position Position in seconds
        ///
        void setPosition(float position);

        ///
        /// Gets the current sound position in seconds.
        /// Position lays in range from zero to sound duration.
        /// \returns Position in seconds
        ///
        float getPosition();

        ///
        /// If \a isLooping is true, the sound playing will be looped
        ///
        void setLooping(bool isLooping);

        ///
        /// Returns true if the sound playing is looped
        ///
        bool isLooping();

        ///
        /// Returns true if the sound is currently playing
        ///
        bool isPlaying() const;

        ///
        /// Sets the sound volume in [0..1] range
        /// \param volume The sound volume in [0..1] range
        ///
        void setVolume(float volume);

        ///
        /// Returns the sound volume in [0..1] range
        ///
        float getVolume();

        ///
        /// Sets the sound speed multiplier
        /// \param volume The sound speed multiplier
        ///
        void setSpeedMultiplier(float multiplier);

        ///
        /// Gets the sound speed multiplier
        ///
        float getSpeedMultiplier();

        ~SoundPlayer();

    private:
        bool mLooping;
        float mVolume;
        float mSpeedMultiplier;

        std::shared_ptr<const Sound> mSound;
        std::unique_ptr<NativeSoundPlayer> mNativeSoundPlayer;
    };
}

