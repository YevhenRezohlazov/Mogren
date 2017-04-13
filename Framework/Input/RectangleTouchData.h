#pragma once

#include <Mogren/Framework/Math/Vector2D.h>
#include <Mogren/Framework/Common/TouchAction.h>

namespace Input
{
    ///
    /// Container for touch data received from rectangle input box (RectangleInputBox)
    ///
    class RectangleTouchData
    {
    public:
        ///
        /// Initializes new instance of a RectangleTouchData class
        /// \param action The touch action (Up/Down/Move)
        /// \param touchPosition The touch position (relative to input rectangle's left top corner)
        /// \param pointerId The pointer (finger) id. Id shouldn't be changed
        /// while user holds finger on the screen
        /// \param touchTime The time when the touch event occurred
        ///
        RectangleTouchData(
            Common::TouchAction action,
            Math::Point2DF touchPosition,
            int pointerId,
            double touchTime);

        ///
        /// Returns the touch action (Up/Down/Move)
        ///
        Common::TouchAction getAction() const;

        ///
        /// Returns the touch position (relative to input rectangle's left top corner)
        ///
        Math::Point2DF getTouchPosition() const;

        ///
        /// Return the The pointer (finger) id. Id isn't changed
        /// while user holds finger on the screen
        ///
        int getPointerId() const;

        ///
        /// Returns the time when the touch event occurred
        ///
        double getTouchTime() const;


    private:
        Common::TouchAction mAction;
        Math::Point2DF mTouchPosition;
        int mPointerId;
        double mTouchTime;
    };
}

