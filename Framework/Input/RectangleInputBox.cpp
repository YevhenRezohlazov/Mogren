#include "RectangleInputBox.h"

namespace Input
{
    RectangleInputBox::RectangleInputBox(
        const Math::RectangleF &rectangle,
        TouchCallback touchCallback,
        TouchCallback touchPreviewCallback)
    {
        mRectangle = rectangle;
        mTouchCallback = touchCallback;
        mTouchPreviewCallback = touchPreviewCallback;
    }

    const Math::RectangleF& RectangleInputBox::getRectangle() const
    {
        return mRectangle;
    }

    void RectangleInputBox::setRectangle(const Math::RectangleF& rectangle)
    {
        mRectangle = rectangle;
    }

    RectangleInputBox::TouchCallback RectangleInputBox::getTouchCallback() const
    {
        return mTouchCallback;
    }

    void RectangleInputBox::setTouchCallback(TouchCallback callback)
    {
        mTouchCallback = callback;
    }

    RectangleInputBox::TouchCallback RectangleInputBox::getTouchPreviewCallback() const
    {
        return mTouchPreviewCallback;
    }

    void RectangleInputBox::setTouchPreviewCallback(TouchCallback callback)
    {
        mTouchPreviewCallback = callback;
    }

    bool RectangleInputBox::checkTouch(const Math::Point3DF &touchRayStartPoint, const Math::Point3DF &touchRayEndPoint) const
    {
        Math::Point2DF point = getRayIntersectionPoint(touchRayStartPoint, touchRayEndPoint);
        return mRectangle.containsPoint(point);
    }

    bool RectangleInputBox::isProcessingTouchPreviews() const
    {
        return (bool)mTouchPreviewCallback;
    }

    bool RectangleInputBox::processTouchPreview(const TouchData &touchData)
    {
        if (mTouchPreviewCallback)
        {
            RectangleTouchData rectTouchData(
                touchData.getAction(),
                getRayIntersectionPoint(touchData.getTouchRayStartPoint(), touchData.getTouchRayEndPoint()),
                touchData.getPointerId(),
                touchData.getTouchTime());

            return mTouchPreviewCallback(*this, rectTouchData);
        }

        return false;
    }

    bool RectangleInputBox::processTouch(const TouchData &touchData)
    {
        if (mTouchCallback)
        {
            RectangleTouchData rectTouchData(
                touchData.getAction(),
                getRayIntersectionPoint(touchData.getTouchRayStartPoint(), touchData.getTouchRayEndPoint()),
                touchData.getPointerId(),
                touchData.getTouchTime());

            return mTouchCallback(*this, rectTouchData);
        }

        return false;
    }

    Math::Point2DF RectangleInputBox::getRayIntersectionPoint(
        const Math::Point3DF& rayStartPoint,
        const Math::Point3DF& rayEndPoint)
    {
        float zc = -rayStartPoint.z / (rayEndPoint.z - rayStartPoint.z);

        return Math::Point2DF(
            rayStartPoint.x + zc * (rayEndPoint.x - rayStartPoint.x),
            rayStartPoint.y + zc * (rayEndPoint.y - rayStartPoint.y));
    }
}