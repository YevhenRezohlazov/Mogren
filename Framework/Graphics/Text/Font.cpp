#include "Font.h"

#include "../TextureLoader.h"
#include "../Texture.h"
#include <Mogren/Framework/Logging/Logger.h>
#include <Mogren/Framework/Logging/FunctionLoggingGuard.h>
#include <Mogren/Framework/IO/BinaryReader.h>
#include <Mogren/Framework/Math/Functions.h>
#include <functional>
#include <algorithm>

namespace Graphics
{
    namespace Text
    {
        Font::Font(float fontSize, std::shared_ptr<Texture> mapTexture, const std::vector<FontCharacterData> &charactersData)
            : mFontSize(fontSize)
            , mMapTexture(mapTexture)
            , mCharactersData()
        {
            mCharactersData.reserve(charactersData.size());
            for (const auto & charData : charactersData)
            {
                mCharactersData[charData.getCharacter()] = charData;
            }
        }

        std::unique_ptr<Font> Font::loadFromStream(IO::InputStream& stream)
        {
            IO::BinaryReader reader(stream);

            auto header = reader.readString(5);

            if (header != "MGFNT")
            {
                Logging::Logger::writeWarning("Wrong font file format.");
            }

            const float fontSize = reader.read<float>();
            const uint32_t charDataCount = reader.read<uint32_t>();

            Logging::Logger::writeInfo("Loading font. Size: %f, char count: %u.", fontSize, charDataCount);

            std::vector<FontCharacterData> charsData;

            for (uint32_t ci = 0; ci < charDataCount; ++ci)
            {
                auto ch = (wchar_t)reader.read<uint16_t>();

                Math::RectangleF mapRect;
                mapRect.position.x = reader.read<float>();
                mapRect.position.y = reader.read<float>();
                mapRect.size.width = reader.read<float>();
                mapRect.size.height = reader.read<float>();

                Math::RectangleF rangeRect;
                rangeRect.position.x = reader.read<float>();
                rangeRect.position.y = reader.read<float>();
                rangeRect.size.width = reader.read<float>();
                rangeRect.size.height = reader.read<float>();

                charsData.push_back(FontCharacterData(ch, mapRect, rangeRect));
            }

            // size in bytes
            uint32_t mapImageSize = reader.read<uint32_t>();
            Logging::Logger::writeInfo("Loading map image. Image size in bytes: %u", mapImageSize);
            
            std::shared_ptr<Texture> mapTexture(static_cast<Texture*>(TextureLoader().loadResource(stream).release()));

            return std::make_unique<Font>(fontSize, mapTexture, charsData);
        }

