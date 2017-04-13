#pragma once

#include <Mogren/Framework/Math/Vector3D.h>
#include <Mogren/Framework/Common/TouchAction.h>

namespace Input
{
    ///
    /// Container for touch event data
    ///
    class TouchData
    {
    public:
        ///
        /// Initializes new empty instance of a TouchData class
        ///
        TouchData();

        ///
        /// Initializes new instance of a TouchData class
        /// \param action The touch action (Up/Down/Move)
        /// \param touchRayStartPoint Start point of the touch ray (point from near screen plane)
        /// \param touchRayEndPoint End point of the touch ray (point from far screen plane)
        /// \param pointerId The pointer (finger) id. Id shouldn't be changed
        /// while user holds finger on the screen
        /// \param touchTime The time when the touch event occurred
        ///
        TouchData(
            Common::TouchAction action,
            Math::Point3DF touchRayStartPoint,
            Math::Point3DF touchRayEndPoint,
            int pointerId,
            double touchTime);

        ///
        /// Returns true, if this instance was created using parametrized constructor
        /// (that is, containing some data)
        ///
        bool isValid() const;

        ///
        /// Returns the touch action (Up/Down/Move)
        ///
        Common::TouchAction getAction() const;

        ///
        /// Returns the start point of the touch ray (point from near screen plane)
        ///
        Math::Point3DF getTouchRayStartPoint() const;

        ///
        /// Returns the end point of the touch ray (point from far screen plane)
        ///
        Math::Point3DF getTouchRayEndPoint() const;

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
        bool mIsValid;
        Common::TouchAction mAction;
        Math::Point3DF mTouchRayStartPoint;
        Math::Point3DF mTouchRayEndPoint;
        int mPointerId;
        double mTouchTime;
    };
}

