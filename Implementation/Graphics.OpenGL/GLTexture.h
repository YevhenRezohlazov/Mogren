#pragma once

#include <Mogren/Framework/Graphics/PrimitiveTypes/TextureFilter.h>
#include <Mogren/Framework/Graphics/PrimitiveTypes/TextureWrapMode.h>
#include "GLResource.h"

namespace Graphics
{
    ///
    /// OpenGL buffer wrapper
    ///
    class GLTexture : public GLResource
    {
    public:
        // disallow copying
        GLTexture(const GLTexture&) = delete;
        GLTexture& operator=(const GLTexture&) = delete;

        explicit GLTexture(GLenum target);

        void init(bool suppressDeletion = false);

        void init(GLuint id, bool suppressDeletion = false);

        void bind() const;

        // texture should be bound
        void setParameters(
            Graphics::TextureFilter minFilter,
            Graphics::TextureFilter magFilter,
            Graphics::TextureWrapMode wrapU,
            Graphics::TextureWrapMode wrapV) const;

    protected:
        void deleteResource();

    private:
        GLenum mBindTarget;
    };
}

