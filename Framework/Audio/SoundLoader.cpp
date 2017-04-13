#include "SoundLoader.h"
#include "Sound.h"
#include "NativeInterface/NativeAudioInterface.h"
#include <Mogren/Framework/Common/ImplementationProvider.h>
#include <Mogren/Framework/Logging/FunctionLoggingGuard.h>

namespace Audio
{
    SoundLoader::SoundLoader()
    {
    }

    const std::vector<std::string> SoundLoader::getResourceExtensions() const
    {
        return {"wav", "ogg"};
    }

    std::unique_ptr<ResourceManagement::Resource> SoundLoader::loadResource(IO::InputStream & inputStream) const
    {
        DECLARE_FUNCTION_LOGGING_GUARD();

        auto nativeSound = Common::getImpl<NativeAudioInterface>().createSound(inputStream);
        assert(nativeSound);
        return std::make_unique<Sound>(std::move(nativeSound));
    }
}