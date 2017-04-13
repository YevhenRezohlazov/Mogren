#include "ActionAnimator.h"

namespace Animation
{
    ActionAnimator::ActionAnimator(Action action, FinishCallback finishCallback)
        : Animator(false)
    {
        mAction = action;
        mFinishCallback = finishCallback;
    }

    void ActionAnimator::animate(float)
    {
        mAction();
    }

    void ActionAnimator::onFinished(AnimationFinishEvent finishEvent)
    {
        mFinishCallback(finishEvent);
    }
}