#pragma once

#include <cmath>
#include <cstdlib>

namespace Math
{
    const float PI = 3.14159265359f;
    const float Half_PI = PI * 0.5f;
    const float Two_PI = PI * 2.0f;

    const float E = 2.71828182846f;

    ///
    /// Calculates absolute value
    /// \param value The input value.
    ///
    static inline int abs(int value)
    {
        return std::abs(value);
    }

    ///
    /// Calculates absolute value
    /// \param value The input value.
    ///
    static inline float abs(float value)
    {
        return std::abs(value);
    }

    ///
    /// Sine function
    /// \param angle Angle in radians
    ///
    static inline float sin(float angle)
    {
        return ::sin(angle);
    }

    ///
    /// Cosine function
    /// \param angle Angle in radians
    ///
    static inline float cos(float angle)
    {
        return std::cos(angle);
    }

    ///
    /// Tangent function
    /// \param angle Angle in radians
    ///
    static inline float tan(float angle)
    {
        return std::tan(angle);
    }

    ///
    /// Arcsine function
    /// \param value Sine value.
    ///
    static inline float asin(float value)
    {
        return std::asin(value);
    }

    ///
    /// Arccosine function
    /// \param value Cosine value.
    ///
    static inline float acos(float value)
    {
        return std::acos(value);
    }

    ///
    /// Arctangent function
    /// \param value Tangent value.
    ///
    static inline float atan(float value)
    {
        return std::atan(value);
    }

    ///
    /// For any real number (e.g., floating point) arguments x and y not both equal to zero,
    /// atan2(y, x) is the angle in radians between the positive x-axis of a plane and
    /// the point given by the coordinates (x, y) on it. The angle is positive for
    /// counter-clockwise angles (upper half-plane, y > 0), and negative for clockwise angles
    /// (lower half-plane, y < 0).
    /// \param value Tangent value.
    ///
    static inline float atan2(float y, float x)
    {
        return std::atan2(y, x);
    }

    ///
    /// Exponent function
    /// \param power Power of exponent
    ///
    static inline float exp(float power)
    {
        return std::exp(power);
    }

    ///
    /// Calculates x in power of y
    /// \param x Parameter.
    /// \param y Power.
    ///
    static inline float pow(float x, float y)
    {
        return std::pow(x, y);
    }

    ///
    /// Calculates square root
    /// \param value The input value.
    ///
    static inline float sqrt(float value)
    {
        return std::sqrt(value);
    }

    ///
    /// Calculates square
    /// \param value The input value.
    ///
    static inline float sqr(float value)
    {
        return value * value;
    }

    ///
    /// Rounds x upward, returning the smallest integral value that is not less than x.
    /// \param value The input value.
    ///
    static inline int ceil(float value)
    {
        return static_cast<int>(std::ceil(value));
    }

    ///
    /// Rounds x downward, returning the largest integral value that is not greater than x.
    /// \param value The input value.
    ///
    static inline int floor(float value)
    {
        return static_cast<int>(std::floor(value));
    }

    ///
    /// Returns the integral value that is nearest to x, with halfway cases rounded away from zero.
    /// \param value The input value.
    ///
    static inline int round(float value)
    {
        return value < 0.0f ? ceil(value - 0.5f) : floor(value + 0.5f);
    }

    ///
    /// Returns the floating-point remainder of numerator/denominator (rounded towards zero).
    /// \param numerator The numerator.
    /// \param denominator The denominator.
    static inline float fmod(float numerator, float denominator)
    {
        return std::fmod(numerator, denominator);
    }

    ///
    /// Gets the minimal of two elements
    /// \param a The first element.
    /// \param b The second element.
    ///
    template<typename T>
    T minimum(T a, T b)
    {
        return a > b ? b : a;
    }

    ///
    /// Gets the maximal of two elements
    /// \param a The first element.
    /// \param b The second element.
    ///
    template<typename T>
    T maximum(T a, T b)
    {
        return a > b ? a : b;
    }

    ///
    /// Gets the sign of the given value (-1 if value < 0, 1 if value > 0 and 0 if value == 0)
    /// \param value The value.
    ///
    template<typename T>
    int sign(T value)
    {
        if (value < 0)
        {
            return -1;
        }

        if (value > 0)
        {
            return 1;
        }

        return 0;
    }

    ///
    /// Returns random value in range from minValue to maxValue
    ///
    template<typename T>
    T random(const T& minValue, const T& maxValue)
    {
        auto coef = rand() / double(RAND_MAX);
        return minValue + (T)(coef * (maxValue - minValue));
    }

    ///
    /// Returns random value in range from zero (T()) to maxValue
    ///
    template<typename T>
    T random(const T& maxValue)
    {
        return random(T(), maxValue);
    }
}

