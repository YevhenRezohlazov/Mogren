#pragma once

#include <Mogren/Framework/Math/Rectangle.h>
#include "InputBox.h"
#include "RectangleTouchData.h"
#include <functional>

namespace Input
{
    ///
    /// InputBox implementation for handling input events in a rectangular area
    ///
    class RectangleInputBox : public InputBox
    {
    public:
        ///
        /// Rectangle touch callback function
        /// \param sender Sender input box
        /// \param touchData The touch data
        /// \returns True if event is handled and shouldn't be dispatched further
        ///
        typedef std::function<bool(RectangleInputBox &sender, const RectangleTouchData &touchData)> TouchCallback;

    public:
        ///
        /// Initializes new instance of a RectangleInputBox class
        /// \param rectangle Input rectangle bounds
        /// \param touchCallback Callback called when a touch event received
        /// \param touchPreviewCallback Callback called when a touch event preview received
        /// \param parent The parent item.
        ///
        explicit RectangleInputBox(
            const Math::RectangleF &rectangle = Math::RectangleF(),
            TouchCallback touchCallback = TouchCallback(),
            TouchCallback touchPreviewCallback = TouchCallback());

        ///
        /// Returns the input rectangle bounds
        ///
        const Math::RectangleF& getRectangle() const;

        ///
        /// Sets the input rectangle bounds
        /// \param rectangle Input rectangle bounds
        ///
        virtual void setRectangle(const Math::RectangleF& rectangle);

        ///
        /// Returns the callback that is called when a touch event received
        ///
        TouchCallback getTouchCallback() const;

        ///
        /// Sets the callback that is called when a touch event received
        ///
        virtual void setTouchCallback(TouchCallback callback);

        ///
        /// Returns the callback that is called when a touch event preview received
        ///
        TouchCallback getTouchPreviewCallback() const;

        ///
        /// Sets the callback that is called when a touch event preview received
        ///
        virtual void setTouchPreviewCallback(TouchCallback callback);

        virtual bool checkTouch(const Math::Point3DF &touchRayStartPoint, const Math::Point3DF &touchRayEndPoint) const;

        virtual bool isProcessingTouchPreviews() const;

        virtual bool processTouchPreview(const TouchData &touchData);

        virtual bool processTouch(const TouchData &touchData);

    private:
        ///
        /// Gets intersection point of given ray and XY plane (Z = 0)
        ///
        static Math::Point2DF getRayIntersectionPoint(
            const Math::Point3DF& rayStartPoint,
            const Math::Point3DF& rayEndPoint);

    private:
        Math::RectangleF mRectangle;
        TouchCallback mTouchCallback;
        TouchCallback mTouchPreviewCallback;
    };
}

