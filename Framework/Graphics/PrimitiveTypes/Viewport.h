#pragma once

#include <Mogren/Framework/Math/Rectangle.h>

namespace Graphics
{
    ///
    /// Camera Viewport structure
    ///
    class Viewport
    {
    public:
        ///
        /// The left viewport edge coordinate.
        ///
        int mLeft;

        ///
        /// The top viewport edge coordinate.
        ///
        int mTop;

        ///
        /// The viewport width.
        ///
        int mWidth;

        ///
        /// The viewport height.
        ///
        int mHeight;

        ///
        /// Initializes a new instance of the Viewport struct.
        ///
        Viewport();

        ///
        /// Initializes a new instance of the Viewport struct.
        ///
        Viewport(int left, int top, int width, int height);

        ///
        /// Initializes a new instance of the Viewport struct.
        ///
        Viewport(Math::RectangleI rect);

        bool operator==(const Viewport &other) const;

        bool operator!=(const Viewport &other) const;
    };
}

