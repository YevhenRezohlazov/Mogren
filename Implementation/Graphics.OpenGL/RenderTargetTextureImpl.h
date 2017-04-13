/*#ifndef _RENDERTARGETTEXTUREIMPL_C0C1EBE9_9D88_4779_8195_168D8D2970E1_
#define _RENDERTARGETTEXTUREIMPL_C0C1EBE9_9D88_4779_8195_168D8D2970E1_

#include "RenderTargetImpl.h"
#include "TextureImpl.h"
#include "GLRenderbuffer.h"

namespace Graphics
{
    class RenderTargetTextureImpl : public RenderTargetImpl, public TextureImpl
    {
    public:
        DECLARE_SMART_PTRS_AND_TYPE_INFO2(RenderTargetTextureImpl, RenderTargetImpl, TextureImpl)

    private:
        GLRenderbuffer mRenderbuffer;

    protected:
        RenderTargetTextureImpl();

        void init(int width, int height);

    public:
        static Ptr create(int width, int height);

        virtual int getWidth() const;

        virtual int getHeight() const;
    };
}
#endif // _RENDERTARGETTEXTUREIMPL_C0C1EBE9_9D88_4779_8195_168D8D2970E1_*/