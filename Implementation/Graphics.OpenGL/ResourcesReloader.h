#pragma once

#include <vector>

namespace Graphics
{
    class GLResource;

    class ResourcesReloader
    {
    public:
        static void addResource(GLResource * resource);
        static void removeResource(GLResource * resource);

        static void reloadResources();

    private:
        static std::vector<GLResource*> mResources;
    };
}

