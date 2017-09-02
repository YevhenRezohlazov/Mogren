#pragma once

#include "Vector3D.h"
#include "Matrix.h"

namespace Math
{
    ///
    /// Represents quaternion.
    ///
    class Quaternion
    {
    public:
        float x;
        float y;
        float z;
        float w;

        Quaternion(const Vector3DF & axis, float angle);

        float getLength() const;

        void normalize();

        Matrix3x3 convertToRotationMatrix() const;
    };
}

