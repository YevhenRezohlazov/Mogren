#pragma once

#include <Mogren/Framework/ResourceManagement/Resource.h>
#include "FontCharacterData.h"
#include "TextMetrics.h"
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

namespace IO
{
    class InputStream;
}

namespace Graphics
{
    class Texture;

    namespace Text
    {
        ///
        /// Font class, which is used to create text textures
        ///
        class Font
            : public ResourceManagement::Resource
        {
        public:
            ///
            /// Initializes a new instance of the Font class.
            ///
            /// \param maps The font character maps.
            Font(float fontSize, std::shared_ptr<Texture> mapTexture, const std::vector<FontCharacterData> &charactersData);

            ///
            /// Loads the font from specified stream.
            ///
            /// \param stream The source stream.
            ///
            static std::unique_ptr<Font> loadFromStream(IO::InputStream &stream);

            ///
            /// Gets the size of the font (relative to texture size).
            ///
            float getFontSize() const;

            ///
            /// Gets the font map texture.
            ///
            std::shared_ptr<const Texture> getMapTexture() const;
            std::shared_ptr<Texture> getMapTexture();

            ///
            /// Gets the font map characters data.
            ///
            const std::unordered_map<wchar_t, FontCharacterData>& getCharactersData() const;

            ///
            /// Measures the text using this font.
            ///
            /// \param text The text to be measured.
            /// \param lineHeight The text line height.
            /// \param maxWidth Maximal text width or 0.0f, if width isn't limited.
            /// \param charSpacing The additional spacing between characters in line.
            /// \param lineSpacing The additional spacing between lines.
            /// \returns Text metrics.
            TextMetrics measureText(const std::wstring &text, float lineHeight = 1.0f, float maxWidth = 0.0f, float charSpacing = 0.0f, float lineSpacing = 0.0f);

        protected:
            virtual void finalize() override;

        private:
            ///
            /// Measures the width of the word.
            ///
            /// \param word The word.
            /// \param isFirstWord Set to \a true, if given word is the first word in the line.
            /// \param scale The font scale.
            /// \param charSpacing The character spacing.
            /// \param charsData The chars data.
            /// \param defaultChar The default char.
            ///
            float measureWordWidth(
                const std::wstring &word,
                bool isFirstWord,
                float scale,
                float charSpacing,
                const FontCharacterData &defaultChar);

            ///
            /// Gets the character data.
            ///
            /// \param ch The character.
            /// \param charsData The chars data.
            /// \param defaultChar The default char data.
            ///
            const FontCharacterData& getCharacterData(
                wchar_t ch, const FontCharacterData &defaultChar);

        private:
            float mFontSize;
            int mFontHeight;
            std::shared_ptr<Texture> mMapTexture;
            std::unordered_map<wchar_t, FontCharacterData> mCharactersData;
        };
    }
}

