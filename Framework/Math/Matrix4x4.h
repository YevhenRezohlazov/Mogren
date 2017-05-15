#pragma once

#include "Matrix.h"
#include "Vector3D.h"
#include "Vector4D.h"

namespace Math
{
    ///
    /// 4x4 immutable matrix
    ///
    template<>
    class Matrix<4, 4>
    {
    public:
        float m00;
        float m01;
        float m02;
        float m03;

        float m10;
        float m11;
        float m12;
        float m13;

        float m20;
        float m21;
        float m22;
        float m23;

        float m30;
        float m31;
        float m32;
        float m33;

        ///
        /// The identity matrix
        ///
        static const Matrix<4, 4> Identity;

        ///
        /// Initializes a new instance of the Matrix struct with zeros.
        ///
        Matrix();

        ///
        /// Initializes a new instance of the Matrix struct with given element values.
        ///
        Matrix(
            float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33);

        ///
        /// Initializes a new instance of the Matrix struct from given elements array.
        /// \param elements The elements array pointer.
        ///
        Matrix(const float *elements);

        ///
        /// Transforms the vector by this matrix.
        /// \param vec Source vector.
        /// \returns Transformed vector.
        ///
        Vector3DF transformVector(const Vector3DF &vec) const;

        ///
        /// Rotates the vector by this matrix.
        /// \param Vector to be rotated.
        /// \returns Rotated vector.
        ///
        Vector3DF rotateVector(const Vector3DF &vec) const;

        ///
        /// Transforms the vector by this matrix.
        /// \param vec Source vector.
        /// \returns Transformed vector.
        ///
        Vector4DF transformHomogeneousVector(const Vector4DF &vec) const;

        ///
        /// Transforms the vector by this matrix.
        /// \param vec Source vector.
        /// \returns Transformed vector.
        ///
        Vector4DF rotateHomogeneousVector(const Vector4DF &vec) const;

        ///
        /// Gets the transposed matrix.
        /// \returns Transposed matrix.
        ///
        Matrix<4, 4> getTransposed() const;

        ///
        /// Gets the inverted matrix
        /// \returns Inverted matrix
        ///
        Matrix<4, 4> getInverted() const;

        ///
        /// Converts this matrix to the camera view matrix. (transposes rotation and inverts position)
        /// \returns Camera view matrix.
        ///
        Matrix<4, 4> convertToCameraViewMatrix() const;

        ///
        /// Creates new matrix filling its main diagonal with 1.0f
        ///
        static Matrix<4, 4> createIdentity()
        {
            return Identity;
        }

        const float* operator[](uint8_t rowIndex) const
        {
            switch (rowIndex)
            {
            case 0: return &m00;
            case 1: return &m10;
            case 2: return &m20;
            case 3: return &m30;
            default:
                throw std::out_of_range("Row index is out of range.");
            }
        }

        float* operator[](uint8_t rowIndex)
        {
            switch (rowIndex)
            {
            case 0: return &m00;
            case 1: return &m10;
            case 2: return &m20;
            case 3: return &m30;
            default:
                throw std::out_of_range("Row index is out of range.");
            }
        }

        Matrix<4, 4> operator-() const;
        Matrix<4, 4> operator-(const Matrix<4, 4> &other) const;
        Matrix<4, 4> operator+(const Matrix<4, 4> &other) const;
        Matrix<4, 4> operator*(float c) const;
        Matrix<4, 4> operator/(float c) const;
        Matrix<4, 4> operator*(const Matrix<4, 4> &other) const;

        const Matrix<4, 4>& operator-=(const Matrix<4, 4> &other);
        const Matrix<4, 4>& operator+=(const Matrix<4, 4> &other);
        const Matrix<4, 4>& operator*=(float c);
        const Matrix<4, 4>& operator/=(float c);
        const Matrix<4, 4>& operator*=(const Matrix<4, 4> &other);
    };

    typedef Matrix<4, 4> Matrix4x4;
}

