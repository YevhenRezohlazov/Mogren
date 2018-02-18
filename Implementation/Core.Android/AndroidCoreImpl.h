#pragma once

#include <Mogren/Framework/Common/NativeInterface/NativeCoreInterface.h>
#include <Mogren/Framework/Math/Vector2D.h>
#include <functional>
#include <string>
#include <vector>
#include <android_native_app_glue.h>
#include <android/asset_manager.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

namespace Common
{
	class AndroidCoreImpl : public Common::NativeCoreInterface
	{
	public:
        AndroidCoreImpl();
        ~AndroidCoreImpl();

		virtual void setInitializationCallback(std::function<void()> callback) override;
		virtual void setRenderCallback(std::function<void()> callback) override;
		virtual void setTouchInputCallback(
                std::function<void(TouchAction /*action*/, const Math::Point2DI& /*position*/, int /*pointerId*/)> callback) override;
		virtual void setBackButtonCallback(std::function<void()> callback) override;
		virtual void setTerminationCallback(std::function<void()> callback) override;

		virtual void setPauseCallback(std::function<void()> callback) override;
		virtual void setResumeCallback(std::function<void()> callback) override;

		virtual void terminateApp() override;

		///
		/// Enables device vibration for given period of time.
		/// @param vibrationDuration Vibration duration in seconds.
		///
		virtual void vibrateDevice(float vibrationDuration) override;

		virtual void keepDeviceAwake(bool keep) override;

		virtual Math::Size2DI getScreenSize() const override;

		virtual std::string getLocaleName() const override;

        void run(android_app* app);

        std::string getSettingsDirectoryPath() const;

        AAssetManager* getAssetManager();

	private:
        static void handleAndroidCommand(android_app* app, int32_t cmd);
        static int32_t handleAndroidInput(android_app* app, AInputEvent* event);

        void initEGL();
        void destroyEGL();
        void render();

    private:
        android_app* mAndroidApp;

        Math::Size2DI mScreenSize;

        EGLDisplay mDisplay;
        EGLSurface mSurface;
        EGLContext mContext;
        bool mAppInitialized = false;
        bool mDrawing;

		std::function<void() > mInitializationCallback;
		std::function<void() > mRenderCallback;
		std::function<void(Common::TouchAction, const Math::Point2DI&, int)> mTouchInputCallback;
		std::function<void() > mBackButtonCallback;
		std::function<void() > mTerminationCallback;
        std::function<void() > mPauseCallback;
        std::function<void() > mResumeCallback;
    };
}

