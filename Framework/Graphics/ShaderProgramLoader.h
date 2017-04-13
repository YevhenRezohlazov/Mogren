#pragma once

#include <Mogren/Framework/ResourceManagement/ResourceLoader.h>

namespace IO
{
    class InputStream;
}

namespace Graphics
{
    class ShaderProgramLoader : public ResourceManagement::ResourceLoader
    {
    private:
        static const uint32_t FileSignature = 0x5FA6B220;

    public:
        ShaderProgramLoader();

        virtual const std::vector<std::string> getResourceExtensions() const override;

        virtual std::unique_ptr<ResourceManagement::Resource> loadResource(IO::InputStream & inputStream) const override;
    };
}

