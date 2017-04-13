#pragma once

#include "AnimationFinishEvent.h"

namespace Animation
{
    ///
    /// Abstract class for implementing animations functionality
    ///
    class Animator
    {
    protected:
        ///
        /// Initializes a new instance of the Animator class.
        ///
        /// \param usesTime Set to \a true, if this animator uses time argument in Animate
        /// method implementation. If false is set, time will always be zero.
        Animator(bool usesTime);

    public:
        ///
        /// Gets a value indicating whether this animator uses time argument in Animate method implementation.
        ///
        bool usesTime() const;

        ///
        /// Performs next frame animation.
        ///
        /// \param time The normalized animation time value or zero, if UsesTime is false.
        virtual void animate(float time) = 0;

        ///
        /// Called when the animation is finished.
        ///
        /// \param finishEvent The animation finish event (completed, canceled or looped).
        virtual void onFinished(AnimationFinishEvent finishEvent);

    private:
        bool mUsesTime;
    };
}

