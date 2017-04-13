#pragma once

#include "Vector.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"

namespace Math
{
    ///
    /// 4x4 immutable matrix
    ///
    template<uint8_t NDimension, uint8_t MDimension>
    class Matrix
    {
    private:
        float mElements[NDimension * MDimension];
    public:
        ///
        /// Initializes a new instance of the Matrix struct with zeros.
        ///
        Matrix()
        {
            memset(mElements, 0, sizeof(mElements));
        }

        ///
        /// Initializes a new instance of the Matrix struct from given elements array.
        /// \param elements The elements array pointer.
        ///
        Matrix(const float *elements)
        {
            memcpy(mElements, elements, sizeof(mElements));
        }

        ///
        /// Transforms the vector by this matrix.
        /// \param vec Source vector.
        /// \returns Transformed vector.
        ///
        Vector<float, MDimension> transformHomogeneousVector(const Vector<float, NDimension> &vec) const
        {
            Vector<float, MDimension> res;

            for (uint8_t j = 0; j < MDimension; ++j)
            {
                float sum = 0.0f;

                for (uint8_t i = 0; i < NDimension; ++i)
                {
                    sum += vec[i] * (*this)[i][j];
                }

                res[j] = sum;
            }

            return res;
        }

        ///
        /// Transforms the vector by this matrix.
        /// \param vec Source vector.
        /// \returns Transformed vector.
        ///
        Vector<float, MDimension - 1> transformVector(const Vector<float, NDimension - 1> &vec) const
        {
            Vector<float, NDimension> homVec(vec, 1.0f);
            return transformHomogeneousVector(homVec).getSubvector();
        }

        ///
        /// Transforms the vector by this matrix.
        /// \param vec Source vector.
        /// \returns Transformed vector.
        ///
        Vector<float, MDimension> rotateHomogeneousVector(const Vector<float, NDimension> &vec) const
        {
            Vector<float, MDimension> res;
            Vector<float, NDimension> vecCpy = vec;
            vecCpy[NDimension - 1] = 0.0f; // w = 0 to skip positioning

            for (uint8_t j = 0; j < MDimension; ++j)
            {
                float sum = 0.0f;

                for (uint8_t i = 0; i < NDimension; ++i)
                {
                    sum += vecCpy[i] * (*this)[i][j];
                }

                res[j] = sum;
            }

            res[MDimension - 1] = vec[NDimension - 1]; // restore w
            return res;
        }

        ///
        /// Transforms the vector by this matrix.
        /// \param vec Source vector.
        /// \returns Transformed vector.
        ///
        Vector<float, MDimension - 1> rotateVector(const Vector<float, NDimension - 1> &vec) const
        {
            Vector<float, NDimension> homVec(vec, 0.0f);
            return transformHomogeneousVector(homVec).getSubvector();
        }

        ///
        /// Gets the transposed matrix.
        /// \returns Transposed matrix.
        ///
        Matrix<MDimension, NDimension> getTransposed() const
        {
            Matrix<MDimension, NDimension> res;

            for (uint8_t i = 0; i < NDimension; ++i)
            {
                for (uint8_t j = 0; j < MDimension; ++j)
                {
                    res[i][j] = (*this)[j][i];
                }
            }

            return res;
        }

        ///
        /// Creates new matrix filling its main diagonal with 1.0f
        ///
        static Matrix<NDimension, MDimension> createIdentity()
        {
            Matrix<NDimension, MDimension> res;

            uint8_t minSize = minimum(NDimension, MDimension);

            for (uint8_t i = 0; i < minSize; ++i)
            {
                res[i][i] = 1.0f;
            }

            return res;
        }

        const float* operator[](uint8_t rowIndex) const
        {
            if (rowIndex >= NDimension)
            {
                throw std::out_of_range("Row index is out of range.");
            }

            return &mElements[rowIndex * MDimension];
        }

        float* operator[](uint8_t rowIndex)
        {
            if (rowIndex >= NDimension)
            {
                throw std::out_of_range("Row index is out of range.");
            }

            return &mElements[rowIndex * MDimension];
        }

