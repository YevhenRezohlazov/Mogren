#include "Transformation3D.h"

namespace Common
{
    Transformation3D::Transformation3D()
    {
    }

    Math::Vector3DF Transformation3D::getPosition() const
    {
        return Math::Vector3DF(mMatrix.m30, mMatrix.m31, mMatrix.m32);
    }

    Transformation3D & Transformation3D::setPosition(const Math::Vector3DF & position)
    {
        mMatrix.m30 = position.x;
        mMatrix.m31 = position.y;
        mMatrix.m32 = position.z;
        return *this;
    }
}