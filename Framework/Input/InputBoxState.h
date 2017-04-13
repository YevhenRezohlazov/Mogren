#pragma once

namespace Input
{
    ///
    /// Represents possible input box states
    ///
    enum class InputBoxState
    {
        ///
        /// Input box is enabled and can receive touch events
        ///
        Enabled,

        ///
        /// Input box doesn't receive any events but prevents events from being
        /// dispatched to the input boxed behind this one (doesn't affect
        /// touch previews)
        ///
        Disabled,

        ///
        /// Input box doesn't receive any events and doesn't affect dispatching,
        /// that is, input box is just ignored
        ///
        Gone
    };
}

