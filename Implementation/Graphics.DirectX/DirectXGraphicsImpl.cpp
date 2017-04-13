#include "PrecompiledHeader.h"
#include "DirectXGraphicsImpl.h"

#include "DirectXRenderTargetImpl.h"
#include "DirectXRendererImpl.h"

namespace Graphics
{
    using namespace NativeInterface;

    DirectXGraphicsImpl * DirectXGraphicsImpl::mInstance;

    DirectXGraphicsImpl::DirectXGraphicsImpl()
    {
        mInstance = this;
    }

    void DirectXGraphicsImpl::init(HWND renderWindow)
    {
        if (FAILED(initializeDirectXDevice(renderWindow)))
        {
            Logging::Logger::writeError(L"Can't initialize DirectX device.");
        }

        mRenderer = DirectXRendererImpl::create();
    }

    DirectXGraphicsImpl::Ptr DirectXGraphicsImpl::create(HWND renderWindow)
    {
        INSERT_CREATION_CODE(DirectXGraphicsImpl, renderWindow)
    }

    NativeVertexBuffer::Ptr DirectXGraphicsImpl::createVertexBuffer(const PrimitiveTypes::VertexStructureDesc &vertexStructureDesc, std::size_t vertexStructSize, std::size_t countElems, bool isDynamic)
    {
        return nullptr;
    }

    NativeIndexBuffer::Ptr DirectXGraphicsImpl::createIndexBuffer(std::size_t countElems, bool isDynamic)
    {
        return nullptr;
    }

    NativeRenderer* DirectXGraphicsImpl::getRenderer()
    {
        return mRenderer;
    }

    NativeTexture::Ptr DirectXGraphicsImpl::loadTexture(IO::InputStream *stream, std::size_t dataLength)
    {
        return nullptr;
    }

    NativeShaderProgram::Ptr DirectXGraphicsImpl::compileShaderProgram(IO::InputStream *stream, std::size_t dataLength)
    {
        return nullptr;
    }

    void DirectXGraphicsImpl::createRenderTargetTexture(int width, int height, NativeRenderTarget::Ptr &renderTarget, NativeTexture::Ptr &texture)
    {
    }

    NativeRenderTarget* DirectXGraphicsImpl::getDisplayRenderTarget()
    {
        return mDefaultRenderTarget;
    }

    Math::Size2DI DirectXGraphicsImpl::getMaxTextureSize() const
    {
        return Math::Size2DI();
    }

    HRESULT DirectXGraphicsImpl::initializeDirectXDevice(HWND renderWindow)
    {
        HRESULT hr = S_OK;

        RECT rc;
        GetClientRect( renderWindow, &rc );
        UINT width = rc.right - rc.left;
        UINT height = rc.bottom - rc.top;

        UINT createDeviceFlags = 0;
#ifdef _DEBUG
        createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        D3D_DRIVER_TYPE driverTypes[] =
        {
            D3D_DRIVER_TYPE_HARDWARE,
            D3D_DRIVER_TYPE_WARP,
            D3D_DRIVER_TYPE_REFERENCE,
        };
        UINT numDriverTypes = ARRAYSIZE( driverTypes );

        D3D_FEATURE_LEVEL featureLevels[] =
        {
            D3D_FEATURE_LEVEL_9_3
        };
        UINT numFeatureLevels = ARRAYSIZE( featureLevels );

        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory( &sd, sizeof( sd ) );
        sd.BufferCount = 1;
        sd.BufferDesc.Width = width;
        sd.BufferDesc.Height = height;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = renderWindow;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;

        for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
        {
            auto driverType = driverTypes[driverTypeIndex];
            hr = D3D11CreateDeviceAndSwapChain( NULL, driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
                D3D11_SDK_VERSION, &sd, &mSwapChain, &mD3DDevice, nullptr, &mDeviceContext );
            if( SUCCEEDED( hr ) )
                break;
        }
        if( FAILED( hr ) )
            return hr;

        // Create a render target view
        ID3D11Texture2D* pBackBuffer = NULL;
        hr = mSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
        if( FAILED( hr ) )
            return hr;

        hr = mD3DDevice->CreateRenderTargetView( pBackBuffer, NULL, &mRenderTargetView );
        pBackBuffer->Release();
        if( FAILED( hr ) )
            return hr;

        mDeviceContext->OMSetRenderTargets( 1, &mRenderTargetView, NULL );

        mDefaultRenderTarget = DirectXRenderTargetImpl::create(mRenderTargetView, Core::getNativeCoreInterface()->getScreenSize(), true);

        // Setup the viewport
        D3D11_VIEWPORT vp;
        vp.Width = (FLOAT)width;
        vp.Height = (FLOAT)height;
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        vp.TopLeftX = 0;
        vp.TopLeftY = 0;
        mDeviceContext->RSSetViewports( 1, &vp );

        return hr;
    }

    DirectXGraphicsImpl::~DirectXGraphicsImpl()
    {
        mInstance = nullptr;
    }

    DirectXGraphicsImpl * DirectXGraphicsImpl::getInstance()
    {
        return mInstance;
    }

    ID3D11Device* DirectXGraphicsImpl::getD3DDevice()
    {
        return mD3DDevice;
    }

    ID3D11DeviceContext* DirectXGraphicsImpl::getDeviceContext()
    {
        return mDeviceContext;
    }

    IDXGISwapChain* DirectXGraphicsImpl::getSwapChain()
    {
        return mSwapChain;
    }

    ID3D11RenderTargetView* DirectXGraphicsImpl::getRenderTargetView()
    {
        return mRenderTargetView;
    }

    void DirectXGraphicsImpl::onFrameDrawingFinished()
    {
        mSwapChain->Present(0, 0);
    }
}