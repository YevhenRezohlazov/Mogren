#pragma once

#include <Mogren/Framework/IO/InputStream.h>
#include <Mogren/Framework/IO/OutputStream.h>

#include <vector>
#include <string>

namespace Settings
{
    class SettingsContainer
    {
    public:
        SettingsContainer();
        
        ///
        /// Loads the settings from the given stream
        ///
        void loadSettings(IO::InputStream &stream);

        ///
        /// Saves the settings to the given stream.
        ///
        void saveSettings(IO::OutputStream &stream);

        ///
        /// Returns the settings version (should be baseClass::getVersion() + 1).
        ///
        virtual uint32_t getVersion() const;

    protected:
        uint32_t getMaxSettingsVersion() const;

        ///
        /// Returns the input stream to read settings from.
        ///
        IO::InputStream &getInputStream();

        ///
        /// Returns the input stream to write settings to.
        ///
        IO::OutputStream &getOutputStream();

        ///
        /// Returns \a true if the settings should be saved or false, if the settings should be loaded.
        ///
        bool isSaving() const;

        ///
        /// When overridden in derived classes implements saving and loading of the settings.
        ///
        virtual void saveOrLoadSettings() = 0;

        template<typename T>
        void saveOrLoadSetting(T &setting);

        template<typename T>
        void saveSetting(const T &setting);

        template<typename T>
        void saveSetting(const std::vector<T> &settingList);

        void saveSetting(const std::string &string);

        void saveSetting(const std::wstring &string);

        template<typename T>
        void loadSetting(T &setting);

        template<typename T>
        void loadSetting(std::vector<T> &settingList);

        void loadSetting(std::string &string);

        void loadSetting(std::wstring &string);

    private:
        IO::InputStream *mInputStream;
        IO::OutputStream *mOutputStream;

        uint32_t mMaxSettingsVersion;
        bool mIsSaving;
    };

    template<typename T>
    inline void SettingsContainer::saveOrLoadSetting(T & setting)
    {
        if (isSaving())
        {
            saveSetting(setting);
        }
        else
        {
            loadSetting(setting);
        }
    }

    template<typename T>
    inline void SettingsContainer::saveSetting(const T & setting)
    {
        getOutputStream().write(&setting, sizeof(T));
    }

    template<typename T>
    inline void SettingsContainer::saveSetting(const std::vector<T>& settingList)
    {
        std::size_t listSize = settingList.size();
        getOutputStream().write(&listSize, sizeof(listSize));

        for (auto item : settingList)
        {
            saveSetting(item);
        }
    }

    template<typename T>
    inline void SettingsContainer::loadSetting(T & setting)
    {
        getInputStream().read(&setting, sizeof(T));
    }

    template<typename T>
    inline void SettingsContainer::loadSetting(std::vector<T>& settingList)
    {
        std::size_t listSize;
        getInputStream().read(&listSize, sizeof(listSize));
        settingList.clear();

        for (std::size_t i = 0; i < listSize; ++i)
        {
            T item;
            loadSetting(item);
            settingList.push_back(item);
        }
    }
}
