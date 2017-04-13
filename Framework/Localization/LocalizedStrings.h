#pragma once

#include <Mogren/Framework/ResourceManagement/Resource.h>

#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <assert.h>

namespace IO
{
    class InputStream;
}

namespace Localization
{
    ///
    /// String localization helper class.
    ///
    class LocalizedStrings : public ResourceManagement::Resource
    {
    private:
        std::unordered_map<std::string, std::vector<std::wstring> > mStringArrays;

    public:
        class ParametrizedString : public std::wstring
        {
        public:
            ParametrizedString(const std::wstring & str);
            ParametrizedString(const wchar_t * str);
            template <typename TValue>
            ParametrizedString& set(const std::string & paramName, const TValue & value);
        };

    public:
        ///
        /// Initializes a new instance of Localizer class.
        ///
        LocalizedStrings(IO::InputStream &inputStream);

        ///
        /// Returns localized string with the specified key or the key string if no localization is found.
        /// \param key Localized string key
        ///
        ParametrizedString getString(const std::string& key);

        ///
        /// Returns localized string from the array with the specified key or the key string if no localization is found.
        /// \param key Localized string array key
        /// \param index Zero-based string index in the array
        /// TODO: Not supported now.
        ///
        ParametrizedString getString(const std::string& key, uint32_t index);

    protected:
        virtual void finalize() override;

    private:
        ///
        /// Preloads all the localized strings from resources.
        ///
        void preloadStrings(IO::InputStream &inputStream);
    };

    template<typename TValue>
    inline LocalizedStrings::ParametrizedString& LocalizedStrings::ParametrizedString
        ::set(const std::string & paramName, const TValue & value)
    {
        std::wstring wParamName;
        wParamName.reserve(paramName.size() + 2);
        wParamName.push_back(L'{');
        wParamName.append(paramName.begin(), paramName.end());
        wParamName.push_back(L'}');
        auto pos = find(wParamName);
        assert(pos);
        std::wstringstream valueStream;
        valueStream << value;
        replace(pos, wParamName.size(), std::move(valueStream).str());
        return *this;
    }
}


