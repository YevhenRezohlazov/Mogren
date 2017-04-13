#pragma once

#include <Mogren/Framework/ResourceManagement/ResourceLoader.h>

namespace Graphics
{
    class TextureLoader : public ResourceManagement::ResourceLoader
    {
    public:
        TextureLoader();

        virtual const std::vector<std::string> getResourceExtensions() const override;

        virtual std::unique_ptr<ResourceManagement::Resource> loadResource(IO::InputStream & inputStream) const override;
    };
}
