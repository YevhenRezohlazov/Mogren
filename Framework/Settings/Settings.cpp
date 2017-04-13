#include "Settings.h"
#include "NativeInterface/NativeSettingsInterface.h"
#include <Mogren/Framework/Common/ImplementationProvider.h>
#include <Mogren/Framework/Logging/Logger.h>
#include <Mogren/Framework/Logging/FunctionLoggingGuard.h>

namespace Settings
{
    void saveSettings(const std::string &settingsName, SettingsContainer &settingsContainer)
    {
        DECLARE_FUNCTION_LOGGING_GUARD();
        Logging::Logger::writeInfo("Saving settings \"%s\"", settingsName.c_str());

        auto outputStream = Common::getImpl<NativeSettingsIntarface>().openSettingsOutputStream(settingsName);

        if (outputStream && outputStream->canWrite())
        {
            settingsContainer.saveSettings(*outputStream);
        }
    }

    bool loadSettings(const std::string &settingsName, SettingsContainer &settingsContainer)
    {
        DECLARE_FUNCTION_LOGGING_GUARD();
        Logging::Logger::writeInfo("Loading settings \"%s\"", settingsName.c_str());

        auto inputStream = Common::getImpl<NativeSettingsIntarface>().openSettingsInputStream(settingsName);

        if (inputStream && inputStream->canRead())
        {
            settingsContainer.loadSettings(*inputStream);
            return true;
        }
        else
        {
            Logging::Logger::writeInfo("Can't find settings with name \"%s\". Settings are not loaded.", settingsName.c_str());
            return false;
        }
    }

    void resetSettings(const std::string &settingsName)
    {
        Common::getImpl<NativeSettingsIntarface>().resetSettings(settingsName);
    }
}