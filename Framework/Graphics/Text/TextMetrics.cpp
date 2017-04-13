#include "TextMetrics.h"
#include "Font.h"

namespace Graphics
{
    namespace Text
    {
        TextMetrics::TextMetrics(
            const std::shared_ptr<const Font> &font,
            const Math::Size2DF &totalSize,
            const std::vector<CharacterMetrics> &characterMetrics)
        {
            mFont = font;
            mTotalSize = totalSize;
            mCharacterMetrics = characterMetrics;
        }

        const std::shared_ptr<const Font>& TextMetrics::getFont() const
        {
            return mFont;
        }

        const Math::Size2DF& TextMetrics::getTotalSize() const
        {
            return mTotalSize;
        }

        const std::vector<CharacterMetrics>& TextMetrics::getCharacterMetrics() const
        {
            return mCharacterMetrics;
        }
    }
}