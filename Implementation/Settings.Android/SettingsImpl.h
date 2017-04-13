#pragma once
#include <Mogren/Framework/Settings/NativeInterface/NativeSettingsInterface.h>
#include <string>

namespace Settings
{
    class SettingsImpl : public Settings::NativeSettingsIntarface
    {
    public:
        SettingsImpl();

        virtual std::unique_ptr<IO::InputStream> openSettingsInputStream(const std::string &settingsName) override;

        virtual std::unique_ptr<IO::OutputStream> openSettingsOutputStream(const std::string &settingsName) override;

        virtual void resetSettings(const std::string &settingsName) override;

    };
}
