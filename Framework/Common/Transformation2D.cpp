#include "Transformation2D.h"
#include <cmath>
#include <assert.h>

namespace Common
{
    Transformation2D::Transformation2D()
        : mRotationAngle(0.0f), mScale(Math::Vector2DF(1.0f, 1.0f))
    {
    }

    Math::Vector2DF Transformation2D::getPosition() const
    {
        return Math::Vector2DF(mMatrix.m30, mMatrix.m31);
    }

    Transformation2D& Transformation2D::setPosition(const Math::Vector2DF& position)
    {
        mMatrix.m30 = position.x;
        mMatrix.m31 = position.y;
        incrementVersion();
        return *this;
    }

    float Transformation2D::getRotationAngle() const
    {
        return mRotationAngle;
    }

    Transformation2D& Transformation2D::setRotationAngle(float angle)
    {
        mRotationAngle = angle;
        auto sinv = Math::sin(mRotationAngle);
        auto cosv = Math::cos(mRotationAngle);

        mMatrix.m00 = cosv * mScale.x;
        mMatrix.m01 = sinv * mScale.y;
        mMatrix.m10 = -sinv * mScale.x;
        mMatrix.m11 = cosv * mScale.y;

        incrementVersion();
        return *this;
    }

    Math::Vector2DF Transformation2D::getScale() const
    {
        return mScale;
    }

    Transformation2D& Transformation2D::setScale(const Math::Vector2DF &scale)
    {
        assert(std::isfinite(scale.x) && std::isfinite(scale.y));
        if (mScale.x == 0.0f || mScale.y == 0.0f)
        {
            mScale = scale;
            setRotationAngle(mRotationAngle);
        }
        else
        {
            auto invX = 1.0f / mScale.x;
            auto invY = 1.0f / mScale.y;

            mMatrix.m00 *= invX * scale.x;
            mMatrix.m10 *= invX * scale.x;
            mMatrix.m01 *= invY * scale.y;
            mMatrix.m11 *= invY * scale.y;

            mScale = scale;
            incrementVersion();
        }

        return *this;
    }
}