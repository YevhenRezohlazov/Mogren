#pragma once

#include <string>
#include <chrono>

namespace Logging
{
    class FunctionLoggingGuard
    {
    private:
        decltype(std::chrono::high_resolution_clock::now()) mExecutionStartTime;
        std::string mFunctionName;

    public:
        FunctionLoggingGuard(const char * functionName);

        ~FunctionLoggingGuard();
    };
}

#ifdef _DEBUG
#define DECLARE_FUNCTION_LOGGING_GUARD() Logging::FunctionLoggingGuard __functionLoggingGuard(__FUNCTION__);
#else
#define DECLARE_FUNCTION_LOGGING_GUARD()
#endif

