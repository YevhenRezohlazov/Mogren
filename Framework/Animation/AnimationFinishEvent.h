#pragma once

namespace Animation
{
    ///
    /// Animation finish events
    ///
    enum class AnimationFinishEvent
    {
        ///
        /// The animation playing has been fully completed
        ///
        Completed,

        ///
        /// The animation playing has been canceled
        ///
        Cancelled,

        ///
        /// The looped animation loop has been completed (but animation will continue playing from beginning)
        ///
        LoopCompleted
    };
}