        TextMetrics Font::measureText(
            const std::wstring &text,
            float lineHeight, float maxWidth /*= 0.0f*/, float charSpacing /*= 0.0f*/, float lineSpacing /*= 0.0f*/)
        {
            DECLARE_FUNCTION_LOGGING_GUARD();

            Logging::Logger::writeInfo(
                "Measuring text. Text: %ls, font height: %f, max width: %f, charSpacing: %f, lineSpacing: %f",
                text.c_str(), lineHeight, maxWidth, charSpacing, lineSpacing);

            std::vector<std::wstring> lines;
            auto endFound = text.begin();
            auto nextFound = endFound;
            while ((nextFound = std::find(endFound, text.end(), L'\n')) != text.end())
            {
                lines.emplace_back(endFound, nextFound);
                endFound = nextFound + 1;
            }

            lines.emplace_back(endFound, nextFound);

            const auto defCharData = mCharactersData[0];
            const auto spaceCharData = getCharacterData(' ', defCharData);

            std::vector<CharacterMetrics> charMetrics;
            charMetrics.reserve(text.length());

            const float scale = lineHeight / getFontSize();

            float curHeight = 0;
            for (const auto& line : lines)
            {
                float curWidth = 0;
                int wordStart = 0;

                for (uint32_t ci = 0; ci <= line.length(); ++ci)
                {
                    if (ci == line.length() || line[ci] == L' ')
                    {
                        auto word = line.substr(wordStart, ci - wordStart);
                        wordStart = ci + 1;
                        auto wordWidth = measureWordWidth(word, curWidth == 0.0f, charSpacing, scale, defCharData);

                        if (maxWidth <= 0 || curWidth + wordWidth <= maxWidth)
                        {
                            std::function<void(wchar_t, bool)> addChar =
                                [this, &defCharData, &curWidth, curHeight, charSpacing, scale, &charMetrics](wchar_t ch, bool firstChar)
                            {
                                auto &charData = getCharacterData(ch, defCharData);
                                auto charShift = firstChar ? 0.0f : (charData.getRangeRectangle().position.x * scale);
                                Math::RectangleF texRect(
                                    Math::Point2DF(curWidth - charShift, curHeight),
                                    charData.getMapRectangle().size * scale);

                                charMetrics.push_back(CharacterMetrics(charData, texRect));
                                curWidth +=
                                    (firstChar ? charData.getRangeRectangle().position.x * scale : 0)
                                    + (charData.getRangeRectangle().size *scale).width + charSpacing;
                            };

                            bool firstChar = true;
                            for (auto ch : word)
                            {
                                addChar(ch, firstChar);
                                firstChar = false;
                            }

                            if (ci != line.length()
                                && (maxWidth <= 0 || curWidth + spaceCharData.getRangeRectangle().size.width * scale <= maxWidth))
                            {
                                addChar(' ', false);
                            }
                        }
                        else
                        {
                            curHeight += lineHeight + lineSpacing;
                            ci -= 1;
                            continue;
                        }
                    }
                }

                curHeight += lineHeight + lineSpacing;
            }

            float realWidth = 0.0f;
            if (charMetrics.empty())
            {
                realWidth = maxWidth;
            }
            else
            {
                for (const auto & cm : charMetrics)
                {
                    realWidth = Math::maximum(realWidth, cm.getTextRectangle().position.x + cm.getTextRectangle().size.width);
                }
            }

            Logging::Logger::writeInfo("Result texture size: %fx%f", realWidth, curHeight);

            return TextMetrics(std::dynamic_pointer_cast<Font>(shared_from_this()), Math::Size2DF(realWidth, curHeight), charMetrics);
        }

        void Font::finalize()
        {
            static_cast<ResourceManagement::Resource&>(*mMapTexture).finalize();
        }

        float Font::measureWordWidth(
            const std::wstring &word,
            bool isFirstWord,
            float scale,
            float charSpacing,
            const FontCharacterData &defaultChar)
        {
            float width = 0;

            for (uint32_t i = 0; i < word.length(); ++i)
            {
                auto ch = word[i];
                const auto& charData = getCharacterData(ch, defaultChar);

                if (isFirstWord && word.length() == 1)
                {
                    width += (charData.getMapRectangle().size.width) * scale;
                }
                else if (i == 0 && isFirstWord)
                {
                    width += (charData.getRangeRectangle().position.x + charData.getRangeRectangle().size.width) * scale;
                }
                else if (i == word.length() - 1)
                {
                    width += (charData.getMapRectangle().size.width - charData.getRangeRectangle().position.x) * scale;
                }
                else
                {
                    width += charData.getRangeRectangle().size.width * scale;
                }

                width += (i == word.length() - 1) ? 0 : charSpacing;
            }

            return width;
        }

        const FontCharacterData& Font::getCharacterData(
            wchar_t ch, const FontCharacterData &defaultChar)
        {
            auto res = mCharactersData.find(ch);
            return res == mCharactersData.end() ? defaultChar : res->second;
        }

        float Font::getFontSize() const
        {
            return mFontSize;
        }

        std::shared_ptr<const Texture> Font::getMapTexture() const
        {
            return mMapTexture;
        }

        std::shared_ptr<Texture> Font::getMapTexture()
        {
            return mMapTexture;
        }

        const std::unordered_map<wchar_t, FontCharacterData>& Font::getCharactersData() const
        {
            return mCharactersData;
        }
    }
}