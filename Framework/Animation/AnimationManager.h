#pragma once

#include "Animator.h"
#include "AnimationController.h"
#include <vector>

namespace Animation
{
    ///
    /// AnimationManager for creating and performing animations
    ///
    class AnimationManager final
    {
    public:
        typedef std::function<float(float)> EasingFunction;

    public:
        AnimationManager();
        AnimationManager(const AnimationManager&) = delete;
        AnimationManager& operator=(const AnimationManager&) = delete;
        
        ///
        /// Adds the animation to animation queue.
        ///
        /// \param animator The animation to be added.
        /// \param duration The duration of the animation (in seconds).
        /// \param delay The delay before animation starts (in seconds).
        /// \param looped if set to \a true, animation will be playing repeatedly
        /// until Cancel method is called on animation controller.
        /// \param easingFunction The animation time easing function.
        /// \returns Animation controller instance.
        std::shared_ptr<AnimationController> addAnimation(
            std::unique_ptr<Animator> animator, double duration,
            double delay = 0, bool looped = false,
            EasingFunction easingFunction = EasingFunction());

        ///
        /// Performs all the scheduled animations.
        ///
        /// \param timeDelta Time delta in seconds.
        void performAnimations(double timeDelta);

        ~AnimationManager();

    private:
        void addController(std::shared_ptr<AnimationController> &controller);
        void removeController(AnimationController &controller);

    private:
        std::shared_ptr<AnimationController> mFirstController;
    };
}

