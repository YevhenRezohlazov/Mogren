#pragma once

#include "GLResource.h"
#include <vector>
#include <stdint.h>

namespace Graphics
{
    ///
    /// OpenGL buffer wrapper
    ///
    class GLBuffer : public GLResource
    {
    public:
        // disallow copying
        GLBuffer(const GLBuffer&) = delete;
        GLBuffer& operator=(const GLBuffer&) = delete;

        GLBuffer();

        void init(bool isDynamic, bool suppressDeletion = false);

        void init(GLuint id, bool isDynamic, bool suppressDeletion = false);

        void bind(GLenum target) const;

        virtual void reload() override;

        std::vector< uint8_t >& getData();

    protected:
        void deleteResource();

    private:
        bool mIsDynamic = false;
        std::vector< uint8_t > mData;
    };
}

