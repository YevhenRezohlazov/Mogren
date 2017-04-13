#pragma once

#include <memory>

namespace ResourceManagement
{
    ///
    /// Resource interface
    ///
    class Resource
        : public std::enable_shared_from_this<Resource>
    {
    protected:
        Resource() = default;

    public:
        Resource(Resource&) = delete;
        Resource& operator=(Resource&) = delete;

        ///
        /// Called from main thread to finalize resource (upload data to GPU, etc)
        ///
        virtual void finalize() = 0;

        virtual ~Resource() = default;
    };
}
