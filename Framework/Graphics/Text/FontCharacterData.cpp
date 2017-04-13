#include "FontCharacterData.h"

namespace Graphics
{
    namespace Text
    {
        FontCharacterData::FontCharacterData(wchar_t character, Math::RectangleF mapRectangle, Math::RectangleF rangeRectangle)
            : mCharacter(character), mMapRectangle(mapRectangle), mRangeRectangle(rangeRectangle)
        {
        }

        FontCharacterData::FontCharacterData()
        {
        }

        wchar_t FontCharacterData::getCharacter() const
        {
            return mCharacter;
        }

        Math::RectangleF FontCharacterData::getMapRectangle() const
        {
            return mMapRectangle;
        }

        Math::RectangleF FontCharacterData::getRangeRectangle() const
        {
            return mRangeRectangle;
        }
    }
}