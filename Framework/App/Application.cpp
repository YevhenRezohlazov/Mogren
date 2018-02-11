#include "Application.h"
#include <Mogren/Framework/Common/ImplementationProvider.h>
#include <Mogren/Framework/Common/NativeInterface/NativeCoreInterface.h>
#include <Mogren/Framework/Graphics/NativeInterface/NativeGraphicsInterface.h>
#include <Mogren/Framework/Graphics/NativeInterface/NativeRenderTarget.h>
#include <Mogren/Framework/Graphics/RenderTarget.h>
#include <Mogren/Framework/Graphics/Camera.h>
#include <Mogren/Framework/Input/InputManager.h>
#include <Mogren/Framework/Graphics/ShaderProgramLoader.h>
#include <Mogren/Framework/Graphics/TextureLoader.h>
#include <Mogren/Framework/Graphics/Text/FontLoader.h>
#include <Mogren/Framework/Audio/SoundLoader.h>
#include <Mogren/Framework/Localization/LocalizedStringsLoader.h>
#include <assert.h>

namespace App
{
    std::unique_ptr<Application> Application::mInstance;

    Application::Application()
    {
        Common::getImpl<Graphics::NativeGraphicsInterface>().initialize();

        mDisplayRenderTarget = std::make_shared<Graphics::RenderTarget>(
            Common::getImpl<Graphics::NativeGraphicsInterface>().createDisplayRenderTarget());

        getResourceManager().addResourceLoader(std::make_unique<Graphics::ShaderProgramLoader>());
        getResourceManager().addResourceLoader(std::make_unique<Graphics::TextureLoader>());
        getResourceManager().addResourceLoader(std::make_unique<Graphics::Text::FontLoader>());
        getResourceManager().addResourceLoader(std::make_unique<Audio::SoundLoader>());
        getResourceManager().addResourceLoader(std::make_unique<Localization::LocalizedStringsLoader>());
    }

    void Application::onTouch(Common::TouchAction touchAction, const Math::Point2DI &position, int pointerId)
    {
    }

    void Application::onBackButtonPress()
    {
    }

    void Application::keepDeviceAwake( bool keep )
    {
        Common::getImpl<Common::NativeCoreInterface>().keepDeviceAwake(keep);
    }

    void Application::vibrateDevice( float vibrationDuration )
    {
        Common::getImpl<Common::NativeCoreInterface>().vibrateDevice(vibrationDuration);
    }

    const Common::TimeManager& Application::getTimeManager() const
    {
        return mTimeManager;
    }

    Common::TimeManager& Application::getTimeManager()
    {
        return mTimeManager;
    }

    const ResourceManagement::ResourceManager& Application::getResourceManager() const
    {
        return mResourceManager;
    }

    ResourceManagement::ResourceManager& Application::getResourceManager()
    {
        return mResourceManager;
    }

    const Animation::AnimationManager& Application::getAnimationManager() const
    {
        return mAnimationManager;
    }

    Animation::AnimationManager& Application::getAnimationManager()
    {
        return mAnimationManager;
    }

    std::shared_ptr<Graphics::RenderTarget> Application::getDisplayRenderTarget()
    {
        return mDisplayRenderTarget;
    }

    void Application::terminate()
    {
        Common::getImpl<Common::NativeCoreInterface>().terminateApp();
    }

    void Application::prerender()
    {
        getResourceManager().finalizeResources();
        Input::InputManager::dispatchTouches();
        getAnimationManager().performAnimations(getTimeManager().getDeltaTime());
    }

    void Application::render()
    {
        for (auto camera : Graphics::Camera::getCameras())
        {
            camera->render();
        }
    }

    void Application::postrender()
    {
        mTimeManager.notifyFrameEnd();
    }

    void Application::onPause()
    {
    }

    void Application::onResume()
    {
    }

    void Application::setup(std::function<std::unique_ptr<Application>()> applicationCreator)
    {
        auto & nativeInterface = Common::getImpl<Common::NativeCoreInterface>();
        nativeInterface.setInitializationCallback([applicationCreator]() { mInstance = applicationCreator(); });
        nativeInterface.setTerminationCallback([]() { mInstance.reset(); });

        nativeInterface.setRenderCallback(
            []() { if (mInstance) { mInstance->prerender(); mInstance->render(); mInstance->postrender(); } });
        nativeInterface.setTouchInputCallback(
            [](Common::TouchAction action, const Math::Point2DI position, int pointerId)
            { if (mInstance) { mInstance->onTouch(action, position, pointerId); } });
        nativeInterface.setBackButtonCallback([]() { if (mInstance) mInstance->onBackButtonPress(); });

        nativeInterface.setPauseCallback([]() { if (mInstance) mInstance->onPause(); });
        nativeInterface.setResumeCallback([]() { if (mInstance) mInstance->onResume(); });
    }

    Application & Application::getInstance()
    {
        assert(mInstance != nullptr);
        return *mInstance;
    }
}