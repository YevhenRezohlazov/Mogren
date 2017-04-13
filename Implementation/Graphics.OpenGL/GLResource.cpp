#include "GLResource.h"

#include <Mogren/Framework/Logging/Logger.h>

namespace Graphics
{
    void GLResource::init(bool suppressDeletion)
    {
        if (mInited)
        {
            Logging::Logger::writeWarning("Initializing of already initialized resource.");
        }

        mSuppressDeletion = suppressDeletion;
        mId = -1;
        mInited = true;
    }

    void GLResource::init(GLuint id, bool suppressDeletion)
    {
        if (mInited)
        {
            Logging::Logger::writeWarning("Initializing of already initialized resource.");
        }

        mSuppressDeletion = suppressDeletion;
        mId = id;
        mInited = true;
    }

    GLResource::GLResource() : mInited(false)
    {
    }

    GLuint GLResource::getId() const
    {
        checkInited();
        return mId;
    }

    GLResource::~GLResource()
    {
        if (mInited && !mSuppressDeletion)
        {
            deleteResource();
        }
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