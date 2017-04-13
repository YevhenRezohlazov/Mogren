#include "OpenAL.h"

namespace Audio
{
    void OpenAL::initialize()
    {
        mDevice = alcOpenDevice(0);
        mContext = alcCreateContext(mDevice, 0);
        alcMakeContextCurrent(mContext);
    }

    void OpenAL::destroy()
    {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(mContext);
        alcCloseDevice(mDevice);
    }

    ALCcontext * OpenAL::mContext;

    ALCdevice * OpenAL::mDevice;
}