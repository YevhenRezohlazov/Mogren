#pragma once

#include "FontCharacterData.h"

#include <Mogren/Framework/Math/Rectangle.h>

namespace Graphics
{
    namespace Text
    {
        ///
        /// Represents metrics of the character used to create text textures.
        ///
        class CharacterMetrics
        {
        private:
            FontCharacterData mCharacterData;
            Math::RectangleF mTextRectangle;

        public:
            ///
            /// Initializes a new instance of the CharacterMetrics class.
            ///
            /// \param charData The font character data.
            /// \param textRectangle The rectangle of this character in the result text.
            CharacterMetrics(const FontCharacterData &charData, const Math::RectangleF &textRectangle);

            ///
            /// Gets the corresponding font character data.
            ///
            const FontCharacterData& getCharacterData() const;

            ///
            /// Gets the rectangle of this character in the result text.
            ///
            const Math::RectangleF& getTextRectangle() const;
        };
    }
}

