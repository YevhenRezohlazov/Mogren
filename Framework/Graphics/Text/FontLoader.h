#pragma once

#include <Mogren/Framework/ResourceManagement/ResourceLoader.h>

namespace Graphics
{
    namespace Text
    {
        class FontLoader : public ResourceManagement::ResourceLoader
        {
        public:
            virtual const std::vector<std::string> getResourceExtensions() const override;

            virtual std::unique_ptr<ResourceManagement::Resource> loadResource(IO::InputStream & inputStream) const override;
        };
    }
}

