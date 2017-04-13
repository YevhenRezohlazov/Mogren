#include "LocalizedStringsLoader.h"

#include "LocalizedStrings.h"

namespace Localization
{
    LocalizedStringsLoader::LocalizedStringsLoader()
    {
    }

    const std::vector<std::string> LocalizedStringsLoader::getResourceExtensions() const
    {
        return { "str" };
    }

    std::unique_ptr<ResourceManagement::Resource> 
        LocalizedStringsLoader::loadResource(IO::InputStream &inputStream) const
    {
        return std::make_unique<LocalizedStrings>(inputStream);
    }
}