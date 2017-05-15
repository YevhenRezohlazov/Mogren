#include "Transformation3D.h"
#include <Mogren/Framework/Math/Functions.h>

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
        incrementVersion();
        return *this;
    }

    Transformation3D & Transformation3D::setRotation(const Math::Vector3DF & pitchYawRoll)
    {
        const char rotPitch = (char)(Math::abs(pitchYawRoll.x) > 1e-5f) << 0;
        const char rotYaw = (char)(Math::abs(pitchYawRoll.y) > 1e-5f) << 1;
        const char rotRoll = (char)(Math::abs(pitchYawRoll.z) > 1e-5f) << 2;

        auto pitchMatrix = Math::Matrix3x3::createIdentity();

        if (rotPitch)
        {
            const float pitchSin = Math::sin(pitchYawRoll.x);
            const float pitchCos = Math::cos(pitchYawRoll.x);
            pitchMatrix[1][1] = pitchCos;
            pitchMatrix[1][2] = pitchSin;
            pitchMatrix[2][1] = -pitchSin;
            pitchMatrix[2][2] = pitchCos;
        }

        auto yawMatrix = Math::Matrix3x3::createIdentity();

        if (rotYaw)
        {
            const float yawSin = Math::sin(pitchYawRoll.y);
            const float yawCos = Math::cos(pitchYawRoll.y);
            yawMatrix[0][0] = yawCos;
            yawMatrix[0][2] = -yawSin;
            yawMatrix[2][0] = yawSin;
            yawMatrix[2][2] = yawCos;
        }

        auto rollMatrix = Math::Matrix3x3::createIdentity();

        if (rotRoll)
        {
            const float rollSin = Math::sin(pitchYawRoll.z);
            const float rollCos = Math::cos(pitchYawRoll.z);
            rollMatrix[0][0] = rollCos;
            rollMatrix[0][1] = rollSin;
            rollMatrix[1][0] = -rollSin;
            rollMatrix[1][1] = rollCos;
        }

        auto rotMatrix = Math::Matrix3x3::createIdentity();

        switch (rotPitch + rotYaw + rotRoll)
        {
        case 0/*nothing*/: break;
        case 1/*pitch*/: rotMatrix = pitchMatrix; break;
        case 2/*yaw*/: rotMatrix = yawMatrix; break;
        case 3/*pitch*yaw*/: rotMatrix = pitchMatrix * yawMatrix; break;
        case 4/*roll*/: rotMatrix = rollMatrix; break;
        case 5/*roll * pitch*/: rotMatrix = rollMatrix * pitchMatrix; break;
        case 6/*roll * yaw*/: rotMatrix = rollMatrix * yawMatrix; break;
        case 7/*roll * pitch * yaw*/: rotMatrix = rollMatrix * pitchMatrix * yawMatrix; break;
        }

        mMatrix.m00 = rotMatrix[0][0] * mScale.x;
        mMatrix.m10 = rotMatrix[1][0] * mScale.x;
        mMatrix.m20 = rotMatrix[2][0] * mScale.x;
        
        mMatrix.m01 = rotMatrix[0][1] * mScale.y;
        mMatrix.m11 = rotMatrix[1][1] * mScale.y;
        mMatrix.m21 = rotMatrix[2][1] * mScale.y;

        mMatrix.m02 = rotMatrix[0][2] * mScale.z;
        mMatrix.m12 = rotMatrix[1][2] * mScale.z;
        mMatrix.m22 = rotMatrix[2][2] * mScale.z;

        incrementVersion();
        return *this;
    }

    Transformation3D & Transformation3D::setScale(const Math::Vector3DF & scale)
    {
        mMatrix.m00 *= scale.x / mScale.x;
        mMatrix.m10 *= scale.x / mScale.x;
        mMatrix.m20 *= scale.x / mScale.x;

        mMatrix.m01 *= scale.y / mScale.y;
        mMatrix.m11 *= scale.y / mScale.y;
        mMatrix.m21 *= scale.y / mScale.y;

        mMatrix.m02 *= scale.z / mScale.z;
        mMatrix.m12 *= scale.z / mScale.z;
        mMatrix.m22 *= scale.z / mScale.z;

        mScale = scale;

        incrementVersion();
        return *this;
    }

    Math::Vector3DF Transformation3D::getScale() const
    {
        return mScale;
    }
}