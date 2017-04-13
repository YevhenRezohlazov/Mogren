#pragma once

#include <cstdint>
#include <cmath>
#include <stdexcept>
#include <stdarg.h>
#include <memory.h>

#include "Functions.h"

namespace Math
{
    ///
    /// Base vector
    ///
    template <typename TValue, uint8_t Dimension>
    class Vector
    {
    public:
        TValue mComponents[Dimension];

        ///
        /// Initializes a new instance of the Vector struct.
        ///
        Vector();

        ///
        /// Initializes a new instance of the Vector struct.
        ///
        Vector(const Vector<TValue, Dimension - 1> &base, TValue last);

        ///
        /// Initializes a new instance of the Vector struct.
        ///
        explicit Vector(TValue x);

        ///
        /// Initializes a new instance of the Vector struct.
        ///
        template <typename TOtherValue>
        explicit Vector(const Vector<TOtherValue, Dimension>& src);

        ///
        /// Returns the vector containing all this vector coordinates except the last one
        ///
        Vector<TValue, Dimension - 1> getSubvector() const;

        ///
        /// Gets vector length.
        ///
        TValue getLength() const;

        ///
        /// Normalizes vector.
        ///
        /// \returns Previous vector length.
        TValue normalize();

        ///
        /// Gets normalized vector.
        ///
        /// \returns The normalized vector.
        Vector<TValue, Dimension> getNormalized() const;

        ///
        /// Returns dot product of this and given second vector.
        ///
        /// \returns Dot product.
        /// \param other Second vector.
        TValue calculateDotProduct(Vector<TValue, Dimension> other) const;

        const TValue& operator[](uint8_t index) const
        {
            if (index >= Dimension)
            {
                throw std::out_of_range("Vector index out of range.");
            }

            return mComponents[index];
        }

        TValue& operator[](uint8_t index)
        {
            if (index >= Dimension)
            {
                throw std::out_of_range("Vector index out of range.");
            }

            return mComponents[index];
        }

        Vector<TValue, Dimension> operator-() const
        {
            Vector<TValue, Dimension> res;

            for (uint8_t i = 0; i < Dimension; ++i)
            {
                res.mComponents[i] = -mComponents[i];
            }

            return res;
        }

        Vector<TValue, Dimension> operator+(const Vector<TValue, Dimension> &other) const
        {
            Vector<TValue, Dimension> res;

            for (uint8_t i = 0; i < Dimension; ++i)
            {
                res.mComponents[i] = mComponents[i] + other.mComponents[i];
            }

            return res;
        }

        Vector<TValue, Dimension> operator-(const Vector<TValue, Dimension> &other) const
        {
            Vector<TValue, Dimension> res;

            for (uint8_t i = 0; i < Dimension; ++i)
            {
                res.mComponents[i] = mComponents[i] - other.mComponents[i];
            }

            return res;
        }

        Vector<TValue, Dimension> operator*(const Vector<TValue, Dimension> &other) const
        {
            Vector<TValue, Dimension> res;

            for (uint8_t i = 0; i < Dimension; ++i)
            {
                res.mComponents[i] = static_cast<TValue>(mComponents[i] * other[i]);
            }

            return res;
        }

        Vector<TValue, Dimension> operator/(const Vector<TValue, Dimension> &other) const
        {
            Vector<TValue, Dimension> res;

            for (uint8_t i = 0; i < Dimension; ++i)
            {
                res.mComponents[i] = static_cast<TValue>(mComponents[i] / other[i]);
            }

            return res;
        }

        Vector<TValue, Dimension> operator*(float c) const
        {
            Vector<TValue, Dimension> res;

            for (uint8_t i = 0; i < Dimension; ++i)
            {
                res.mComponents[i] = static_cast<TValue>(mComponents[i] / c);
            }

            return res;
        }

        Vector<TValue, Dimension> operator/(float c) const
        {
            Vector<TValue, Dimension> res;

            for (uint8_t i = 0; i < Dimension; ++i)
            {
                res.mComponents[i] = static_cast<TValue>(mComponents[i] / c);
            }

            return res;
        }

        const Vector<TValue, Dimension>& operator+=(const Vector<TValue, Dimension> &other)
        {
            for (uint8_t i = 0; i < Dimension; ++i)
            {
                mComponents[i] += other.mComponents[i];
            }

            return *this;
        }

        const Vector<TValue, Dimension>& operator-=(const Vector<TValue, Dimension> &other)
        {
            for (uint8_t i = 0; i < Dimension; ++i)
            {
                mComponents[i] -= other.mComponents[i];
            }

            return *this;
        }

