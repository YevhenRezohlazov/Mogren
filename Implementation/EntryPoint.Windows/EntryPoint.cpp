#include <Mogren/Framework/App/Application.h>
#include <Mogren/Framework/Common/ImplementationProvider.h>
#include <Mogren/Implementation/Core.Windows/WindowsCoreImpl.h>
#include <Mogren/Implementation/ResourceManagement.Windows/ResourceManagerImpl.h>
#include <Mogren/Implementation/Audio.OpenAL/OpenALAudioImpl.h>
#include <Mogren/Implementation/Graphics.OpenGL/OpenGLGraphicsImpl.h>
#include <Mogren/Implementation/Settings.Windows/SettingsImpl.h>

#include <Mogren/Framework/Logging/Logger.h>
#include <Mogren/Framework/Logging/DebugLogWriter.h>
#include <Mogren/Framework/Logging/FileLogger.h>

#include <memory>

std::unique_ptr<App::Application> createApplication();

int main(int argc, char **argv)
{
    Common::ImplementationHolder<Common::NativeCoreInterface> coreImplHolder(
        std::make_unique<Common::WindowsCoreImpl>(Math::Vector2DI(1280, 720), Common::RendererType::OpenGL));
    Common::ImplementationHolder<ResourceManagement::NativeResourceManager>resManImplHolder(
        std::make_unique<ResourceManagement::ResourceManagerImpl>());
    Common::ImplementationHolder<Graphics::NativeGraphicsInterface> glGraphicsImplHolder(
        std::make_unique<Graphics::OpenGLGraphicsImpl>());
    Common::ImplementationHolder<Audio::NativeAudioInterface> alAudioImplHolder(
        std::make_unique<Audio::OpenALAudioImpl>());
    Common::ImplementationHolder<Settings::NativeSettingsIntarface> settingsImplHolder(
        std::make_unique<Settings::SettingsImpl>());

    Logging::Logger::addLogWriter(std::make_unique<Logging::DebugLogWriter>());
    Logging::Logger::addLogWriter(std::make_unique<Logging::FileLogger>("LogOutput.log"));

    App::Application::setup(createApplication);
    static_cast<Common::WindowsCoreImpl&>(Common::getImpl<Common::NativeCoreInterface>()).run();
    return 0;
}