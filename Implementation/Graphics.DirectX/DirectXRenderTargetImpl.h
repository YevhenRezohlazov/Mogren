#ifndef _RENDERTARGETIMPL_1860DD83_089C_48DA_93F4_7F36572E3433_
#define _RENDERTARGETIMPL_1860DD83_089C_48DA_93F4_7F36572E3433_

#include <Mogren/Framework/Core/Include.h>
#include <Mogren/Framework/Math/Include.h>
#include <Mogren/Framework/Graphics/Include.h>

#include <d3d11.h>

namespace Graphics
{
    class DirectXRenderTargetImpl : public Graphics::NativeInterface::NativeRenderTarget
    {
    public:
        DECLARE_SMART_PTRS_AND_TYPE_INFO(DirectXRenderTargetImpl, Graphics::NativeInterface::NativeRenderTarget)

    private:
        ID3D11RenderTargetView *mRenderTargetView;
        Math::Size2DI mSize;
        bool mSuppressDestruction;

    protected:
        DirectXRenderTargetImpl();

        void init(ID3D11RenderTargetView *renderTargetView, const Math::Size2DI &size, bool suppressDestruction);

    public:
        static Ptr create(ID3D11RenderTargetView *renderTargetView, const Math::Size2DI &size, bool suppressDestruction);

        ID3D11RenderTargetView* getRenderTargetView();

        virtual int getWidth() const;
        virtual int getHeight() const;

        ~DirectXRenderTargetImpl();
    };
}

#endif // _RENDERTARGETIMPL_1860DD83_089C_48DA_93F4_7F36572E3433_