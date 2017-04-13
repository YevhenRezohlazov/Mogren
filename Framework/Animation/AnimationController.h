#pragma once

#include <memory>
#include <functional>

namespace Animation
{
    class Animator;

    ///
    /// AnimationController class for controlling animation process
    ///
    class AnimationController
    {
    public:
        typedef std::function<float(float)> EasingFunction;
        friend class AnimationManager;

        ///
        /// Initializes a new instance of the AnimationController class.
        ///
        /// \param manager The animation manager.
        /// \param elem The animation element.
        AnimationController(
            std::unique_ptr<Animator> animator, double duration, double delay,
            bool looped, EasingFunction easingFunction);

        ///
        /// Gets a value indicating whether the animation is finished.
        ///
        bool isFinished() const;

        ///
        /// Gets a value indicating whether the animation is currently paused.
        ///
        bool isPaused() const;

        ///
        /// Pauses the animation.
        ///
        void pause();

        ///
        /// Resumes the animation.
        ///
        void resume();

        ///
        /// Cancels the animation.
        ///
        void cancel();

        ~AnimationController();

    private:
        std::shared_ptr<AnimationController> mPrevious;
        std::shared_ptr<AnimationController> mNext;

        std::unique_ptr< Animator > mAnimator;
        double mDuration;
        double mDelay;
        bool mIsLooped;

        bool mShouldCancel;

        double mCurrentTime;

        EasingFunction mEasingFunction;

        double mPauseStartTime;
        bool mIsPaused;
    };
}

