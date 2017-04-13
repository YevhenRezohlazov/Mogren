#pragma once

#include "NativeInterface/NativeSettingsInterface.h"
#include "SettingsContainer.h"

namespace Settings
{
    ///
    /// Saves given settings with the given name.
    ///
    void saveSettings(const std::string &settingsName, SettingsContainer &settingsContainer);

    ///
    /// Loads given settings with the given name.
    ///
    bool loadSettings(const std::string &settingsName, SettingsContainer &settingsContainer);

    ///
    /// Removes settings with the given name.
    ///
    void resetSettings(const std::string &settingsName);
}
