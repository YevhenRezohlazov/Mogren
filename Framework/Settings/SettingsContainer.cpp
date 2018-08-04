#include "SettingsContainer.h"

namespace Settings
{
    IO::InputStream& SettingsContainer::getInputStream()
    {
        return *mInputStream;
    }

    IO::OutputStream& SettingsContainer::getOutputStream()
    {
        return *mOutputStream;
    }

    bool SettingsContainer::isSaving() const
    {
        return mIsSaving;
    }

    void SettingsContainer::saveSetting(const std::string & string)
    {
        std::size_t stringSize = string.length();
        getOutputStream().write(&stringSize, sizeof(stringSize));
        getOutputStream().write(string.c_str(), stringSize * sizeof(char));
    }

    void SettingsContainer::saveSetting(const std::wstring & string)
    {
        std::size_t stringSize = string.length();
        getOutputStream().write(&stringSize, sizeof(stringSize));
        getOutputStream().write(string.c_str(), stringSize * sizeof(wchar_t));
    }

    void SettingsContainer::loadSetting(std::string & string)
    {
        std::size_t stringSize;
        getInputStream().read(&stringSize, sizeof(stringSize));
        string.resize(stringSize);
        getInputStream().read(const_cast<char*>(string.c_str()), stringSize * sizeof(char));
    }

    void SettingsContainer::loadSetting(std::wstring & string)
    {
        std::size_t stringSize;
        getInputStream().read(&stringSize, sizeof(stringSize));
        string.resize(stringSize);
        getInputStream().read(const_cast<wchar_t*>(string.c_str()), stringSize * sizeof(wchar_t));
    }

    void SettingsContainer::loadSettings(IO::InputStream &stream)
    {
        mInputStream = &stream;
        mIsSaving = false;
        stream.read(&mMaxSettingsVersion, sizeof(mMaxSettingsVersion));
        saveOrLoadSettings();
    }

    void SettingsContainer::saveSettings(IO::OutputStream &stream)
    {
        mOutputStream = &stream;
        mIsSaving = true;
        auto version = getVersion();
        stream.write(&version, sizeof(version));
        mMaxSettingsVersion = version;
        saveOrLoadSettings();
    }

    uint32_t SettingsContainer::getVersion() const
    {
        return 0;
    }

    uint32_t SettingsContainer::getMaxSettingsVersion() const
    {
        return mMaxSettingsVersion;
    }

    SettingsContainer::SettingsContainer()
        : mInputStream(nullptr), mOutputStream(nullptr), mMaxSettingsVersion(0U), mIsSaving(false)
    {
    }
}