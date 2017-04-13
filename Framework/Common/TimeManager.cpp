#include "TimeManager.h"
#include <chrono>

namespace Common
{
    TimeManager::TimeManager()
        : mCurrentTime(0.0), mLastRealTime(0.0), mDeltaTime(0.0f),
        mLastRealTimeInitialized(false), mIsTimePaused(false)
    {
    }

    double TimeManager::getTime() const
    {
        return mCurrentTime;
    }

    float TimeManager::getDeltaTime() const
    {
        return mDeltaTime;
    }

    double TimeManager::getRealTime() const
    {
        return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    }

    void TimeManager::pauseTime()
    {
        mIsTimePaused = true;
        mDeltaTime = 0.0f;
    }

    void TimeManager::resumeTime()
    {
        if (mIsTimePaused)
        {
            mIsTimePaused = false;
            mLastRealTime = getRealTime();
        }
    }

    void TimeManager::notifyFrameEnd()
    {
        if (!mIsTimePaused)
        {
            auto currentRealTime = getRealTime();

            if (mLastRealTimeInitialized)
            {
                mDeltaTime = float(currentRealTime - mLastRealTime);
                mCurrentTime += mDeltaTime;
            }
            else
            {
                mLastRealTimeInitialized = true;
            }

            mLastRealTime = currentRealTime;
        }
    }
}