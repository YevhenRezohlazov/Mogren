#pragma once

#include <Mogren/Framework/ResourceManagement/NativeInterface/NativeResourceManager.h>

namespace ResourceManagement
{
    class ResourceManagerImpl : public NativeResourceManager
    {
    public:
        static const std::string ResourcesRootPath;

        ResourceManagerImpl();

    public:
        virtual std::unique_ptr<IO::InputStream> openStream(const std::string &path) override;
    };
}

