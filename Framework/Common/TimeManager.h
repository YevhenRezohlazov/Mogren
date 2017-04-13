#pragma once

namespace Common
{
    class TimeManager
    {
    private:
        double mCurrentTime;
        double mLastRealTime;
        float mDeltaTime;

        bool mLastRealTimeInitialized;
        bool mIsTimePaused;

    public:
        ///
        /// Creates a new instance of TimeManager class.
        ///
        TimeManager();

        ///
        /// Returns the time (in seconds) since the application started (pause time is not included).
        ///
        double getTime() const;

        ///
        /// Returns the time (in seconds) elapsed from the last frame (pause time is not included).
        ///
        float getDeltaTime() const;

        ///
        /// Returns the real current time (in seconds) (including pause time).
        ///
        double getRealTime() const;

        ///
        /// Pauses the time flow so the TimeManager will return the same time until resumeTime is called.
        ///
        void pauseTime();

        ///
        /// Resumes the time flow from the point it was paused.
        ///
        void resumeTime();

        ///
        /// Should be called when the current frame is ended.
        ///
        void notifyFrameEnd();
    };
}


