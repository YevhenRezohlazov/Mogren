#include "ResourcesReloader.h"
#include "GLResource.h"
#include <algorithm>

namespace Graphics
{
    std::vector<GLResource*> ResourcesReloader::mResources;

    void ResourcesReloader::addResource(GLResource * resource)
    {
        auto iter = std::find(mResources.cbegin(), mResources.cend(), resource);

        if (iter == mResources.end())
            mResources.push_back(resource);
    }

    void ResourcesReloader::removeResource(GLResource * resource)
    {
        auto iter = std::find(mResources.cbegin(), mResources.cend(), resource);

        if (iter != mResources.end())
        {
            mResources.erase(iter);
        }
    }

    void ResourcesReloader::reloadResources()
    {
        for (auto res : mResources)
        {
            if (res->isInitialized())
                res->reload();
        }
    }
}