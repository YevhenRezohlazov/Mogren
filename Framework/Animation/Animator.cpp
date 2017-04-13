#include "Animator.h"

Animation::Animator::Animator(bool usesTime)
{
    mUsesTime = usesTime;
}

bool Animation::Animator::usesTime() const
{
    return mUsesTime;
}

void Animation::Animator::onFinished(AnimationFinishEvent finishEvent)
{
}