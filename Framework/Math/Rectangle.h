#pragma once

#include "Vector2D.h"

namespace Math
{
    ///
    /// Represents rectangle with integer coordinates and size values.
    ///
    template <typename TValue>
    class Rectangle
    {
    public:
        ///
        /// Rectangle position
        ///
        Vector<TValue, 2> position;

        ///
        /// Rectangle size
        ///
        Vector<TValue, 2> size;

        ///
        /// Initializes a new instance of the Rectangle struct.
        ///
        constexpr Rectangle() : position(), size()
        {
        }

        ///
        /// Initializes a new instance of the Rectangle struct.
        ///
        /// \param x Rectangle x coordinate.
        /// \param y Rectangle y coordinate.
        /// \param width Rectangle width.
        /// \param height Rectangle height.
        constexpr Rectangle(TValue x, TValue y, TValue width, TValue height)
            : position(x, y), size(width, height)
        {
        }

        ///
        /// Initializes a new instance of the Rectangle struct.
        ///
        /// \param position Rectangle position.
        /// \param size Rectangle size.
        constexpr Rectangle(const Vector<TValue, 2> &position, const Vector<TValue, 2> &size)
            : position(position), size(size)
        {
        }

        ///
        /// Initializes a new instance of the Rectangle struct with given size. Position is set to (0, 0).
        ///
        /// \param size Rectangle size.
        constexpr explicit Rectangle(const Vector<TValue, 2> &size)
            : position(), size(size)
        {
        }

        ///
        /// Initializes a new instance of the Rectangle struct from given size and center point
        ///
        /// \param size Rectangle size.
        /// \param center Center of the rectangle. (0, 0) by default
        constexpr static Rectangle<TValue> fromSizeCenter(
            const Vector<TValue, 2> &size,
            const Vector<TValue, 2> &center = Vector<TValue, 2>())
        {
            return Rectangle<TValue>(center - size * 0.5f, size);
        }

        ///
        /// Check if the given point is inside the rectangle.
        ///
        constexpr bool containsPoint(const Vector<TValue, 2> &point) const
        {
            return (Math::sign(point.x - position.x) != Math::sign(point.x - (position.x + size.width)))
                & (Math::sign(point.y - position.y) != Math::sign(point.y - (position.y + size.height)));
        }

        constexpr Vector<TValue, 2> getCenterPoint() const
        {
            return Vector<TValue, 2>(position.x + size.width * 0.5f, position.y + size.height * 0.5f);
        }

        constexpr Vector<TValue, 2> getPositionPlusSizeMul(const Vector<TValue, 2> &sizeMul) const
        {
            return position + size * sizeMul;
        }

        constexpr Vector<TValue, 2> getPositionPlusSize() const
        {
            return position + size;
        }

        constexpr Rectangle<TValue> convertWithMargins(
            TValue leftMargin, TValue rightMargin, TValue bottomMargin, TValue topMargin) const
        {
            return Rectangle<TValue>(
                position.x + leftMargin,
                position.y + bottomMargin,
                size.width - (leftMargin + rightMargin),
                size.height - (topMargin + bottomMargin));
        }

        constexpr Rectangle<TValue> convertWithMargins(TValue horizontalMargins, TValue verticalMargins) const
        {
            return convertWithMargins(horizontalMargins, horizontalMargins, verticalMargins, verticalMargins);
        }

        constexpr Rectangle<TValue> convertWithMargins(TValue margins) const
        {
            return convertWithMargins(margins, margins, margins, margins);
        }

        Rectangle<TValue> convertWithAspectRatio(float aspectRatio, bool stretchToFit = false) const
        {
            float currentAR = size.width / (float)size.height;
            Rectangle<TValue> res = *this;

            if ((aspectRatio > currentAR) ^ stretchToFit)
            {
                res.size.height = size.width / aspectRatio;
            }
            else
            {
                res.size.width = size.height * aspectRatio;
            }

            res.position.x += (TValue)((size.width - res.size.width) * 0.5f);
            res.position.y += (TValue)((size.height - res.size.height) * 0.5f);
            return res;
        }

        ///
        /// Transforms the given point from space of the current rectangle to the space of the other rectangle
        ///
        constexpr Vector<TValue, 2> transformPointToRect(const Vector<TValue, 2> & point, const Rectangle<TValue> & other) const
        {
            return ((point - position) / size) * other.size + other.position;
        }
    };

    typedef Rectangle<int> RectangleI;
    typedef Rectangle<float> RectangleF;
}

