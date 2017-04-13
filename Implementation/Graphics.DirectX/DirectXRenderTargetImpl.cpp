#include "PrecompiledHeader.h"
#include "DirectXRenderTargetImpl.h"

namespace Graphics
{
    DirectXRenderTargetImpl::DirectXRenderTargetImpl()
    {
    }

    void DirectXRenderTargetImpl::init(ID3D11RenderTargetView *renderTargetView, const Math::Size2DI &size, bool suppressDestruction)
    {
        mRenderTargetView = renderTargetView;
        mSize = size;
        mSuppressDestruction = suppressDestruction;
    }

    DirectXRenderTargetImpl::Ptr DirectXRenderTargetImpl::create(ID3D11RenderTargetView *renderTargetView, const Math::Size2DI &size, bool suppressDestruction)
    {
        INSERT_CREATION_CODE(DirectXRenderTargetImpl, renderTargetView, size, suppressDestruction)
    }

    int DirectXRenderTargetImpl::getWidth() const
    {
        return mSize.width;
    }

    int DirectXRenderTargetImpl::getHeight() const
    {
        return mSize.width;
    }

    DirectXRenderTargetImpl::~DirectXRenderTargetImpl()
    {
        if (!mSuppressDestruction)
        {
            mRenderTargetView->Release();
        }
    }

    ID3D11RenderTargetView* DirectXRenderTargetImpl::getRenderTargetView()
    {
        return mRenderTargetView;
    }
}