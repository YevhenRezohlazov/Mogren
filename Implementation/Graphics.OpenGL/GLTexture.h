#pragma once

#include <Mogren/Framework/Graphics/PrimitiveTypes/TextureFilter.h>
#include <Mogren/Framework/Graphics/PrimitiveTypes/TextureWrapMode.h>
#include "GLResource.h"
#include <stdint.h>
#include <vector>

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

        void init(int width, int height, const uint8_t * sourcePixels, int channelsCount);

        void bind() const;

        // texture should be bound
        void setParameters(
            Graphics::TextureFilter minFilter,
            Graphics::TextureFilter magFilter,
            Graphics::TextureWrapMode wrapU,
            Graphics::TextureWrapMode wrapV) const;

        virtual void reload() override;

    protected:
        void deleteResource();

    private:
        GLenum mBindTarget;

        int mWidth;
        int mHeight;

        std::vector<uint8_t> mSourcePixels;
        int mChannelsCount;
    };
}

