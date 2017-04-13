#include "SettingsImpl.h"
#include <Windows.h>
#include <Mogren/Framework/IO/FileStream.h>

namespace Settings
{
    namespace
    {
        BOOL DirectoryExists(const std::string & path)
        {
            DWORD dwAttrib = GetFileAttributesA(path.c_str());

            return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
                (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
        }
    }

    SettingsImpl::SettingsImpl()
    {
    }

    std::unique_ptr<IO::InputStream> SettingsImpl::openSettingsInputStream(const std::string & settingsName)
    {
        auto result = std::make_unique<IO::FileStream>("Settings\\" + settingsName, IO::FileMode::ReadBinary);
        return result->canRead() ? std::move(result) : nullptr;
    }

    std::unique_ptr<IO::OutputStream> SettingsImpl::openSettingsOutputStream(const std::string & settingsName)
    {
        if (!DirectoryExists("Settings"))
        {
            CreateDirectoryA("Settings", NULL);
        }

        return std::make_unique<IO::FileStream>("Settings\\" + settingsName, IO::FileMode::WriteBinary);
    }

    void SettingsImpl::resetSettings(const std::string & settingsName)
    {
        DeleteFileA(("Settings\\" + settingsName).c_str());
    }
}