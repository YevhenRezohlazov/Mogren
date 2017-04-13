#pragma once

#include "LogWriter.h"

namespace Logging
{
    class FileLogger : public LogWriter
    {
    public:
        FileLogger(const char *fileName);

        FileLogger(FileLogger&) = delete;
        FileLogger& operator=(FileLogger&) = delete;

    public:
        virtual void write(const char * message) override;

        ~FileLogger();

    private:
        void *mFile;
    };
}

