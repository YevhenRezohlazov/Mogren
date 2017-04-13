#include "FileLogger.h"
#include <stdio.h>
#include <assert.h>

namespace Logging
{
    FileLogger::FileLogger(const char * fileName)
    {
        mFile = fopen(fileName, "w");
        assert(mFile);
    }

    void FileLogger::write(const char * message)
    {
        fputs(message, (FILE*)mFile);
        fputs("\n", (FILE*)mFile);
        fflush((FILE*)mFile);
    }

    FileLogger::~FileLogger()
    {
        fclose((FILE*)mFile);
    }
}