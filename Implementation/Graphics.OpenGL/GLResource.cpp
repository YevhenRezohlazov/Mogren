#include "GLResource.h"
#include "ResourcesReloader.h"

#include <Mogren/Framework/Logging/Logger.h>

namespace Graphics
{
    void GLResource::init(bool suppressDeletion)
    {
        if (mInited)
        {
            Logging::Logger::writeWarning("Initializing of already initialized resource.");
            return;
        }

        mSuppressDeletion = suppressDeletion;
        mId = -1;
        mInited = true;
        ResourcesReloader::addResource(this);
    }

    void GLResource::init(GLuint id, bool suppressDeletion)
    {
        if (mInited)
        {
            Logging::Logger::writeWarning("Initializing of already initialized resource.");
            return;
        }

        mSuppressDeletion = suppressDeletion;
        mId = id;
        mInited = true;
        ResourcesReloader::addResource(this);
    }

    GLResource::GLResource() : mInited(false)
    {

    }

    GLuint GLResource::getId() const
    {
        checkInited();
        return mId;
    }

    bool GLResource::isInitialized() const
    {
        return mInited;
    }

    GLResource::~GLResource()
    {
        if (mInited && !mSuppressDeletion)
        {
            deleteResource();
        }

        ResourcesReloader::removeResource(this);
    }

    void GLResource::deleteResource()
    {
    }

    void GLResource::checkInited() const
    {
        if (!mInited)
        {
            Logging::Logger::writeWarning("Using uninitialized resource.");
        }
    }
}