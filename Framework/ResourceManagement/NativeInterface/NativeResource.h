#pragma once

namespace ResourceManagement
{
    ///
    /// Native resource interface
    ///
    class NativeResource
    {
    public:
        ///
        /// Called from main thread to finalize resource (upload data to GPU, etc)
        ///
        virtual void finalize() = 0;

        virtual ~NativeResource() = default;
    };
}

