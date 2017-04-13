#pragma once

#include "Functions.h"
#include "Vector.h"
#include "Vector3D.h"

namespace Math
{
    ///
    /// Four-dimensional vector
    ///
    template <typename TValue>
    class Vector<TValue, 4>
    {
    public:
        TValue x;
        TValue y;
        TValue z;
        TValue w;

        ///
        /// Initializes a new instance of the Vector4D struct.
        ///
        Vector()
            : x(), y(), z(), w()
        {
        }

        ///
        /// Initializes a new instance of the Vector2D struct.
        ///
        Vector(const Vector<TValue, 3> &base, TValue w)
            : x(base.x), y(base.y), z(base.z), w(w)
        {
        }

        ///
        /// Initializes a new instance of the Vector4D struct from Vector3D instance (w = 1.0f).
        ///
        Vector(const Vector<TValue, 3> &vector)
            : x(vector.x), y(vector.y), z(vector.z), w(1.0f)
        {
        }

        ///
        /// Initializes a new instance of the Vector4D struct.
        ///
        /// \param x The x coordinate.
        /// \param y The y coordinate.
        /// \param z The z coordinate.
        Vector(float x, float y, float z, float w)
            : x(x), y(y), z(z), w(w)
        {
        }

        ///
        /// Initializes a new instance of the Vector4D struct.
        ///
        /// \param value The x and y coordinates value.
        explicit Vector(TValue value) : x(value), y(value), z(value), w(value)
        {
        }

        ///
        /// Initializes a new instance of the Vector4D struct.
        ///
        template <typename TOtherValue>
        explicit Vector(const Vector<TOtherValue, 4>& src)
            : x((TValue)src.x), y((TValue)src.y), z((TValue)src.z), w((TValue)src.w)
        {
        }

        ///
        /// Returns the vector containing all this vector coordinates except the last one
        ///
        Vector<TValue, 3> getSubvector() const
        {
            return Vector<TValue, 3>(x, y, z);
        }

        ///
        /// Gets vector length.
        ///
        float getLength() const
        {
            return static_cast<TValue>(sqrt(x * x + y * y + z * z) / w);
        }

        ///
        /// Normalizes vector.
        ///
        /// \returns Previous vector length.
        float normalize()
        {
            auto len = getLength();

            x /= len;
            y /= len;
            z /= len;
            w = 1.0f;

            return len;
        }

        ///
        /// Gets normalized vector.
        ///
        /// \returns The normalized vector.
        Vector<TValue, 4> getNormalized() const
        {
            auto len = getLength();
            return Vector<TValue, 4>(x / len, y / len, z / len, w / len);
        }

        ///
        /// Returns dot product of this and given second vector.
        ///
        /// \returns Dot product.
        /// \param other Second vector.
        float calculateDotProduct(const Vector<TValue, 4> &other) const
        {
            return x * other.x + y * other.y + z * other.z + w * other.w;
        }

        ///
        /// Converts homogeneous coordinates to simple 3D vector.
        ///
        Vector<TValue, 3> convertToVector3D() const
        {
            return Vector<TValue, 3>(x / w, y / w, z / w);
        }

        const TValue& operator[](uint8_t index) const
        {
            if (index >= 4)
            {
                throw std::out_of_range("Vector index out of range.");
            }

            return *(&x + index);
        }

        TValue& operator[](uint8_t index)
        {
            if (index >= 4)
            {
                throw std::out_of_range("Vector index out of range.");
            }

            return *(&x + index);
        }

        Vector<TValue, 4> operator-() const
        {
            return Vector<TValue, 4>(-x, -y, -z, -w);
        }

        Vector<TValue, 4> operator+(const Vector<TValue, 4> &other) const
        {
            return Vector<TValue, 4>(x + other.x, y + other.y, z + other.z, w + other.w);
        }

        Vector<TValue, 4> operator-(const Vector<TValue, 4> &other) const
        {
            return Vector<TValue, 4>(x - other.x, y - other.y, z - other.z, w - other.w);
        }

        Vector<TValue, 4> operator*(const Vector<TValue, 4> &other) const
        {
            return Vector<TValue, 4>(x * other.x, y * other.y, z * other.z, w * other.w);
        }

        Vector<TValue, 4> operator/(const Vector<TValue, 4> &other) const
        {
            return Vector<TValue, 4>(x / other.x, y / other.y, z / other.z, w / other.w);
        }

        Vector<TValue, 4> operator*(float c) const
        {
            return Vector<TValue, 4>((TValue)(x * c), (TValue)(y * c), (TValue)(z * c), (TValue)(w * c));
        }

        Vector<TValue, 4> operator/(float c) const
        {
            return *this * (1.0f / c);
        }

        const Vector<TValue, 4>& operator+=(const Vector<TValue, 4> &other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;
            return *this;
        }

        const Vector<TValue, 4>& operator-=(const Vector<TValue, 4> &other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            w -= other.w;
            return *this;
        }

        const Vector<TValue, 4>& operator*=(const Vector<TValue, 4> &other)
        {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            w *= other.w;
            return *this;
        }

        const Vector<TValue, 4>& operator/=(const Vector<TValue, 4> &other)
        {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            w /= other.w;
            return *this;
        }

        const Vector<TValue, 4>& operator*=(float c)
        {
            x *= c;
            y *= c;
            z *= c;
            w *= c;
            return *this;
        }

        const Vector<TValue, 4>& operator/=(float c)
        {
            return *this *= 1.0f / c;
        }
    };

    typedef Vector<bool, 4> Vector4DB;
    typedef Vector<float, 4> Vector4DF;
    typedef Vector<int32_t, 4> Vector4DI;
}

