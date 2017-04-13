#pragma once

#include <string>

namespace Logging
{
    ///
    /// Logger interface
    ///
    class LogWriter
    {
    public:
        ///
        /// Writes the informational message into the log.
        ///
        /// \param message The log message to be written.
        virtual void write(const char * message) = 0;
    };
}
