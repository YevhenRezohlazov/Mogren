#include "AndroidCoreImpl.h"
#include <Mogren/Framework/Logging/Logger.h>
#include <Mogren/Implementation/Graphics.OpenGL/OpenGLGraphicsImpl.h>
#include <cassert>
#include <android/native_activity.h>
#include <android/window.h>
#include <time.h>

namespace Common
{
    namespace
    {
        double getCurrentTime()
        {
            timespec ts;
            clock_gettime(CLOCK_REALTIME, &ts);
            return static_cast<double>(ts.tv_sec) + static_cast<double>(ts.tv_nsec) / 1e9;
        }
    }

	AndroidCoreImpl::AndroidCoreImpl()
	{
        mGLContext = ndk_helper::GLContext::GetInstance();
	}

	AndroidCoreImpl::~AndroidCoreImpl()
	{
	}

    void AndroidCoreImpl::setInitializationCallback(std::function<void()> callback)
    {
        mInitializationCallback = std::move(callback);
    }

    void AndroidCoreImpl::setRenderCallback(std::function<void()> callback)
    {
        mRenderCallback = std::move(callback);
    }

    void AndroidCoreImpl::setTouchInputCallback(
            std::function<void(TouchAction, const Math::Point2DI &, int)> callback)
    {
        mTouchInputCallback = std::move(callback);
    }

    void AndroidCoreImpl::setBackButtonCallback(std::function<void()> callback)
    {
        mBackButtonCallback = std::move(callback);
    }

    void AndroidCoreImpl::setTerminationCallback(std::function<void()> callback)
    {
        mTerminationCallback = std::move(callback);
    }

    void AndroidCoreImpl::setPauseCallback(std::function<void()> callback)
    {
        mPauseCallback = std::move(callback);
    }

    void AndroidCoreImpl::setResumeCallback(std::function<void()> callback)
    {
        mResumeCallback = std::move(callback);
    }

    void AndroidCoreImpl::terminateApp()
    {
        ANativeActivity_finish(mAndroidApp->activity);
    }

