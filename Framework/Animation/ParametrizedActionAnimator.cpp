#include "ParametrizedActionAnimator.h"

namespace Animation
{
    ParametrizedActionAnimator::ParametrizedActionAnimator(Action action, FinishCallback finishCallback)
        : Animator(true)
    {
        mAction = action;
        mFinishCallback = finishCallback;
    }

    void ParametrizedActionAnimator::animate(float time)
    {
        mAction(time);
    }

    void ParametrizedActionAnimator::onFinished(AnimationFinishEvent finishEvent)
    {
        mFinishCallback(finishEvent);
    }
}