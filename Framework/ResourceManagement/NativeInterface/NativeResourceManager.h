#pragma once

#include <memory>
#include <string>

namespace IO
{
    class InputStream;
}

namespace ResourceManagement
{
    ///
    /// Native resource manager interface
    ///
    class NativeResourceManager
    {
    public:
        ///
        /// Opens the input stream for the specified file path.
        ///
        /// \param path The file path.
        /// \returns File stream.
        virtual std::unique_ptr<IO::InputStream> openStream(const std::string &path) = 0;

        virtual ~NativeResourceManager() = default;
    };
}

