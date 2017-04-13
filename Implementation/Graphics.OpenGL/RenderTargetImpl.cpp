#include "RenderTargetImpl.h"

namespace Graphics
{
    RenderTargetImpl::RenderTargetImpl(GLuint glFrameBufferId, int width, int height, bool suppressFrameBufferDeletion)
    {
        mGLFrameBuffer.init(glFrameBufferId, suppressFrameBufferDeletion);
        mWidth = width;
        mHeight = height;
    }

    const GLFramebuffer& RenderTargetImpl::getGLFrameBuffer() const
    {
        return mGLFrameBuffer;
    }

    int RenderTargetImpl::getWidth() const
    {
        return mWidth;
    }

    int RenderTargetImpl::getHeight() const
    {
        return mHeight;
    }
}