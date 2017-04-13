#include "RectangleTouchData.h"

namespace Input
{
    using namespace Common;

    RectangleTouchData::RectangleTouchData(TouchAction action, Math::Point2DF touchPosition, int pointerId, double touchTime)
        : mAction(action), mTouchPosition(touchPosition), mPointerId(pointerId), mTouchTime(touchTime)
    {
    }

    TouchAction RectangleTouchData::getAction() const
    {
        return mAction;
    }

    Math::Point2DF RectangleTouchData::getTouchPosition() const
    {
        return mTouchPosition;
    }

    int RectangleTouchData::getPointerId() const
    {
        return mPointerId;
    }

    double RectangleTouchData::getTouchTime() const
    {
        return mTouchTime;
    }
}