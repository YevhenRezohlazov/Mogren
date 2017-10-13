#include "SettingsImpl.h"
#include <Mogren/Framework/IO/FileStream.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

namespace Settings
{
    SettingsImpl::SettingsImpl()
    {
    }

    std::unique_ptr<IO::InputStream> SettingsImpl::openSettingsInputStream(const std::string & settingsName)
    {
        auto result = std::make_unique<IO::FileStream>("Settings/" + settingsName, IO::FileMode::ReadBinary);
        return result->canRead() ? std::move(result) : nullptr;
    }

    std::unique_ptr<IO::OutputStream> SettingsImpl::openSettingsOutputStream(const std::string & settingsName)
    {
        struct stat st;
        if (stat("settings", &st) != 0)
        {
            /* Directory does not exist. EEXIST for race condition */
            mkdir("settings", 0777);
        }

        return std::make_unique<IO::FileStream>("settings/" + settingsName, IO::FileMode::WriteBinary);
    }

    void SettingsImpl::resetSettings(const std::string & settingsName)
    {
        remove(("settings/" + settingsName).c_str());
    }
}
