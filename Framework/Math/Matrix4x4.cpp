#include "Matrix4x4.h"

namespace Math
{
    const Matrix4x4 Matrix4x4::Identity = Matrix4x4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1);

    Matrix4x4 Matrix4x4::operator-() const
    {
        return Matrix4x4(
            -m00, -m01, -m02, -m03,
            -m10, -m11, -m12, -m13,
            -m20, -m21, -m22, -m23,
            -m30, -m31, -m32, -m33);
    }

    Matrix4x4 Matrix4x4::operator-(const Matrix4x4 &other) const
    {
        return Matrix4x4(
            m00 - other.m00, m01 - other.m01, m02 - other.m02, m03 - other.m03,
            m10 - other.m10, m11 - other.m11, m12 - other.m12, m13 - other.m13,
            m20 - other.m20, m21 - other.m21, m22 - other.m22, m23 - other.m23,
            m30 - other.m30, m31 - other.m31, m32 - other.m32, m33 - other.m33);
    }

    Matrix4x4 Matrix4x4::operator+(const Matrix4x4 &other) const
    {
        return Matrix4x4(
            m00 + other.m00, m01 + other.m01, m02 + other.m02, m03 + other.m03,
            m10 + other.m10, m11 + other.m11, m12 + other.m12, m13 + other.m13,
            m20 + other.m20, m21 + other.m21, m22 + other.m22, m23 + other.m23,
            m30 + other.m30, m31 + other.m31, m32 + other.m32, m33 + other.m33);
    }

    Matrix4x4 Matrix4x4::operator*(float c) const
    {
        return Matrix4x4(
            c * m00, c * m01, c * m02, c * m03,
            c * m10, c * m11, c * m12, c * m13,
            c * m20, c * m21, c * m22, c * m23,
            c * m30, c * m31, c * m32, c * m33);
    }

    Matrix4x4 Matrix4x4::operator/(float c) const
    {
        return *this * (1.0f / c);
    }

    Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &other) const
    {
        float M00 = m00 * other.m00 + m01 * other.m10 + m02 * other.m20 + m03 * other.m30;
        float M01 = m00 * other.m01 + m01 * other.m11 + m02 * other.m21 + m03 * other.m31;
        float M02 = m00 * other.m02 + m01 * other.m12 + m02 * other.m22 + m03 * other.m32;
        float M03 = m00 * other.m03 + m01 * other.m13 + m02 * other.m23 + m03 * other.m33;

        float M10 = m10 * other.m00 + m11 * other.m10 + m12 * other.m20 + m13 * other.m30;
        float M11 = m10 * other.m01 + m11 * other.m11 + m12 * other.m21 + m13 * other.m31;
        float M12 = m10 * other.m02 + m11 * other.m12 + m12 * other.m22 + m13 * other.m32;
        float M13 = m10 * other.m03 + m11 * other.m13 + m12 * other.m23 + m13 * other.m33;

        float M20 = m20 * other.m00 + m21 * other.m10 + m22 * other.m20 + m23 * other.m30;
        float M21 = m20 * other.m01 + m21 * other.m11 + m22 * other.m21 + m23 * other.m31;
        float M22 = m20 * other.m02 + m21 * other.m12 + m22 * other.m22 + m23 * other.m32;
        float M23 = m20 * other.m03 + m21 * other.m13 + m22 * other.m23 + m23 * other.m33;

        float M30 = m30 * other.m00 + m31 * other.m10 + m32 * other.m20 + m33 * other.m30;
        float M31 = m30 * other.m01 + m31 * other.m11 + m32 * other.m21 + m33 * other.m31;
        float M32 = m30 * other.m02 + m31 * other.m12 + m32 * other.m22 + m33 * other.m32;
        float M33 = m30 * other.m03 + m31 * other.m13 + m32 * other.m23 + m33 * other.m33;

        return Matrix4x4(
            M00, M01, M02, M03,
            M10, M11, M12, M13,
            M20, M21, M22, M23,
            M30, M31, M32, M33);
    }

    const Matrix4x4& Matrix4x4::operator-=(const Matrix4x4 &other)
    {
        m00 -= other.m00;
        m10 -= other.m10;
        m20 -= other.m20;
        m30 -= other.m30;

        m01 -= other.m01;
        m11 -= other.m11;
        m21 -= other.m21;
        m31 -= other.m31;

        m02 -= other.m02;
        m12 -= other.m12;
        m22 -= other.m22;
        m32 -= other.m32;

        m03 -= other.m03;
        m13 -= other.m13;
        m23 -= other.m23;
        m33 -= other.m33;

        return *this;
    }

    const Matrix4x4& Matrix4x4::operator+=(const Matrix4x4 &other)
    {
        m00 += other.m00;
        m10 += other.m10;
        m20 += other.m20;
        m30 += other.m30;

        m01 += other.m01;
        m11 += other.m11;
        m21 += other.m21;
        m31 += other.m31;

        m02 += other.m02;
        m12 += other.m12;
        m22 += other.m22;
        m32 += other.m32;

        m03 += other.m03;
        m13 += other.m13;
        m23 += other.m23;
        m33 += other.m33;

        return *this;
    }

    const Matrix4x4& Matrix4x4::operator*=(float c)
    {
        m00 *= c;
        m10 *= c;
        m20 *= c;
        m30 *= c;

        m01 *= c;
        m11 *= c;
        m21 *= c;
        m31 *= c;

        m02 *= c;
        m12 *= c;
        m22 *= c;
        m32 *= c;

        m03 *= c;
        m13 *= c;
        m23 *= c;
        m33 *= c;

        return *this;
    }

    const Matrix4x4& Matrix4x4::operator/=(float c)
    {
        return *this *= (1.0f / c);
    }

    const Matrix4x4& Matrix4x4::operator*=(const Matrix4x4 &other)
    {
        float M00 = m00 * other.m00 + m01 * other.m10 + m02 * other.m20 + m03 * other.m30;
        float M01 = m00 * other.m01 + m01 * other.m11 + m02 * other.m21 + m03 * other.m31;
        float M02 = m00 * other.m02 + m01 * other.m12 + m02 * other.m22 + m03 * other.m32;
        float M03 = m00 * other.m03 + m01 * other.m13 + m02 * other.m23 + m03 * other.m33;

        float M10 = m10 * other.m00 + m11 * other.m10 + m12 * other.m20 + m13 * other.m30;
        float M11 = m10 * other.m01 + m11 * other.m11 + m12 * other.m21 + m13 * other.m31;
        float M12 = m10 * other.m02 + m11 * other.m12 + m12 * other.m22 + m13 * other.m32;
        float M13 = m10 * other.m03 + m11 * other.m13 + m12 * other.m23 + m13 * other.m33;

        float M20 = m20 * other.m00 + m21 * other.m10 + m22 * other.m20 + m23 * other.m30;
        float M21 = m20 * other.m01 + m21 * other.m11 + m22 * other.m21 + m23 * other.m31;
        float M22 = m20 * other.m02 + m21 * other.m12 + m22 * other.m22 + m23 * other.m32;
        float M23 = m20 * other.m03 + m21 * other.m13 + m22 * other.m23 + m23 * other.m33;

        float M30 = m30 * other.m00 + m31 * other.m10 + m32 * other.m20 + m33 * other.m30;
        float M31 = m30 * other.m01 + m31 * other.m11 + m32 * other.m21 + m33 * other.m31;
        float M32 = m30 * other.m02 + m31 * other.m12 + m32 * other.m22 + m33 * other.m32;
        float M33 = m30 * other.m03 + m31 * other.m13 + m32 * other.m23 + m33 * other.m33;

        return *this = Matrix4x4(
            M00, M01, M02, M03,
            M10, M11, M12, M13,
            M20, M21, M22, M23,
            M30, M31, M32, M33);
    }

    Matrix4x4 Matrix4x4::convertToCameraViewMatrix() const
    {
        Matrix4x4 result(
            m00, m10, m20, 0.0f,
            m01, m11, m21, 0.0f,
            m02, m12, m22, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);

        auto position = result.rotateVector(-Math::Vector3DF(m30, m31, m32));
        result.m30 = position.x;
        result.m31 = position.y;
        result.m32 = position.z;

        return result;
    }

    Matrix4x4 Matrix4x4::getTransposed() const
    {
        return Matrix4x4(
            m00, m10, m20, m30,
            m01, m11, m21, m31,
            m02, m12, m22, m32,
            m03, m13, m23, m33);
    }

    // from http://stackoverflow.com/questions/2624422/efficient-4x4-matrix-inverse-affine-transform
    Matrix4x4 Matrix4x4::getInverted() const
    {
        Matrix4x4 m;

        auto s0 = m00 * m11 - m10 * m01;
        auto s1 = m00 * m12 - m10 * m02;
        auto s2 = m00 * m13 - m10 * m03;
        auto s3 = m01 * m12 - m11 * m02;
        auto s4 = m01 * m13 - m11 * m03;
        auto s5 = m02 * m13 - m12 * m03;
        auto c5 = m22 * m33 - m32 * m23;
        auto c4 = m21 * m33 - m31 * m23;
        auto c3 = m21 * m32 - m31 * m22;
        auto c2 = m20 * m33 - m30 * m23;
        auto c1 = m20 * m32 - m30 * m22;
        auto c0 = m20 * m31 - m30 * m21;

        // Should check for 0 determinant
        auto invdet = 1.0f / (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);

        m.m00 = (m11 * c5 - m12 * c4 + m13 * c3) * invdet;
        m.m01 = (-m01 * c5 + m02 * c4 - m03 * c3) * invdet;
        m.m02 = (m31 * s5 - m32 * s4 + m33 * s3) * invdet;
        m.m03 = (-m21 * s5 + m22 * s4 - m23 * s3) * invdet;

        m.m10 = (-m10 * c5 + m12 * c2 - m13 * c1) * invdet;
        m.m11 = (m00 * c5 - m02 * c2 + m03 * c1) * invdet;
        m.m12 = (-m30 * s5 + m32 * s2 - m33 * s1) * invdet;
        m.m13 = (m20 * s5 - m22 * s2 + m23 * s1) * invdet;

        m.m20 = (m10 * c4 - m11 * c2 + m13 * c0) * invdet;
        m.m21 = (-m00 * c4 + m01 * c2 - m03 * c0) * invdet;
        m.m22 = (m30 * s4 - m31 * s2 + m33 * s0) * invdet;
        m.m23 = (-m20 * s4 + m21 * s2 - m23 * s0) * invdet;

        m.m30 = (-m10 * c3 + m11 * c1 - m12 * c0) * invdet;
        m.m31 = (m00 * c3 - m01 * c1 + m02 * c0) * invdet;
        m.m32 = (-m30 * s3 + m31 * s1 - m32 * s0) * invdet;
        m.m33 = (m20 * s3 - m21 * s1 + m22 * s0) * invdet;

        return m;
    }

    Matrix4x4::Matrix()
        : m00(0.0f), m01(0.0f), m02(0.0f), m03(0.0f),
        m10(0.0f), m11(0.0f), m12(0.0f), m13(0.0f),
        m20(0.0f), m21(0.0f), m22(0.0f), m23(0.0f),
        m30(0.0f), m31(0.0f), m32(0.0f), m33(0.0f)
    {
    }

    Matrix4x4::Matrix(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33)
        : m00(m00), m01(m01), m02(m02), m03(m03),
        m10(m10), m11(m11), m12(m12), m13(m13),
        m20(m20), m21(m21), m22(m22), m23(m23),
        m30(m30), m31(m31), m32(m32), m33(m33)
    {
    }

    Matrix4x4::Matrix(const float *elements)
    {
        m00 = elements[0]; m01 = elements[1]; m02 = elements[2]; m03 = elements[3];
        m10 = elements[4]; m11 = elements[5]; m12 = elements[6]; m13 = elements[7];
        m20 = elements[8]; m21 = elements[9]; m22 = elements[10]; m23 = elements[11];
        m30 = elements[12]; m31 = elements[13]; m32 = elements[14]; m33 = elements[15];
    }

    Vector3DF Matrix4x4::transformVector(const Vector3DF &vec) const
    {
        return Vector3DF(
            vec.x * m00 + vec.y * m10 + vec.z * m20 + m30,
            vec.x * m01 + vec.y * m11 + vec.z * m21 + m31,
            vec.x * m02 + vec.y * m12 + vec.z * m22 + m32);
    }

    Vector4DF Matrix4x4::transformHomogeneousVector(const Vector4DF &vec) const
    {
        return Vector4DF(
            vec.x * m00 + vec.y * m10 + vec.z * m20 + m30,
            vec.x * m01 + vec.y * m11 + vec.z * m21 + m31,
            vec.x * m02 + vec.y * m12 + vec.z * m22 + m32,
            vec.x * m03 + vec.y * m13 + vec.z * m23 + m33);
    }

    Vector4DF Matrix4x4::rotateHomogeneousVector(const Vector4DF &vec) const
    {
        return Vector4DF(
            vec.x * m00 + vec.y * m10 + vec.z * m20,
            vec.x * m01 + vec.y * m11 + vec.z * m21,
            vec.x * m02 + vec.y * m12 + vec.z * m22,
            vec.x * m03 + vec.y * m13 + vec.z * m23);
    }

    Vector3DF Matrix4x4::rotateVector(const Vector3DF &vec) const
    {
        return Vector3DF(
            vec.x * m00 + vec.y * m10 + vec.z * m20,
            vec.x * m01 + vec.y * m11 + vec.z * m21,
            vec.x * m02 + vec.y * m12 + vec.z * m22);
    }
} // Math