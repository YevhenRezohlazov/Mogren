#include "Logger.h"
#include "LogWriter.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <mutex>

namespace Logging
{
    namespace
    {
        enum class LogMessageType
        {
            Info,
            Warning,
            Error
        };

        std::mutex gMutex;
        constexpr int gMessageBufferSize = 1024;
        constexpr char gInfoPrefix[] = "[INFO] ";
        constexpr char gWarningPrefix[] = "[WARNING] ";
        constexpr char gErrorPrefix[] = "[ERROR] ";
        thread_local char gInfoBuffer[gMessageBufferSize + sizeof(gInfoPrefix)];
        thread_local char gWarningBuffer[gMessageBufferSize + sizeof(gWarningPrefix)];
        thread_local char gErrorBuffer[gMessageBufferSize + sizeof(gErrorPrefix)];
        std::vector< std::unique_ptr<LogWriter> > gLogWriters;

        static void write(LogMessageType type, const char * format, va_list argList)
        {
            {
                std::lock_guard<std::mutex> lock(gMutex);
                if (gLogWriters.empty())
                {
                    return;
                }
            }

            char * outBuffer;
            char * buffer;
            switch (type)
            {
            case LogMessageType::Info:
                memcpy(gInfoBuffer, gInfoPrefix, sizeof(gInfoPrefix));
                outBuffer = gInfoBuffer;
                buffer = gInfoBuffer + sizeof(gInfoPrefix) - 1;
                break;
            case LogMessageType::Warning:
                memcpy(gWarningBuffer, gWarningPrefix, sizeof(gWarningPrefix));
                outBuffer = gWarningBuffer;
                buffer = gWarningBuffer + sizeof(gWarningPrefix) - 1;
                break;
            case LogMessageType::Error:
                memcpy(gErrorBuffer, gErrorPrefix, sizeof(gErrorPrefix));
                outBuffer = gErrorBuffer;
                buffer = gErrorBuffer + sizeof(gErrorPrefix) - 1;
                break;
            default:
                return;
            }

            vsnprintf(buffer, gMessageBufferSize, format, argList);

            std::lock_guard<std::mutex> lock(gMutex);
            for (auto & logWriter : gLogWriters)
            {
                logWriter->write(outBuffer);
            }
        }
    }

    void Logger::addLogWriter(std::unique_ptr<LogWriter>&& writer)
    {
        gLogWriters.push_back(std::move(writer));
    }

    void Logger::writeInfo(const char * format, ...)
    {
        va_list argList;
        va_start(argList, format);
        write(LogMessageType::Info, format, argList);
        va_end(argList);
    }

    void Logger::writeWarning(const char * format, ...)
    {
        va_list argList;
        va_start(argList, format);
        write(LogMessageType::Warning, format, argList);
        va_end(argList);
    }

    void Logger::writeError(const char * format, ...)
    {
        va_list argList;
        va_start(argList, format);
        write(LogMessageType::Error, format, argList);
        va_end(argList);
    }
}