        Matrix<NDimension, MDimension> operator-() const
        {
            Matrix<MDimension, NDimension> res;

            for (uint16_t i = 0; i < NDimension * MDimension; ++i)
            {
                res.mElements[i] = -this->mElements[i];
            }

            return res;
        }

        Matrix<NDimension, MDimension> operator-(const Matrix<NDimension, MDimension> &other) const
        {
            Matrix<MDimension, NDimension> res;

            for (uint16_t i = 0; i < NDimension * MDimension; ++i)
            {
                res.mElements[i] = this->mElements[i] - other.mElements[i];
            }

            return res;
        }

        Matrix<NDimension, MDimension> operator+(const Matrix<NDimension, MDimension> &other) const
        {
            Matrix<MDimension, NDimension> res;

            for (uint16_t i = 0; i < NDimension * MDimension; ++i)
            {
                res.mElements[i] = this->mElements[i] + other.mElements[i];
            }

            return res;
        }

        Matrix<NDimension, MDimension> operator*(float c) const
        {
            Matrix<MDimension, NDimension> res;

            for (uint16_t i = 0; i < NDimension * MDimension; ++i)
            {
                res.mElements[i] = this->mElements[i] * c;
            }

            return res;
        }

        Matrix<NDimension, MDimension> operator/(float c) const
        {
            Matrix<MDimension, NDimension> res;

            for (uint16_t i = 0; i < NDimension * MDimension; ++i)
            {
                res.mElements[i] = this->mElements[i] / c;
            }

            return res;
        }

        template <uint8_t KDimension>
        Matrix<NDimension, KDimension> operator*(const Matrix<MDimension, KDimension> &other) const
        {
            Matrix<NDimension, KDimension> res;

            for (uint8_t i = 0; i < NDimension; ++i)
            {
                for (uint8_t j = 0; j < KDimension; ++j)
                {
                    float sum = 0.0f;

                    for (uint8_t k = 0; k < MDimension; ++k)
                    {
                        sum += (*this)[i][k] * other[k][j];
                    }

                    res[i][j] = sum;
                }
            }

            return res;
        }

        const Matrix<NDimension, MDimension>& operator-=(const Matrix<NDimension, MDimension> &other)
        {
            for (uint16_t i = 0; i < NDimension * MDimension; ++i)
            {
                this->mElements[i] -= other.mElements[i];
            }

            return *this;
        }

        const Matrix<NDimension, MDimension>& operator+=(const Matrix<NDimension, MDimension> &other)
        {
            for (uint16_t i = 0; i < NDimension * MDimension; ++i)
            {
                this->mElements[i] += other.mElements[i];
            }

            return *this;
        }

        const Matrix<NDimension, MDimension>& operator*=(float c)
        {
            for (uint16_t i = 0; i < NDimension * MDimension; ++i)
            {
                this->mElements[i] *= c;
            }

            return *this;
        }

        const Matrix<NDimension, MDimension>& operator/=(float c)
        {
            for (uint16_t i = 0; i < NDimension * MDimension; ++i)
            {
                this->mElements[i] /= c;
            }

            return *this;
        }

        const Matrix<NDimension, MDimension>& operator*=(const Matrix<NDimension, MDimension> &other)
        {
            return *this = *this * other;
        }
    };

    typedef Matrix<2, 2> Matrix2x2;
    typedef Matrix<2, 3> Matrix2x3;
    typedef Matrix<2, 4> Matrix2x4;
    typedef Matrix<3, 2> Matrix3x2;
    typedef Matrix<3, 3> Matrix3x3;
    typedef Matrix<3, 4> Matrix3x4;
    typedef Matrix<4, 2> Matrix4x2;
    typedef Matrix<4, 3> Matrix4x3;

    template<uint8_t NDimension, uint8_t MDimension>
    Matrix<NDimension, MDimension> operator*(float c, const Matrix<NDimension, MDimension> &mat)
    {
        return mat * c;
    }
}

