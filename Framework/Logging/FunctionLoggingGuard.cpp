#include "FunctionLoggingGuard.h"
#include "Logger.h"

#include <chrono>

namespace Logging
{
    FunctionLoggingGuard::FunctionLoggingGuard(const char * functionName)
        : mFunctionName(functionName)
    {
        mExecutionStartTime = std::chrono::high_resolution_clock::now();
        Logger::writeInfo("--> %s", functionName);
    }

    FunctionLoggingGuard::~FunctionLoggingGuard(void)
    {
        const std::chrono::duration<double> executionTime = std::chrono::high_resolution_clock::now() - mExecutionStartTime;
        Logger::writeInfo("<-- %s. Execution time: %.3lf sec.", mFunctionName.c_str(), executionTime.count());
    }
}