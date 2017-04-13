#pragma once

namespace Audio
{
    class NativeSoundPlayer
    {
    public:
        ///
        /// Starts playing the sound
        ///
        virtual void play() = 0;

        ///
        /// Pauses playing the sound
        ///
        virtual void pause() = 0;

        ///
        /// Stops playing the sound
        ///
        virtual void stop() = 0;

        ///
        /// Sets current playing position in seconds.
        /// If position is larger then sound duration or less then zero,
        /// position is set as if the sound were looping infinitely
        /// \param position Position in seconds
        ///
        virtual void setPosition(float position) = 0;

        ///
        /// Gets the current sound position in seconds.
        /// Position lays in range from zero to sound duration.
        /// \returns Position in seconds
        ///
        virtual float getPosition() = 0;

        ///
        /// If \a isLooping is true, the sound playing will be looped
        ///
        virtual void setLooping(bool isLooping) = 0;

        ///
        /// Returns true if the sound is currently playing
        ///
        virtual bool isPlaying() const = 0;

        ///
        /// Sets the sound volume in [0..1] range
        /// \param volume The sound volume in [0..1] range
        ///
        virtual void setVolume(float volume) = 0;

        ///
        /// Sets the sound speed multiplier
        /// \param volume The sound speed multiplier
        ///
        virtual void setSpeedMultiplier(float multiplier) = 0;

        virtual ~NativeSoundPlayer() = default;
    };
}

