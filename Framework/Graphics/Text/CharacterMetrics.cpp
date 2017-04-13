#include "CharacterMetrics.h"

namespace Graphics
{
    namespace Text
    {
        CharacterMetrics::CharacterMetrics(const FontCharacterData &charData, const Math::RectangleF &textRectangle)
            : mCharacterData(charData), mTextRectangle(textRectangle)
        {
        }

        const FontCharacterData& CharacterMetrics::getCharacterData() const
        {
            return mCharacterData;
        }

        const Math::RectangleF& CharacterMetrics::getTextRectangle() const
        {
            return mTextRectangle;
        }
    }
}