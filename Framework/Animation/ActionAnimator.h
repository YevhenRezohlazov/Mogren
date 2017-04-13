#pragma once

#include "Animator.h"
#include <functional>

namespace Animation
{
    ///
    /// Animator implementation for animating by calling System.Action delegate without parameters.
    ///
    class ActionAnimator : public Animator
    {
    public:
        typedef std::function<void()> Action;
        typedef std::function<void(AnimationFinishEvent finishEvent)> FinishCallback;

        ///
        /// Initializes a new instance of the ActionAnimator class.
        ///
        /// \param action The animation action.
        ActionAnimator(Action action, FinishCallback finishCallback = [](auto) {});

        ///
        /// Performs next frame animation (invokes Action delegate).
        ///
        /// \param time The normalized animation time value or zero, if UsesTime is false.
        virtual void animate(float time) override;

        virtual void onFinished(AnimationFinishEvent finishEvent) override;

    private:
        Action mAction;
        FinishCallback mFinishCallback;
    };
}

