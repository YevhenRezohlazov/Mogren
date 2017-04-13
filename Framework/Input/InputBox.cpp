#include "InputBox.h"

namespace Input
{
    InputBox::InputBox() : mState(InputBoxState::Enabled)
    {
    }

    Input::InputBoxState InputBox::getState() const
    {
        return mState;
    }

    void InputBox::setState(InputBoxState state)
    {
        mState = state;
    }
}