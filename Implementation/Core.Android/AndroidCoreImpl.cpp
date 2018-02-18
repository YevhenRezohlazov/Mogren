#include "AndroidCoreImpl.h"
#include <Mogren/Framework/Logging/Logger.h>
#include <Mogren/Implementation/Graphics.OpenGL/OpenGLGraphicsImpl.h>
#include <cassert>
#include <android/native_activity.h>
#include <android/window.h>

namespace Common
{
	AndroidCoreImpl::AndroidCoreImpl()
	{
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

    Math::Size2DI AndroidCoreImpl::getScreenSize() const
    {
        return mScreenSize;
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
                    destroyEGL();
                    return;
                }
            }

            render();
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
                    that->initEGL();
                    if (!that->mAppInitialized) {
                        that->mInitializationCallback();
                        that->mAppInitialized = true;
                    } else {
                        Graphics::OpenGLGraphicsImpl::reloadResources();
                    }
                    that->mDrawing = true;
                    that->render();
                }
                break;
            case APP_CMD_TERM_WINDOW:
                // The window is being hidden or closed, clean it up.
                Logging::Logger::writeInfo("ANDROID COMMAND APP_CMD_TERM_WINDOW");
                that->mDrawing = false;
                that->destroyEGL();
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
        if (mDisplay == nullptr)
        {
            // No display.
            return;
        }

        mRenderCallback();
        eglSwapBuffers(mDisplay, mSurface);
    }

    void AndroidCoreImpl::initEGL()
    {
        const EGLint attribs[] = {
                EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_BLUE_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_RED_SIZE, 8,
                EGL_NONE
        };

        EGLint w, h, format;
        EGLint numConfigs;
        EGLConfig config;

        mDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);

        eglInitialize(mDisplay, 0, 0);

        /* Here, the application chooses the configuration it desires.
         * find the best match if possible, otherwise use the very first one
         */
        eglChooseConfig(mDisplay, attribs, nullptr,0, &numConfigs);
        std::unique_ptr<EGLConfig[]> supportedConfigs(new EGLConfig[numConfigs]);
        assert(supportedConfigs);
        eglChooseConfig(mDisplay, attribs, supportedConfigs.get(), numConfigs, &numConfigs);
        assert(numConfigs);

        int i = 0;
        for (; i < numConfigs; i++)
        {
            auto& cfg = supportedConfigs[i];
            EGLint r, g, b, d;
            if (eglGetConfigAttrib(mDisplay, cfg, EGL_RED_SIZE, &r)   &&
                eglGetConfigAttrib(mDisplay, cfg, EGL_GREEN_SIZE, &g) &&
                eglGetConfigAttrib(mDisplay, cfg, EGL_BLUE_SIZE, &b)  &&
                eglGetConfigAttrib(mDisplay, cfg, EGL_DEPTH_SIZE, &d) &&
                r == 8 && g == 8 && b == 8 && d == 0 )
            {
                config = supportedConfigs[i];
                break;
            }
        }

        if (i == numConfigs)
        {
            config = supportedConfigs[0];
        }

        /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
         * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
         * As soon as we picked a EGLConfig, we can safely reconfigure the
         * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
        eglGetConfigAttrib(mDisplay, config, EGL_NATIVE_VISUAL_ID, &format);
        mSurface = eglCreateWindowSurface(mDisplay, config, mAndroidApp->window, NULL);
        const EGLint attrib_list [] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
        mContext = eglCreateContext(mDisplay, config, NULL, attrib_list);

        if (eglMakeCurrent(mDisplay, mSurface, mSurface, mContext) == EGL_FALSE)
        {
            assert("Unable to eglMakeCurrent");
        }

        eglQuerySurface(mDisplay, mSurface, EGL_WIDTH, &w);
        eglQuerySurface(mDisplay, mSurface, EGL_HEIGHT, &h);

        mScreenSize = Math::Size2DI(w, h);

        // Check openGL on the system
        auto opengl_info = {GL_VENDOR, GL_RENDERER, GL_VERSION, GL_EXTENSIONS};

        for (auto name : opengl_info)
        {
            auto info = glGetString(name);
            Logging::Logger::writeInfo("OpenGL Info: %s", info);
        }
        // Initialize GL state.
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void AndroidCoreImpl::destroyEGL()
    {
        if (mDisplay != EGL_NO_DISPLAY)
        {
            eglMakeCurrent(mDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
            if (mContext != EGL_NO_CONTEXT)
            {
                eglDestroyContext(mDisplay, mContext);
            }

            if (mSurface != EGL_NO_SURFACE)
            {
                eglDestroySurface(mDisplay, mSurface);
            }

            eglTerminate(mDisplay);
        }

        mDisplay = EGL_NO_DISPLAY;
        mContext = EGL_NO_CONTEXT;
        mSurface = EGL_NO_SURFACE;
    }

    void AndroidCoreImpl::keepDeviceAwake(bool keep)
    {
        ANativeActivity_setWindowFlags(
                mAndroidApp->activity,
                keep ? AWINDOW_FLAG_KEEP_SCREEN_ON : 0,
                keep ? 0 : AWINDOW_FLAG_KEEP_SCREEN_ON);
    }
}