    void AndroidCoreImpl::vibrateDevice(float vibrationDuration)
    {
        auto jvm = mAndroidApp->activity->vm;
        assert(jvm);

        JNIEnv *jniEnv = nullptr;

        bool attached = false;
        switch (jvm->GetEnv((void**)&jniEnv, JNI_VERSION_1_6))
        {
        case JNI_OK:
            break;
        case JNI_EDETACHED:
            if (jvm->AttachCurrentThread(&jniEnv, nullptr)!=0)
            {
                assert("Could not attach current thread");
            }
            attached = true;
            break;
        case JNI_EVERSION:
            assert("Invalid java version");
            return;
        }

        assert(jniEnv);
        jclass activityClass = jniEnv->GetObjectClass(mAndroidApp->activity->clazz);
        jmethodID methodId = jniEnv->GetMethodID(activityClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
        jstring serviceName = jniEnv->NewStringUTF("vibrator");
        jobject vibrator = jniEnv->CallObjectMethod(mAndroidApp->activity->clazz, methodId, serviceName);
        jclass vibClass = jniEnv->GetObjectClass(vibrator);
        jmethodID vibrateMethodId = jniEnv->GetMethodID(vibClass, "vibrate", "(J)V");
        jlong vibDuration = (jlong)(1000 * vibrationDuration);
        jniEnv->CallVoidMethod(vibrator, vibrateMethodId, vibDuration);

        if (attached)
            jvm->DetachCurrentThread();
    }

    void AndroidCoreImpl::showInterstitialAd()
    {
        callVoidJavaMethod("showInterstitialAd");
    }

    void AndroidCoreImpl::openUrl(const std::string & url)
    {
        auto jvm = mAndroidApp->activity->vm;
        assert(jvm);

        JNIEnv *jniEnv = nullptr;

        bool attached = false;
        switch (jvm->GetEnv((void**)&jniEnv, JNI_VERSION_1_6))
        {
            case JNI_OK:
                break;
            case JNI_EDETACHED:
                if (jvm->AttachCurrentThread(&jniEnv, nullptr)!=0)
                {
                    assert("Could not attach current thread");
                }
                attached = true;
                break;
            case JNI_EVERSION:
                assert("Invalid java version");
                return;
        }

        assert(jniEnv);
        jclass activityClass = jniEnv->GetObjectClass(mAndroidApp->activity->clazz);
        jmethodID methodId = jniEnv->GetMethodID(activityClass, "openURL", "(Ljava/lang/String;)V");
        jstring jurl = jniEnv->NewStringUTF(url.c_str());
        jniEnv->CallVoidMethod(mAndroidApp->activity->clazz, methodId, jurl);
        jniEnv->DeleteLocalRef(jurl);
        if (attached)
            jvm->DetachCurrentThread();
    }

    Math::Size2DI AndroidCoreImpl::getScreenSize() const
    {
        return Math::Size2DI(mGLContext->GetScreenWidth(), mGLContext->GetScreenHeight());
    }

    std::string AndroidCoreImpl::getLocaleName() const
    {
        char lang[3];
        AConfiguration_getLanguage(mAndroidApp->config, lang);
        lang[2] = 0;
        return lang;
    }

    void AndroidCoreImpl::run(android_app *app)
    {
        mAndroidApp = app;
        app->onAppCmd = handleAndroidCommand;
        app->onInputEvent = handleAndroidInput;
        app->userData = this;
        mDrawing = false;
        mFpsLastTimestamp = getCurrentTime();

        while (1)
        {
            // Read all pending events.
            int events;
            struct android_poll_source* source;

            // If not animating, we will block forever waiting for events.
            // If animating, we loop until all events are read, then continue
            // to draw the next frame of animation.
            while (ALooper_pollAll(mDrawing ? 0 : -1, NULL, &events, (void**)&source) >= 0)
            {
                // Process this event.
                if (source != NULL)
                {
                    source->process(app, source);
                }

                // Check if we are exiting.
                if (app->destroyRequested != 0) {
                    mGLContext->Suspend();
                    return;
                }
            }

            render();
            ++mFrameCountSinceLastTimestamp;
            const double currentTime = getCurrentTime();
            if (currentTime - mFpsLastTimestamp >= 1.0)
            {
                Logging::Logger::writeInfo(
                        "FPS: %.1lf",
                        static_cast<double>(mFrameCountSinceLastTimestamp) / (currentTime - mFpsLastTimestamp));
                mFpsLastTimestamp = currentTime;
                mFrameCountSinceLastTimestamp = 0;
            }
        }
    }

    std::string AndroidCoreImpl::getSettingsDirectoryPath() const
    {
        return mAndroidApp->activity->internalDataPath;
    }

    AAssetManager *AndroidCoreImpl::getAssetManager()
    {
        return mAndroidApp->activity->assetManager;
    }

    void AndroidCoreImpl::handleAndroidCommand(android_app *app, int32_t cmd)
    {
        auto that = static_cast<AndroidCoreImpl*>(app->userData);

        switch (cmd)
        {
            case APP_CMD_SAVE_STATE:
                app->savedStateSize = 0;
                Logging::Logger::writeInfo("ANDROID COMMAND APP_CMD_SAVE_STATE");
                break;
            case APP_CMD_INIT_WINDOW:
                Logging::Logger::writeInfo("ANDROID COMMAND APP_CMD_INIT_WINDOW");
                // The window is being shown, get it ready.
                if (app->window != NULL)
                {
                    that->initApp(app);
                    that->mDrawing = true;
                    that->render();
                }
                break;
            case APP_CMD_TERM_WINDOW:
                // The window is being hidden or closed, clean it up.
                Logging::Logger::writeInfo("ANDROID COMMAND APP_CMD_TERM_WINDOW");
                that->mDrawing = false;
                that->mGLContext->Suspend();
                break;
            case APP_CMD_GAINED_FOCUS:
                Logging::Logger::writeInfo("ANDROID COMMAND APP_CMD_GAINED_FOCUS");
                that->mDrawing = true;
                // App gains focus
                break;
            case APP_CMD_LOST_FOCUS:
                Logging::Logger::writeInfo("ANDROID COMMAND APP_CMD_LOST_FOCUS");
                that->mDrawing = false;
                that->render();
                break;
            case APP_CMD_RESUME:
                Logging::Logger::writeInfo("ANDROID COMMAND APP_CMD_RESUME");
                that->mResumeCallback();
                break;
            case APP_CMD_PAUSE:
                Logging::Logger::writeInfo("ANDROID COMMAND APP_CMD_PAUSE");
                that->mPauseCallback();
                break;
            case APP_CMD_START:
                Logging::Logger::writeInfo("ANDROID COMMAND APP_CMD_START");
                break;
            case APP_CMD_DESTROY:
                Logging::Logger::writeInfo("ANDROID COMMAND APP_CMD_DESTROY");
                that->mTerminationCallback();
                that->mAppInitialized = false;
                that->mGLContext->Invalidate();
                break;
            case APP_CMD_CONFIG_CHANGED:
                Logging::Logger::writeInfo("ANDROID COMMAND APP_CMD_CONFIG_CHANGED");
                break;
        }
    }

    int32_t AndroidCoreImpl::handleAndroidInput(android_app *app, AInputEvent *event)
    {
        auto that = static_cast<AndroidCoreImpl*>(app->userData);

        switch (AInputEvent_getType(event))
        {
        case AINPUT_EVENT_TYPE_MOTION:
        {
            const Math::Point2DI coords(AMotionEvent_getX(event, 0), AMotionEvent_getY(event, 0));
            switch (AMotionEvent_getAction(event))
            {
            case AMOTION_EVENT_ACTION_DOWN:
                that->mTouchInputCallback(Common::TouchAction::Down, coords, 0);
                return 1;
            case AMOTION_EVENT_ACTION_UP:
                that->mTouchInputCallback(Common::TouchAction::Up, coords, 0);
                return 1;
            case AMOTION_EVENT_ACTION_MOVE:
                that->mTouchInputCallback(Common::TouchAction::Move, coords, 0);
                return 1;
            }
        }
        case AINPUT_EVENT_TYPE_KEY:
            if (AKeyEvent_getKeyCode(event) == AKEYCODE_BACK)
            {
                that->mBackButtonCallback();
                return 1;
            }
            break;
        }

        return 0;
    }

    void AndroidCoreImpl::render()
    {
        mRenderCallback();

        if (EGL_SUCCESS != mGLContext->Swap()) {
            Graphics::OpenGLGraphicsImpl::reloadResources();
        }
    }

    void AndroidCoreImpl::initApp(android_app *app)
    {
        if (!mAppInitialized) {
            mGLContext->Init(app->window);
            mInitializationCallback();
            mAppInitialized = true;
        } else if(app->window != mGLContext->GetANativeWindow()) {
            // Re-initialize ANativeWindow.
            // On some devices, ANativeWindow is re-created when the app is resumed
            assert(mGLContext->GetANativeWindow());
            mGLContext->Invalidate();
            mGLContext->Init(app->window);
            Graphics::OpenGLGraphicsImpl::reloadResources();
        } else {
            // initialize OpenGL ES and EGL
            if (EGL_SUCCESS == mGLContext->Resume(app->window)) {
                Graphics::OpenGLGraphicsImpl::reloadResources();
            } else {
                assert(0);
            }
        }
    }

    void AndroidCoreImpl::keepDeviceAwake(bool keep)
    {
        ANativeActivity_setWindowFlags(
                mAndroidApp->activity,
                keep ? AWINDOW_FLAG_KEEP_SCREEN_ON : 0,
                keep ? 0 : AWINDOW_FLAG_KEEP_SCREEN_ON);
    }

    void AndroidCoreImpl::callVoidJavaMethod(const std::string &methodName)
    {
        auto jvm = mAndroidApp->activity->vm;
        assert(jvm);

        JNIEnv *jniEnv = nullptr;

        bool attached = false;
        switch (jvm->GetEnv((void**)&jniEnv, JNI_VERSION_1_6))
        {
            case JNI_OK:
                break;
            case JNI_EDETACHED:
                if (jvm->AttachCurrentThread(&jniEnv, nullptr)!=0)
                {
                    assert("Could not attach current thread");
                }
                attached = true;
                break;
            case JNI_EVERSION:
                assert("Invalid java version");
                return;
        }

        assert(jniEnv);
        jclass activityClass = jniEnv->GetObjectClass(mAndroidApp->activity->clazz);
        jmethodID methodId = jniEnv->GetMethodID(activityClass, methodName.c_str(), "()V");
        jniEnv->CallVoidMethod(mAndroidApp->activity->clazz, methodId);

        if (attached)
            jvm->DetachCurrentThread();
    }

    void AndroidCoreImpl::showVideoAd() {
        callVoidJavaMethod("showVideoAd");
    }
}
