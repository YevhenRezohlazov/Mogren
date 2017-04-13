#include "TouchData.h"

namespace Input
{
    TouchData::TouchData(
        Common::TouchAction action,
        Math::Point3DF touchRayStartPoint,
        Math::Point3DF touchRayEndPoint,
        int pointerId,
        double touchTime)
        : mIsValid(true), mAction(action),
        mTouchRayStartPoint(touchRayStartPoint), mTouchRayEndPoint(touchRayEndPoint),
        mPointerId(pointerId), mTouchTime(touchTime)
    {
    }

    TouchData::TouchData() : mIsValid(false)
    {
    }

    Common::TouchAction TouchData::getAction() const
    {
        return mAction;
    }

    int TouchData::getPointerId() const
    {
        return mPointerId;
    }

    double TouchData::getTouchTime() const
    {
        return mTouchTime;
    }

    Math::Point3DF TouchData::getTouchRayStartPoint() const
    {
        return mTouchRayStartPoint;
    }

    Math::Point3DF TouchData::getTouchRayEndPoint() const
    {
        return mTouchRayEndPoint;
    }

    bool TouchData::isValid() const
    {
        return mIsValid;
    }
}