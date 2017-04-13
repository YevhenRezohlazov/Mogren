#pragma once

#include <Mogren/Framework/ResourceManagement/ResourceLoader.h>

namespace
{
    class InputStream;
}

namespace Localization
{
    class LocalizedStringsLoader : public ResourceManagement::ResourceLoader
    {
    public:
        LocalizedStringsLoader();

        virtual const std::vector<std::string> getResourceExtensions() const override;

        virtual std::unique_ptr<ResourceManagement::Resource> loadResource(
            IO::InputStream &inputStream) const override;
    };
}