        const Vector<TValue, Dimension>& operator*=(const Vector<TValue, Dimension> &other)
        {
            for (uint8_t i = 0; i < Dimension; ++i)
            {
                mComponents[i] *= other[i];
            }

            return *this;
        }

        const Vector<TValue, Dimension>& operator/=(const Vector<TValue, Dimension> &other)
        {
            for (uint8_t i = 0; i < Dimension; ++i)
            {
                mComponents[i] /= other[i];
            }

            return *this;
        }

        const Vector<TValue, Dimension>& operator*=(float c)
        {
            for (uint8_t i = 0; i < Dimension; ++i)
            {
                mComponents[i] *= c;
            }

            return *this;
        }

        const Vector<TValue, Dimension>& operator/=(float c)
        {
            for (uint8_t i = 0; i < Dimension; ++i)
            {
                mComponents[i] /= c;
            }

            return *this;
        }
    };

    template <typename TValue, uint8_t Dimension>
    Vector<TValue, Dimension> operator*(float c, const Vector<TValue, Dimension>& vec)
    {
        return vec * c;
    }

    ///
    /// Initializes a new instance of the Vector struct.
    ///
    template<typename TValue, uint8_t Dimension>
    inline Vector<TValue, Dimension>::Vector()
    {
        memset(mComponents, 0, sizeof(mComponents));
    }

    ///
    /// Initializes a new instance of the Vector struct.
    ///
    template<typename TValue, uint8_t Dimension>
    inline Vector<TValue, Dimension>::Vector(const Vector<TValue, Dimension - 1>& base, TValue last)
    {
        memcpy(mComponents, base.mComponents, sizeof(base.mComponents));
        mComponents[Dimension - 1] = last;
    }

    ///
    /// Initializes a new instance of the Vector struct.
    ///
    template<typename TValue, uint8_t Dimension>
    inline Vector<TValue, Dimension>::Vector(TValue x)
    {
        for (uint8_t i = 0; i < Dimension; ++i)
        {
            (*this)[i] = x;
        }
    }

    ///
    /// Initializes a new instance of the Vector struct.
    ///
    template<typename TValue, uint8_t Dimension>
    template<typename TOtherValue>
    inline Vector<TValue, Dimension>::Vector(const Vector<TOtherValue, Dimension>& src)
    {
        for (uint8_t i = 0; i < Dimension; ++i)
        {
            (*this)[i] = (TValue)src[i];
        }
    }

    ///
    /// Returns the vector containing all this vector coordinates except the last one
    ///
    template<typename TValue, uint8_t Dimension>
    inline Vector<TValue, Dimension - 1> Vector<TValue, Dimension>::getSubvector() const
    {
        Vector<TValue, Dimension - 1> res;
        memcpy(res.mComponents, mComponents, sizeof(res.mComponents));
        return res;
    }

    ///
    /// Gets vector length.
    ///
    template<typename TValue, uint8_t Dimension>
    inline TValue Vector<TValue, Dimension>::getLength() const
    {
        TValue sum = 0;

        for (uint8_t i = 0; i < Dimension; ++i)
        {
            sum += mComponents[i] * mComponents[i];
        }

        return static_cast<TValue>(sqrt(sum));
    }

    ///
    /// Normalizes vector.
    ///
    /// \returns Previous vector length.
    template<typename TValue, uint8_t Dimension>
    inline TValue Vector<TValue, Dimension>::normalize()
    {
        TValue len = getLength();

        for (uint8_t i = 0; i < Dimension; ++i)
        {
            mComponents[i] /= len;
        }

        return len;
    }

    ///
    /// Gets normalized vector.
    ///
    /// \returns The normalized vector.
    template<typename TValue, uint8_t Dimension>
    inline Vector<TValue, Dimension> Vector<TValue, Dimension>::getNormalized() const
    {
        Vector<TValue, Dimension> res;

        TValue len = getLength();

        for (uint8_t i = 0; i < Dimension; ++i)
        {
            res.mComponents[i] = mComponents[i] / len;
        }

        return res;
    }

    ///
    /// Returns dot product of this and given second vector.
    ///
    /// \returns Dot product.
    /// \param other Second vector.
    template<typename TValue, uint8_t Dimension>
    inline TValue Vector<TValue, Dimension>::calculateDotProduct(Vector<TValue, Dimension> other) const
    {
        TValue res = 0;

        for (uint8_t i = 0; i < Dimension; ++i)
        {
            res += mComponents[i] * other.mComponents[i];
        }
    }
}

