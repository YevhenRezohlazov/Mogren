#include "SettingsImpl.h"

#include <Mogren/Implementation/Core.Android/AndroidCoreImpl.h>
#include <Mogren/Framework/Common/ImplementationProvider.h>
#include <Mogren/Framework/IO/FileStream.h>
#include <Mogren/Framework/Logging/Logger.h>
#include <cstdio>

namespace Settings
{
    SettingsImpl::SettingsImpl()
    {

    }

    std::unique_ptr<IO::InputStream> SettingsImpl::openSettingsInputStream(const std::string &settingsName)
    {
        auto settingsDirectoryPath = static_cast<Common::AndroidCoreImpl&>(Common::getImpl<Common::NativeCoreInterface>())
                .getSettingsDirectoryPath();
        return std::make_unique<IO::FileStream>(settingsDirectoryPath + "/" + settingsName, IO::FileMode::ReadBinary);
    }

    std::unique_ptr<IO::OutputStream> SettingsImpl::openSettingsOutputStream(const std::string &settingsName)
    {
        auto settingsDirectoryPath = static_cast<Common::AndroidCoreImpl&>(Common::getImpl<Common::NativeCoreInterface>())
                .getSettingsDirectoryPath();
        return std::make_unique<IO::FileStream>(settingsDirectoryPath + "/" + settingsName, IO::FileMode::WriteBinary);
    }

    void SettingsImpl::resetSettings(const std::string &settingsName)
    {
        auto settingsDirectoryPath = static_cast<Common::AndroidCoreImpl&>(Common::getImpl<Common::NativeCoreInterface>())
                .getSettingsDirectoryPath();
        auto fileName = settingsDirectoryPath + "/" + settingsName;

        if (remove(fileName.c_str()) != 0)
        {
            Logging::Logger::writeError("Can't remove settings file (%s).", settingsName.c_str());
        }
    }
}
