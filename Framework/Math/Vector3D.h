#pragma once

#include "Functions.h"
#include "Vector.h"
#include "Vector2D.h"

namespace Math
{
    ///
    /// Three-dimensional vector
    ///
    template <typename TValue>
    class Vector<TValue, 3>
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

        union
        {
            ///
            /// Z vector coordinate (depth)
            ///
            TValue z;

            ///
            /// Z vector coordinate (depth)
            ///
            TValue depth;
        };

        ///
        /// Initializes a new instance of the Vector struct.
        ///
        constexpr Vector() : x(), y(), z()
        {
        }

        ///
        /// Initializes a new instance of the Vector2D struct.
        ///
        constexpr Vector(const Vector<TValue, 2> &base, TValue z)
            : x(base.x), y(base.y), z(z)
        {
        }

        ///
        /// Initializes a new instance of the Vector struct.
        ///
        /// \param x The x coordinate (width).
        /// \param y The y coordinate (height).
        /// \param z The z coordinate (depth).
        constexpr Vector(TValue x, TValue y, TValue z)
            : x(x), y(y), z(z)
        {
        }

        ///
        /// Initializes a new instance of the Vector3D struct.
        ///
        /// \param value The x and y coordinates value.
        constexpr explicit Vector(TValue value) : x(value), y(value), z(value)
        {
        }

        ///
        /// Initializes a new instance of the Vector3D struct.
        ///
        template <typename TOtherValue>
        constexpr explicit Vector(const Vector<TOtherValue, 3>& src)
            : x((TValue)src.x), y((TValue)src.y), z((TValue)src.z)
        {
        }

        ///
        /// Returns the vector containing all this vector coordinates except the last one
        ///
        constexpr Vector<TValue, 2> getSubvector() const
        {
            return Vector<TValue, 2>(x, y);
        }

        ///
        /// Gets vector length.
        ///
        constexpr TValue getLength() const
        {
            return static_cast<TValue>(sqrt(x * x + y * y + z * z));
        }

        ///
        /// Normalizes vector.
        ///
        /// \returns Previous vector length.
        float normalize()
        {
            TValue len = getLength();
            x /= len;
            y /= len;
            z /= len;

            return len;
        }

        ///
        /// Gets normalized vector.
        ///
        /// \returns The normalized vector.
        constexpr Vector<TValue, 3> getNormalized() const
        {
            Vector<TValue, 3> res;

            TValue len = getLength();
            res.x = x / len;
            res.x = y / len;
            res.x = z / len;

            return res;
        }

        ///
        /// Returns dot product of this and given second vector.
        ///
        /// \returns Dot product.
        /// \param other Second vector.
        constexpr TValue calculateDotProduct(const Vector<TValue, 3> &other) const
        {
            return x * other.x + y * other.y + z * other.z;
        }

        ///
        /// Returns the cross product of this and given second vector.
        ///
        /// \param other The second vector.
        ///
        constexpr Vector<TValue, 3> calculateCrossProduct(const Vector<TValue, 3> &other) const
        {
            return Vector<TValue, 3>(y * other.z - other.y * z, other.x * z - x * other.z, x * other.y - other.x * y);
        }

        constexpr const TValue& operator[](uint8_t index) const
        {
            if (index >= 3)
            {
                throw std::out_of_range("Vector index out of range.");
            }

            return *(&x + index);
        }

        TValue& operator[](uint8_t index)
        {
            if (index >= 3)
            {
                throw std::out_of_range("Vector index out of range.");
            }

            return *(&x + index);
        }

        constexpr Vector operator-() const
        {
            return Vector<TValue, 3>(-x, -y, -z);
        }

        constexpr Vector operator+(const Vector &other) const
        {
            return Vector<TValue, 3>(x + other.x, y + other.y, z + other.z);
        }

        constexpr Vector operator-(const Vector &other) const
        {
            return Vector<TValue, 3>(x - other.x, y - other.y, z - other.z);
        }

        constexpr Vector operator*(const Vector &other) const
        {
            return Vector<TValue, 3>(x * other.x, y * other.y, z * other.z);
        }

        constexpr Vector operator/(const Vector &other) const
        {
            return Vector<TValue, 3>(x / other.x, y / other.y, z / other.z);
        }

        constexpr Vector operator*(float c) const
        {
            return Vector<TValue, 3>((TValue)(x * c), (TValue)(y * c), (TValue)(z * c));
        }

        constexpr Vector operator/(float c) const
        {
            return Vector<TValue, 3>((TValue)(x / c), (TValue)(y / c), (TValue)(z / c));
        }

        const Vector& operator+=(const Vector &other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        const Vector& operator-=(const Vector &other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        const Vector& operator*=(const Vector &other)
        {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            return *this;
        }

        const Vector& operator/=(const Vector &other)
        {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            return *this;
        }

        const Vector& operator*=(float c)
        {
            x *= c;
            y *= c;
            z *= c;
            return *this;
        }

        const Vector& operator/=(float c)
        {
            x /= c;
            y /= c;
            z /= c;
            return *this;
        }
    };

    typedef Vector<bool, 3> Vector3DB;
    typedef Vector<float, 3> Vector3DF;
    typedef Vector<int32_t, 3> Vector3DI;

    typedef Vector<float, 3> Point3DF;
    typedef Vector<int32_t, 3> Point3DI;

    typedef Vector<float, 3> Size3DF;
    typedef Vector<int32_t, 3> Size3DI;
}

