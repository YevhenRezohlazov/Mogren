#pragma once

#include <Mogren/Framework/ResourceManagement/ResourceLoader.h>

namespace Audio
{
    class SoundLoader : public ResourceManagement::ResourceLoader
    {
    public:
        SoundLoader();

        virtual const std::vector<std::string> getResourceExtensions() const override;

        virtual std::unique_ptr<ResourceManagement::Resource> loadResource(IO::InputStream & inputStream) const override;
    };
}
