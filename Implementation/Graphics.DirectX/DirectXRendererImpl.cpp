#include "PrecompiledHeader.h"
#include "DirectXRendererImpl.h"

#include "DirectXGraphicsImpl.h"
#include "DirectXRenderTargetImpl.h"

namespace Graphics
{
    DirectXRendererImpl::DirectXRendererImpl()
    {
    }

    void DirectXRendererImpl::init()
    {
    }

    DirectXRendererImpl::Ptr DirectXRendererImpl::create()
    {
        INSERT_CREATION_CODE(DirectXRendererImpl)
    }

    void DirectXRendererImpl::clearTarget(const PrimitiveTypes::Color &clearColor)
    {
        auto graphicsImpl = DirectXGraphicsImpl::getInstance();

        if (graphicsImpl)
        {
            graphicsImpl->getDeviceContext()->ClearRenderTargetView(
                graphicsImpl->getDisplayRenderTarget()->staticCast<DirectXRenderTargetImpl>()->getRenderTargetView(),
                (const float*)&clearColor);
        }
    }

    void DirectXRendererImpl::render()
    {
    }
}