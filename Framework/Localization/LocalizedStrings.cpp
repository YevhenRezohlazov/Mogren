#include "LocalizedStrings.h"
#include <Mogren/Framework/Logging/Logger.h>
#include <Mogren/Framework/IO/InputStream.h>
#include <Mogren/Framework/IO/BinaryReader.h>
#include <Mogren/ThirdParty/utf8/utf8.h>

namespace Localization
{
    LocalizedStrings::LocalizedStrings(IO::InputStream &inputStream)
    {
        preloadStrings(inputStream);
    }

    void LocalizedStrings::preloadStrings(IO::InputStream &inputStream)
    {
        IO::BinaryReader reader(inputStream);
        auto keyCount = reader.read<int32_t>();

        for (int i = 0; i < keyCount; ++i)
        {
            auto keyLength = reader.read<int32_t>();
            auto key = reader.readString(keyLength);

            auto countValues = reader.read<int32_t>();

            for (int j = 0; j < countValues; ++j)
            {
                auto valueLength = reader.read<int32_t>();
                auto valueUtf8 = reader.readString(valueLength);
                std::wstring value;

                static_assert(sizeof(std::wstring::value_type) == 2 || sizeof(std::wstring::value_type) == 4, "Invalid wide char size");

                if (sizeof(std::wstring::value_type) == 2)
                    utf8::utf8to16(valueUtf8.cbegin(), valueUtf8.cend(), std::back_inserter(value));
                else
                    utf8::utf8to32(valueUtf8.cbegin(), valueUtf8.cend(), std::back_inserter(value));

                mStringArrays[key].push_back(value);
            }
        }
    }

    LocalizedStrings::ParametrizedString LocalizedStrings::getString(const std::string& key)
    {
        return getString(key, 0);
    }

    LocalizedStrings::ParametrizedString LocalizedStrings::getString(const std::string& key, uint32_t index)
    {
        auto item = mStringArrays.find(key);

        if (item != mStringArrays.end() && index < item->second.size())
        {
            return item->second[index];
        }

        Logging::Logger::writeError("Cannot find localized string for key \"%s\" and index %d.", key.c_str(), index);
        assert(false && "#WRONG_STRING_KEY#");
        return L"#WRONG_STRING_KEY#";
    }

    std::vector<LocalizedStrings::ParametrizedString> LocalizedStrings::getStrings(const std::string & key)
    {
        auto item = mStringArrays.find(key);

        if (item != mStringArrays.end())
        {
            std::vector<LocalizedStrings::ParametrizedString> res;
            res.reserve(item->second.size());
            for (const auto & str : item->second) res.push_back(str);
            return res;
        }

        Logging::Logger::writeError("Cannot find localized string for key \"%s\".", key.c_str());
        assert(false && "#WRONG_STRING_KEY#");
        return{ L"#WRONG_STRING_KEY#" };
    }

    void LocalizedStrings::finalize()
    {
    }

    LocalizedStrings::ParametrizedString::ParametrizedString(const std::wstring & str)
        : std::wstring(str)
    {
    }

    LocalizedStrings::ParametrizedString::ParametrizedString(const wchar_t * str)
        : std::wstring(str)
    {
    }
}