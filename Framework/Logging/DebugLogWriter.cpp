#include "DebugLogWriter.h"

namespace Logging
{
    void DebugLogWriter::write(const char * message)
    {
        puts(message);
    }
}