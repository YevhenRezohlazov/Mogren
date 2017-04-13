#include "AnimationManager.h"
#include "AnimationController.h"

namespace Animation
{
    AnimationController::AnimationController(
        std::unique_ptr<Animator> animator,
        double duration, double delay, bool looped, EasingFunction easingFunction)
        : mAnimator(std::move(animator)), mDuration(duration)
        , mDelay(delay), mIsLooped(looped), mShouldCancel(false)
        , mCurrentTime(0.0), mEasingFunction(easingFunction), mPauseStartTime(), mIsPaused(false)
    {
    }

    bool AnimationController::isFinished() const
    {
        return mAnimator == nullptr;
    }

    bool AnimationController::isPaused() const
    {
        return mIsPaused;
    }

    void AnimationController::pause()
    {
        mIsPaused = true;
    }

    void AnimationController::resume()
    {
        mIsPaused = false;
    }

    void AnimationController::cancel()
    {
        mShouldCancel = true;
    }

    AnimationController::~AnimationController()
    {
        if (!isFinished() && mIsPaused)
        {
            cancel();
        }
    }
}