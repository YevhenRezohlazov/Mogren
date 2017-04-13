#include "AnimationManager.h"
#include <Mogren/Framework/Logging/Logger.h>
#include <Mogren/Framework/Math/Functions.h>
#include <assert.h>

namespace Animation
{
    AnimationManager::AnimationManager() : mFirstController()
    {
    }

    std::shared_ptr<AnimationController> AnimationManager::addAnimation(
        std::unique_ptr<Animator> animator, double duration, double delay /*= 0*/,
        bool looped /*= false*/, EasingFunction easingFunction /*= EasingFunction()*/)
    {
        assert(animator);

        auto controller = std::make_shared<AnimationController>(std::move(animator), duration, delay, looped,
            easingFunction ? easingFunction : [](auto t) { return t; });
        addController(controller);
        return controller;
    }

    void AnimationManager::performAnimations(double timeDelta)
    {
        for (auto controller = mFirstController; controller != nullptr; controller = controller->mNext)
        {
            if (controller->mShouldCancel)
            {
                controller->mAnimator->onFinished(AnimationFinishEvent::Cancelled);
                controller->mAnimator.reset();
                removeController(*controller);
                continue;
            }

            if (controller->isPaused())
            {
                continue;
            }

            controller->mCurrentTime += timeDelta;

            auto animTime = controller->mCurrentTime - controller->mDelay;

            if (animTime >= 0.0)
            {
                auto finish = false;
                auto loopCompleted = false;

                if (animTime >= controller->mDuration)
                {
                    if (controller->mIsLooped)
                    {
                        animTime = Math::fmod((float)animTime, (float)controller->mDuration);
                        loopCompleted = true;
                    }
                    else
                    {
                        finish = true;
                    }
                }

                if (controller->mAnimator->usesTime())
                {
                    float param;

                    if (finish)
                    {
                        param = 1.0f;
                    }
                    else
                    {
                        param = (float)(animTime / controller->mDuration);
                    }

                    // apply easing function
                    param = controller->mEasingFunction(param);

                    controller->mAnimator->animate(param);
                }
                else
                {
                    controller->mAnimator->animate(0.0f);
                }

                if (finish)
                {
                    controller->mAnimator->onFinished(AnimationFinishEvent::Completed);
                    controller->mAnimator.reset();
                    removeController(*controller);
                }
                else if (loopCompleted)
                {
                    controller->mAnimator->onFinished(AnimationFinishEvent::LoopCompleted);
                }
            }
        }
    }

    void AnimationManager::addController(std::shared_ptr<AnimationController> &controller)
    {
        controller->mNext = mFirstController;

        if (mFirstController != nullptr)
            mFirstController->mPrevious = controller;

        mFirstController = controller;
    }

    void AnimationManager::removeController(AnimationController & controller)
    {
        if (controller.mNext != nullptr)
        {
            controller.mNext->mPrevious = controller.mPrevious;
        }

        if (controller.mPrevious != nullptr)
        {
            controller.mPrevious->mNext = controller.mNext;
        }

        if (mFirstController.get() == &controller)
        {
            mFirstController = controller.mNext;
        }
    }

    AnimationManager::~AnimationManager()
    {
        // Convert doubly linked list to singly linked list, so it'll be deleted after mFirstController deletion
        for (auto controller = mFirstController; controller != nullptr; controller = controller->mNext)
            controller->mPrevious = nullptr;
    }
}