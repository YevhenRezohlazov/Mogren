#pragma once

#include <vector>
#include <string>
#include <memory>

namespace IO
{
    class InputStream;
}

namespace ResourceManagement
{
    class Resource;

    ///
    /// Resource loader interface
    ///
    class ResourceLoader
    {
    public:
        ///
        /// When implemented in derived classes, returns list of file extensions
        /// that can be loaded by this loader
        ///
        virtual const std::vector<std::string> getResourceExtensions() const = 0;

        ///
        /// When implemented in derived classes, loads the resource from given input stream
        /// \param inputStream The stream to load the resource from
        ///
        virtual std::unique_ptr<Resource> loadResource(IO::InputStream & inputStream) const = 0;

        virtual ~ResourceLoader() = default;
    };
}
