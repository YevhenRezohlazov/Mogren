#include "ResourceManagerImpl.h"
#include "AssetStream.h"

namespace ResourceManagement
{
    std::unique_ptr<IO::InputStream> ResourceManagerImpl::openStream(const std::string &path)
    {
        return std::make_unique<AssetStream>(path);
    }

    ResourceManagerImpl::ResourceManagerImpl()
    {
    }
}