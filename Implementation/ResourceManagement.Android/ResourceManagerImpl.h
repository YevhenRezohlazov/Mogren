#pragma once

#include <Mogren/Framework/ResourceManagement/NativeInterface/NativeResourceManager.h>
#include <Mogren/Framework/IO/InputStream.h>

namespace ResourceManagement
{
    class ResourceManagerImpl : public ResourceManagement::NativeResourceManager
    {
    public:
        ResourceManagerImpl();

        virtual std::unique_ptr<IO::InputStream> openStream(const std::string &path) override;
    };
}
