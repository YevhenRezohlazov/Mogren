#pragma once

#include <Mogren/Framework/Common/NativeInterface/NativeCoreInterface.h>
#include <Mogren/Framework/Math/Vector2D.h>
#include <Windows.h>
#include <memory>

namespace Common
{
    enum class RendererType
    {
        OpenGL,
        DirectX
    };

    class WindowsCoreImpl : public NativeCoreInterface
    {
    public:
        WindowsCoreImpl(const Math::Size2DI& screenSize, RendererType rendererType);

        void run();

        virtual void setInitializationCallback(std::function< void() > callback);

        virtual void setRenderCallback(std::function< void() > callback);

        virtual void setTouchInputCallback(
            std::function<void(Common::TouchAction /*action*/, const Math::Point2DI& /*position*/, int /*pointerId*/)> callback);

        virtual void setTerminationCallback(std::function< void() > callback);

        virtual void setBackButtonCallback(std::function<void() > callback);

        virtual void setPauseCallback(std::function<void() > callback);

        virtual void setResumeCallback(std::function<void() > callback);

        virtual Math::Size2DI getScreenSize() const;

        virtual void terminateApp();

        virtual std::string getLocaleName() const;

        HWND getDirectXWindowHandle() const;

    private:
        void callRenderCallback();
        void callTouchInputCallback(Common::TouchAction action, const Math::Point2DI& position, int pointerId);
        void callBackButtonCallback();

        static void glutMotionCallback(int x, int y);
        static void glutMouseCallback(int button, int state, int x, int y);
        static void glutKeyUpCallback(unsigned char key, int x, int y);
        static void glutRender();

        virtual void vibrateDevice(float vibrationDuration);
        virtual void keepDeviceAwake(bool keep);
        virtual void showInterstitialAd();
        virtual void showVideoAd();
        virtual void openUrl(const std::string & url);
    private:
        static WindowsCoreImpl* mInstance;

        Math::Size2DI mScreenSize;
        RendererType mRendererType;
        bool mMouseButtonPressed;

        HWND mDirectXWindowHandle;

        std::function<void() > mInitializationCallback;
        std::function<void() > mRenderCallback;
        std::function<void(Common::TouchAction, const Math::Point2DI&, int)> mTouchInputCallback;
        std::function<void() > mBackButtonCallback;
        std::function<void() > mTerminationCallback;
    };
}

