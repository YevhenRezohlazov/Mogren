#include "Quaternion.h"
#include "Functions.h"

namespace Math
{
    Math::Quaternion::Quaternion(const Vector3DF & axis, float angle)
    {
        const auto sina = Math::sin(angle);
        const auto cosa = Math::cos(angle);
        x = axis.x * sina;
        y = axis.y * sina;
        z = axis.z * sina;
        w = cosa;
        normalize();
    }

    float Quaternion::getLength() const
    {
        return sqrt(x * x + y * y + z * z + w * w);
    }

    void Quaternion::normalize()
    {
        const auto invLength = 1.0f / getLength();
        x *= invLength;
        y *= invLength;
        z *= invLength;
        w *= invLength;
    }

    Matrix3x3 Quaternion::convertToRotationMatrix() const
    {
        const auto xx = x * x;
        const auto xy = x * y;
        const auto xz = x * z;
        const auto xw = x * w;

        const auto yy = y * y;
        const auto yz = y * z;
        const auto yw = y * w;

        const auto zz = z * z;
        const auto zw = z * w;

        Matrix3x3 result;

        result[0][0] = 1 - 2 * (yy + zz);
        result[0][1] = 2 * (xy - zw);
        result[0][2] = 2 * (xz + yw);

        result[1][0] = 2 * (xy + zw);
        result[1][1] = 1 - 2 * (xx + zz);
        result[1][2] = 2 * (yz - xw);

        result[2][0] = 2 * (xz - yw);
        result[2][1] = 2 * (yz + xw);
        result[2][2] = 1 - 2 * (xx + yy);

        return result;
    }
}

