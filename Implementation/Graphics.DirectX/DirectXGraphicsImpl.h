#ifndef _DIRECTXGRAPHICSIMPL_13682995_0233_4C61_8A81_B647AE98C40A_
#define _DIRECTXGRAPHICSIMPL_13682995_0233_4C61_8A81_B647AE98C40A_

#include <Mogren/Framework/Core/Include.h>
#include <Mogren/Framework/Graphics/Include.h>

#include <Windows.h>
#include <d3d11.h>

namespace Graphics
{
    class DirectXRenderTargetImpl;
    class DirectXRendererImpl;

    class DirectXGraphicsImpl : public Graphics::NativeInterface::NativeGraphicsInterface
    {
    public:
        DECLARE_SMART_PTRS_AND_TYPE_INFO(DirectXGraphicsImpl, Graphics::NativeInterface::NativeGraphicsInterface)

    private:
        static DirectXGraphicsImpl *mInstance;

        ID3D11Device*           mD3DDevice;
        ID3D11DeviceContext*    mDeviceContext;
        IDXGISwapChain*         mSwapChain;
        ID3D11RenderTargetView* mRenderTargetView;

        Core::SharedPtr<DirectXRendererImpl> mRenderer;
        Core::SharedPtr<DirectXRenderTargetImpl> mDefaultRenderTarget;

    protected:
        DirectXGraphicsImpl();

        void init(HWND renderWindow);

    public:
        static Ptr create(HWND renderWindow);

        static DirectXGraphicsImpl *getInstance();

        ID3D11Device* getD3DDevice();
        ID3D11DeviceContext* getDeviceContext();
        IDXGISwapChain* getSwapChain();
        ID3D11RenderTargetView* getRenderTargetView();

        virtual NativeInterface::NativeVertexBuffer::Ptr createVertexBuffer(const PrimitiveTypes::VertexStructureDesc &vertexStructureDesc, std::size_t vertexStructSize, std::size_t countElems, bool isDynamic);

        virtual NativeInterface::NativeIndexBuffer::Ptr createIndexBuffer(std::size_t countElems, bool isDynamic);

        virtual NativeInterface::NativeRenderer* getRenderer();

        virtual NativeInterface::NativeTexture::Ptr loadTexture(IO::InputStream *stream, std::size_t dataLength);

        virtual NativeInterface::NativeShaderProgram::Ptr compileShaderProgram(IO::InputStream *stream, std::size_t dataLength);

        virtual void createRenderTargetTexture(int width, int height, NativeInterface::NativeRenderTarget::Ptr &renderTarget, NativeInterface::NativeTexture::Ptr &texture);

        virtual NativeInterface::NativeRenderTarget* getDisplayRenderTarget();

        virtual Math::Size2DI getMaxTextureSize() const;

        virtual void onFrameDrawingFinished();

        ~DirectXGraphicsImpl();

    private:
        HRESULT initializeDirectXDevice(HWND renderWindow);
    };
}

#endif // _DIRECTXGRAPHICSIMPL_13682995_0233_4C61_8A81_B647AE98C40A_