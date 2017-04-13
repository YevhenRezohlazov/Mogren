#include "ResourceManagerImpl.h"
#include <Mogren/Framework/IO/FileStream.h>

namespace ResourceManagement
{
    const std::string ResourceManagerImpl::ResourcesRootPath = "resources";

    ResourceManagerImpl::ResourceManagerImpl()
    {
    }
    std::unique_ptr<IO::InputStream> ResourceManagerImpl::openStream(const std::string & path)
    {
        return std::make_unique<IO::FileStream>(ResourcesRootPath + "/" + path, IO::FileMode::ReadBinary);
    }
}