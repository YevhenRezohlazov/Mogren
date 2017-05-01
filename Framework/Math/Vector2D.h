#pragma once

#include "Functions.h"
#include "Vector.h"

namespace Math
{
    ///
    /// Two-dimensional vector
    ///
    template <typename TValue>
    class Vector<TValue, 2>
    {
    public:
        union
        {
            ///
            /// X vector coordinate (width)
            ///
            TValue x;

            ///
            /// X vector coordinate (width)
            ///
            TValue width;
        };

        union
        {
            ///
            /// Y vector coordinate (height)
            ///
            TValue y;

            ///
            /// Y vector coordinate (height)
            ///
            TValue height;
        };

        ///
        /// Initializes a new instance of the Vector2D struct.
        ///
        constexpr Vector() : x(), y()
        {
        }

        ///
        /// Initializes a new instance of the Vector2D struct.
        ///
        constexpr Vector(const Vector<TValue, 1> &base, TValue y)
            : x(base[0]), y(y)
        {
        }

        ///
        /// Initializes a new instance of the Vector2D struct.
        ///
        /// \param x The x coordinate (width).
        /// \param y The y coordinate (height).
        constexpr Vector(TValue x, TValue y) : x(x), y(y)
        {
        }

        ///
        /// Initializes a new instance of the Vector2D struct.
        ///
        /// \param value The x and y coordinates value.
        constexpr explicit Vector(TValue value) : x(value), y(value)
        {
        }

        ///
        /// Initializes a new instance of the Vector2D struct.
        ///
        template <typename TOtherValue>
        constexpr explicit Vector(const Vector<TOtherValue, 2>& src)
            : x((TValue)src.x), y((TValue)src.y)
        {
        }

        ///
        /// Creates vector that makes given angle with X axis and has length 1.0.
        /// @param angle The angle in radians.
        ///
        constexpr static Vector<TValue, 2> fromAngle(float angle)
        {
            return Vector<TValue, 2>((TValue)cos(angle), (TValue)sin(angle));
        }

        ///
        /// Creates vector that makes given angle with X axis and has given length.
        /// @param angle The angle in radians.
        /// @param length The vector length.
        ///
        constexpr static Vector<TValue, 2> fromAngleAndLength(float angle, TValue length)
        {
            return Vector<TValue, 2>((TValue)(cos(angle) * length), (TValue)(sin(angle) * length));
        }

        ///
        /// Returns the vector containing all this vector coordinates except the last one
        ///
        constexpr Vector<TValue, 1> getSubvector() const
        {
            return Vector<TValue, 1>(x);
        }

        ///
        /// Gets vector length.
        ///
        constexpr TValue getLength() const
        {
            return static_cast<TValue>(sqrt(x * x + y * y));
        }

        ///
        /// Normalizes vector.
        ///
        /// \returns Previous vector length.
        TValue normalize()
        {
            TValue len = getLength();

            x /= len;
            y /= len;

            return len;
        }

        ///
        /// Gets normalized vector.
        ///
        /// \returns The normalized vector.
        constexpr Vector<TValue, 2> getNormalized() const
        {
            Vector<TValue, 2> res;
            TValue len = getLength();

            res.x = x / len;
            res.y = y / len;

            return res;
        }

        ///
        /// Returns dot product of this and given second vector.
        ///
        /// \returns Dot product.
        /// \param other Second vector.
        constexpr float calculateDotProduct(Vector<TValue, 2> other) const
        {
            return x * other.x + y * other.y;
        }

        ///
        /// Returns the angle between this vector and X axis.
        ///
        constexpr float getAngle() const
        {
            return Math::atan2(y, x);
        }

        constexpr const TValue& operator[](uint8_t index) const
        {
            if (index >= 2)
            {
                throw std::out_of_range("Vector index out of range.");
            }

            return index == 0 ? x : y;
        }

        TValue& operator[](uint8_t index)
        {
            if (index >= 2)
            {
                throw std::out_of_range("Vector index out of range.");
            }

            return index == 0 ? x : y;
        }

        constexpr Vector<TValue, 2> operator-() const
        {
            return Vector<TValue, 2>(-x, -y);
        }

        constexpr Vector<TValue, 2> operator+(const Vector<TValue, 2> &other) const
        {
            return Vector<TValue, 2>(x + other.x, y + other.y);
        }

        constexpr Vector<TValue, 2> operator-(const Vector<TValue, 2> &other) const
        {
            return Vector<TValue, 2>(x - other.x, y - other.y);
        }

        constexpr Vector<TValue, 2> operator*(const Vector<TValue, 2> &other) const
        {
            return Vector<TValue, 2>(x * other.x, y * other.y);
        }

        constexpr Vector<TValue, 2> operator/(const Vector<TValue, 2> &other) const
        {
            return Vector<TValue, 2>(x / other.x, y / other.y);
        }

        constexpr Vector<TValue, 2> operator*(float c) const
        {
            return Vector<TValue, 2>((TValue)(x * c), (TValue)(y * c));
        }

        constexpr Vector<TValue, 2> operator/(float c) const
        {
            return Vector<TValue, 2>((TValue)(x / c), (TValue)(y / c));
        }

        const Vector<TValue, 2>& operator+=(const Vector<TValue, 2> &other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }

        const Vector<TValue, 2>& operator-=(const Vector<TValue, 2> &other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        const Vector<TValue, 2>& operator*=(const Vector<TValue, 2> &other)
        {
            x *= other.x;
            y *= other.y;
            return *this;
        }

        const Vector<TValue, 2>& operator/=(const Vector<TValue, 2> &other)
        {
            x /= other.x;
            y /= other.y;
            return *this;
        }

        const Vector<TValue, 2>& operator*=(float c)
        {
            x *= c;
            y *= c;
            return *this;
        }

        const Vector<TValue, 2>& operator/=(float c)
        {
            x /= c;
            y /= c;
            return *this;
        }

        inline bool operator==(const Vector<TValue, 2>& other) const
        {
            return x == other.x && y == other.y;
        }

        inline bool operator!=(const Vector<TValue, 2>& other) const
        {
            return x != other.x || y != other.y;
        }
    };

    typedef Vector<bool, 2> Vector2DB;
    typedef Vector<float, 2> Vector2DF;
    typedef Vector<int32_t, 2> Vector2DI;

    typedef Vector<float, 2> Point2DF;
    typedef Vector<int32_t, 2> Point2DI;

    typedef Vector<float, 2> Size2DF;
    typedef Vector<int32_t, 2> Size2DI;
}

