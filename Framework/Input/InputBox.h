#pragma once

#include <Mogren/Framework/Common/SceneItem.h>
#include <Mogren/Framework/Math/Vector3D.h>

#include "TouchData.h"
#include "InputBoxState.h"

namespace Input
{
    ///
    /// Base input box class.
    /// Used to handle touch events.
    ///
    class InputBox : public Common::SceneItem
    {
    protected:
        InputBox();

    public:
        ///
        /// Returns current input box state
        ///
        InputBoxState getState() const;

        ///
        /// Sets the current input box state
        ///
        virtual void setState(InputBoxState state);

        ///
        /// Checks if touch with given position should be dispatched to
        /// this input box (that is, processPreviewTouch and processTouch methods
        /// should be called)
        /// \param touchRayStartPoint Start point of the touch ray (point from near screen plane)
        /// \param touchRayEndPoint End point of the touch ray (point from far screen plane)
        /// \returns True, if the touch should be dispatched to this input box
        ///
        virtual bool checkTouch(const Math::Point3DF &touchRayStartPoint, const Math::Point3DF &touchRayEndPoint) const = 0;

        ///
        /// Returns true, if input box should receive touch event previews
        ///
        virtual bool isProcessingTouchPreviews() const = 0;

        ///
        /// Processes the given touch event preview(see 'Processing Touch Events' article in Mogren wiki)
        /// \param touchData The touch data
        ///
        virtual bool processTouchPreview(const TouchData &touchData) = 0;

        ///
        /// Processes the given touch event (see 'Processing Touch Events' article in Mogren wiki)
        /// \param touchData The touch data
        ///
        virtual bool processTouch(const TouchData &touchData) = 0;

    private:
        InputBoxState mState;
    };
}

