#pragma once

#include "GLInclude.h"

namespace Graphics
{
    ///
    /// Base class for OpenGL resource wrappers
    ///
    class GLResource
    {
    private:
        // disallow copying
        GLResource(const GLResource&);
        GLResource& operator=(const GLResource&);

    protected:
        GLuint mId;
        bool mSuppressDeletion;
        bool mInited;

    public:
        GLResource();

        void init(bool suppressDeletion);

        void init(GLuint id, bool suppressDeletion);

        GLuint getId() const;

        bool isInitialized() const;

        virtual void reload() = 0;

        virtual ~GLResource();

    protected:
        virtual void deleteResource();

        void checkInited() const;
    };
}

