#pragma once

#include <string>
#include <memory>

namespace IO
{
    class InputStream;
    class OutputStream;
}

namespace Settings
{
    ///
    /// Native interface for settings module.
    ///
    class NativeSettingsIntarface
    {
    public:
        ///
        /// Returns the settings input stream or NULL, if no such settings were saved.
        ///
        virtual std::unique_ptr<IO::InputStream> openSettingsInputStream(const std::string &settingsName) = 0;

        ///
        /// Returns the settings output stream.
        ///
        virtual std::unique_ptr<IO::OutputStream> openSettingsOutputStream(const std::string &settingsName) = 0;

        ///
        /// Removes given settings from settings storage.
        ///
        virtual void resetSettings(const std::string &settingsName) = 0;

        virtual ~NativeSettingsIntarface() = default;
    };
}
