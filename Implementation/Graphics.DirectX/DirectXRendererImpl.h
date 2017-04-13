#ifndef _RENDERERIMPL_FB80F5AD_E9FA_4F9C_B37E_CCAF20459FF5_
#define _RENDERERIMPL_FB80F5AD_E9FA_4F9C_B37E_CCAF20459FF5_

#include <Mogren/Framework/Core/Include.h>
#include <Mogren/Framework/Graphics/Include.h>

namespace Graphics
{
    class DirectXRendererImpl : public Graphics::NativeInterface::NativeRenderer
    {
    public:
        DECLARE_SMART_PTRS_AND_TYPE_INFO(DirectXRendererImpl, Graphics::NativeInterface::NativeRenderer)

    protected:
        DirectXRendererImpl();

        void init();

    public:
        static Ptr create();

        virtual void clearTarget(const PrimitiveTypes::Color &clearColor);

        virtual void render();
    };
}

#endif // _RENDERERIMPL_FB80F5AD_E9FA_4F9C_B37E_CCAF20459FF5_
