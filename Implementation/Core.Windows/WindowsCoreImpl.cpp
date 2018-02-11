#include "WindowsCoreImpl.h"
#include <Mogren/ThirdParty/freeglut/include/freeglut.h>

namespace
{
    LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );

    //--------------------------------------------------------------------------------------
    // Register class and create window
    //--------------------------------------------------------------------------------------
    HWND InitWindow(const Math::Size2DI &size)
    {
        // Register class
        WNDCLASSEX wcex;
        ZeroMemory(&wcex, sizeof(wcex));

        wcex.cbSize = sizeof( WNDCLASSEX );
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;

        HINSTANCE hInstance = GetModuleHandle(nullptr);

        wcex.hIcon = LoadIcon( hInstance, ( LPCTSTR )IDI_APPLICATION );
        wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
        wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
        wcex.lpszMenuName = NULL;
        wcex.lpszClassName = L"MogrenDirectXWindowClass";
        wcex.hIconSm = LoadIcon( wcex.hInstance, ( LPCTSTR )IDI_APPLICATION );
        if( !RegisterClassEx( &wcex ) )
            return 0;

        // Create window
        RECT rc = { 0, 0, size.width, size.height };
        AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
        HWND hWnd = CreateWindow( L"MogrenDirectXWindowClass", L"Mogren Direct3D Window", WS_OVERLAPPED | WS_MINIMIZEBOX | WS_CAPTION | WS_SYSMENU,
            CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
            NULL );

        ShowWindow(hWnd, SW_SHOW);

        return hWnd;
    }

    //--------------------------------------------------------------------------------------
    // Called every time the application receives a message
    //--------------------------------------------------------------------------------------
    LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
    {
        PAINTSTRUCT ps;
        HDC hdc;

        switch( message )
        {
        case WM_PAINT:
            hdc = BeginPaint( hWnd, &ps );
            EndPaint( hWnd, &ps );
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
        }

        return 0;
    }
}

namespace Common
{
    WindowsCoreImpl* WindowsCoreImpl::mInstance;

    WindowsCoreImpl::WindowsCoreImpl(const Math::Size2DI& screenSize, RendererType rendererType)
        : mScreenSize(screenSize), mRendererType(rendererType), mMouseButtonPressed(false)
    {
        mInstance = this;
    }

    void WindowsCoreImpl::run()
    {
        switch (mRendererType)
        {
        case Common::RendererType::OpenGL:
            {
                int argc = 0;
                char argv[1][1] = { { 0 } };

                glutInit(&argc, reinterpret_cast<char**>(argv));

                glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

                glutInitWindowSize(mScreenSize.width, mScreenSize.height);
                glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
                glutCreateWindow("Mogren Windows Demo");
                glutDisplayFunc(glutRender);
                glutMotionFunc(glutMotionCallback);
                glutMouseFunc(glutMouseCallback);
                glutKeyboardUpFunc(glutKeyUpCallback);

                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                if (mInitializationCallback)
                {
                    mInitializationCallback();
                }

                HWND hwnd = FindWindow(0, L"Mogren Windows Demo");
                LONG lStyle = GetWindowLong(hwnd, GWL_STYLE);
                lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
                SetWindowLong(hwnd, GWL_STYLE, lStyle);

                glutMainLoop();

                if (mTerminationCallback)
                {
                    mTerminationCallback();
                }
            }
            break;
        case Common::RendererType::DirectX:
            {
                mDirectXWindowHandle = InitWindow(mScreenSize);

                if (mInitializationCallback)
                {
                    mInitializationCallback();
                }

                // Main message loop
                MSG msg = {0};
                while( WM_QUIT != msg.message )
                {
                    if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
                    {
                        TranslateMessage( &msg );
                        DispatchMessage( &msg );
                    }
                    else
                    {
                        if (mRenderCallback)
                        {
                            mRenderCallback();
                        }
                    }
                }

                if (mTerminationCallback)
                {
                    mTerminationCallback();
                }
            }
            break;
        default:
            break;
        }
    }

    void WindowsCoreImpl::setInitializationCallback(std::function< void() > callback)
    {
        mInitializationCallback = callback;
    }

    void WindowsCoreImpl::setRenderCallback(std::function< void() > callback)
    {
        mRenderCallback = callback;
    }

    void WindowsCoreImpl::callRenderCallback()
    {
        if (mRenderCallback)
        {
            mRenderCallback();
        }
    }

    void WindowsCoreImpl::glutMotionCallback(int x, int y)
    {
        if (mInstance->mMouseButtonPressed)
        {
            mInstance->callTouchInputCallback(Common::TouchAction::Move, Math::Point2DI(x, y), 0);
        }
    }

    void WindowsCoreImpl::glutMouseCallback(int button, int state, int x, int y)
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            switch (state)
            {
            case GLUT_DOWN:
                mInstance->mMouseButtonPressed = true;
                mInstance->callTouchInputCallback(Common::TouchAction::Down, Math::Point2DI(x, y), 0);
                break;
            case GLUT_UP:
                mInstance->mMouseButtonPressed = false;
                mInstance->callTouchInputCallback(Common::TouchAction::Up, Math::Point2DI(x, y), 0);
                break;
            }
        }
    }

    void WindowsCoreImpl::glutRender()
    {
        mInstance->callRenderCallback();

        glutSwapBuffers();
        glutPostRedisplay();
    }

    Math::Size2DI WindowsCoreImpl::getScreenSize() const
    {
        return mScreenSize;
    }

    void WindowsCoreImpl::setTerminationCallback(std::function< void() > callback)
    {
        mTerminationCallback = callback;
    }

    void WindowsCoreImpl::setTouchInputCallback(std::function<void(Common::TouchAction /*action*/, const Math::Point2DI& /*position*/, int /*pointerId*/)> callback)
    {
        mTouchInputCallback = callback;
    }

    void WindowsCoreImpl::callTouchInputCallback(Common::TouchAction action, const Math::Point2DI& position, int pointerId)
    {
        if (mTouchInputCallback)
        {
            mTouchInputCallback(action, position, pointerId);
        }
    }

    void WindowsCoreImpl::setBackButtonCallback(std::function<void() > callback)
    {
        mBackButtonCallback = callback;
    }

    void WindowsCoreImpl::glutKeyUpCallback(unsigned char key, int x, int y)
    {
        if (key == 27 /*escape*/)
        {
            mInstance->callBackButtonCallback();
        }
    }

    void WindowsCoreImpl::callBackButtonCallback()
    {
        if (mBackButtonCallback)
        {
            mBackButtonCallback();
        }
    }

    void WindowsCoreImpl::terminateApp()
    {
        glutLeaveMainLoop();
    }

    void WindowsCoreImpl::setPauseCallback(std::function<void() > callback)
    {
    }

    void WindowsCoreImpl::setResumeCallback(std::function<void() > callback)
    {
    }

    void WindowsCoreImpl::vibrateDevice(float vibrationDuration)
    {
        // do nothing on windows
    }

    void WindowsCoreImpl::keepDeviceAwake( bool keep )
    {
        // do nothing on windows
    }

    std::string WindowsCoreImpl::getLocaleName() const
    {
        return "";
    }

    HWND WindowsCoreImpl::getDirectXWindowHandle() const
    {
        return mDirectXWindowHandle;
    }
}