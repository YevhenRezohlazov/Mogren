#pragma once

#include <vector>
#include <memory>
#include <stdio.h>

namespace Logging
{
    class LogWriter;
    ///
    /// Static class for logging.
    ///
    class Logger
    {
    public:
        // disallow creating objects
        Logger() = delete;

        static void addLogWriter(std::unique_ptr<LogWriter> && writer);

        ///
        /// Writes given informational message to the log.
        ///
        static void writeInfo(const char * format, ...);

        ///
        /// Writes given warning message to the logs.
        ///
        /// \param message The warning message.
        static void writeWarning(const char * format, ...);

        ///
        /// Writes given error message to the logs.
        ///
        /// \param message The error message.
        static void writeError(const char * format, ...);
    };
}

