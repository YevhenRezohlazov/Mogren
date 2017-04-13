#include <android_native_app_glue.h>
#include <Mogren/Framework/App/Application.h>
#include <Mogren/Framework/Common/ImplementationProvider.h>
#include <Mogren/Implementation/Core.Android/AndroidCoreImpl.h>
#include <Mogren/Implementation/ResourceManagement.Android/ResourceManagerImpl.h>
#include <Mogren/Implementation/Audio.OpenAL/OpenALAudioImpl.h>
#include <Mogren/Implementation/Graphics.OpenGL/OpenGLGraphicsImpl.h>
#include <Mogren/Implementation/Settings.Android/SettingsImpl.h>

#include <Mogren/Framework/Logging/Logger.h>
#include <Mogren/Implementation/Logging.Android/AndroidLogWriter.h>

#include <memory>

std::unique_ptr<App::Application> createApplication();

void android_main(android_app* state)
{
    // Make sure glue isn't stripped.
    app_dummy();

    Common::ImplementationHolder<Common::NativeCoreInterface> coreImplHolder(
            std::make_unique<Common::AndroidCoreImpl>());
    Common::ImplementationHolder<ResourceManagement::NativeResourceManager>resManImplHolder(
            std::make_unique<ResourceManagement::ResourceManagerImpl>());
    Common::ImplementationHolder<Graphics::NativeGraphicsInterface> glGraphicsImplHolder(
            std::make_unique<Graphics::OpenGLGraphicsImpl>());
    Common::ImplementationHolder<Audio::NativeAudioInterface> alAudioImplHolder(
            std::make_unique<Audio::OpenALAudioImpl>());
    Common::ImplementationHolder<Settings::NativeSettingsIntarface> settingsImplHolder(
            std::make_unique<Settings::SettingsImpl>());

    Logging::Logger::addLogWriter(std::make_unique<Logging::AndroidLogWriter>());

    App::Application::setup(createApplication);
    static_cast<Common::AndroidCoreImpl&>(Common::getImpl<Common::NativeCoreInterface>()).run(state);
}
