#pragma once

#include <Mogren/Framework/Math/Rectangle.h>

namespace Graphics
{
    namespace Text
    {
        ///
        /// Container for font character data
        ///
        class FontCharacterData
        {
        private:
            wchar_t mCharacter;
            Math::RectangleF mMapRectangle;
            Math::RectangleF mRangeRectangle;

        public:
            ///
            /// Initializes a new instance of the FontCharacterData class.
            ///
            FontCharacterData();

            ///
            /// Initializes a new instance of the FontCharacterData class.
            ///
            /// \param character The character rectangle.
            /// \param mapRectangle The rectangle of this character on the font map.
            /// \param rangeRectangle The char range rectangle (rectangle of the real character body).
            FontCharacterData(wchar_t character, Math::RectangleF mapRectangle, Math::RectangleF rangeRectangle);

            ///
            /// Gets the character
            ///
            wchar_t getCharacter() const;

            ///
            /// Gets the rectangle of this character on the font map.
            ///
            Math::RectangleF getMapRectangle() const;

            ///
            /// Gets the char range rectangle (rectangle of the real character body).
            ///
            Math::RectangleF getRangeRectangle() const;
        };
    }
}

