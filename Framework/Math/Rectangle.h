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
        Rectangle() : position(), size()
        {
        }

        ///
        /// Initializes a new instance of the Rectangle struct.
        ///
        /// \param x Rectangle x coordinate.
        /// \param y Rectangle y coordinate.
        /// \param width Rectangle width.
        /// \param height Rectangle height.
        Rectangle(TValue x, TValue y, TValue width, TValue height)
            : position(x, y), size(width, height)
        {
        }

        ///
        /// Initializes a new instance of the Rectangle struct.
        ///
        /// \param position Rectangle position.
        /// \param size Rectangle size.
        Rectangle(const Vector<TValue, 2> &position, const Vector<TValue, 2> &size)
            : position(position), size(size)
        {
        }

        ///
        /// Initializes a new instance of the Rectangle struct.
        ///
        /// \param size Rectangle size.
        explicit Rectangle(const Vector<TValue, 2> &size)
            : position(), size(size)
        {
        }

        ///
        /// Check if the given point is inside the rectangle.
        ///
        bool containsPoint(const Vector<TValue, 2> &point) const
        {
            return (Math::sign(point.x - position.x) != Math::sign(point.x - (position.x + size.width)))
                & (Math::sign(point.y - position.y) != Math::sign(point.y - (position.y + size.height)));
        }

        Vector<TValue, 2> getCenterPoint() const
        {
            return Vector<TValue, 2>(position.x + size.width * 0.5f, position.y + size.height * 0.5f);
        }

        Vector<TValue, 2> getPositionPlusSizeMul(const Vector<TValue, 2> &sizeMul) const
        {
            return position + size * sizeMul;
        }
    };

    typedef Rectangle<int> RectangleI;
    typedef Rectangle<float> RectangleF;
}

