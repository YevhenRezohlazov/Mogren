#pragma once

#include "CharacterMetrics.h"

#include <Mogren/Framework/Math/Vector2D.h>
#include <vector>
#include <memory>

namespace Graphics
{
    namespace Text
    {
        class Font;

        ///
        /// Represents result of text measurement performed by Font class.
        ///
        class TextMetrics
        {
        public:
            ///
            /// Initializes a new instance of the TextMetrics class.
            ///
            /// \param totalSize The total text size.
            /// \param characterMetrics The character metrics.
            /// \param font The font used to create text metrics.
            TextMetrics(
                const std::shared_ptr<const Font> &font,
                const Math::Size2DF &totalSize,
                const std::vector<CharacterMetrics> &characterMetrics);

            ///
            /// Gets the font.
            ///
            const std::shared_ptr<const Font>& getFont() const;

            ///
            /// Gets the total text size in pixels.
            ///
            const Math::Size2DF& getTotalSize() const;

            ///
            /// Gets the metrics for each text character.
            ///
            const std::vector<CharacterMetrics>& getCharacterMetrics() const;

        private:
            std::shared_ptr<const Font> mFont;
            Math::Size2DF mTotalSize;
            std::vector<CharacterMetrics> mCharacterMetrics;
        };
    }
}

