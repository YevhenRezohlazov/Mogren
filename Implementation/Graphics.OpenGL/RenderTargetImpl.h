#pragma once

#include <Mogren/Framework/Graphics/NativeInterface/NativeRenderTarget.h>
#include "GLFramebuffer.h"

namespace Graphics
{
    class RenderTargetImpl : public NativeRenderTarget
    {
    private:
        GLFramebuffer mGLFrameBuffer;
        int mWidth;
        int mHeight;

    public:
        RenderTargetImpl(GLuint glFrameBufferId, int width, int height, bool suppressFrameBufferDeletion = false);

        const GLFramebuffer& getGLFrameBuffer() const;

        virtual int getWidth() const;

        virtual int getHeight() const;
    };
}

