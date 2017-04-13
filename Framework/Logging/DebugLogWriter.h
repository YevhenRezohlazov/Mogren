#pragma once

#include "LogWriter.h"

namespace Logging
{
    class DebugLogWriter : public LogWriter
    {
        virtual void write(const char * message) override;
    };
}
