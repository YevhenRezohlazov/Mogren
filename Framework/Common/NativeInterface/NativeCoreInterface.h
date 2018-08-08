#pragma once

#include <Mogren/Framework/Math/Vector2D.h>

#include <functional>
#include <string>
#include "../TouchAction.h"

namespace Common
{
    class NativeCoreInterface
    {
    public:
        virtual void setInitializationCallback(std::function<void()> callback) = 0;
        virtual void setRenderCallback(std::function<void()> callback) = 0;
        virtual void setTouchInputCallback(std::function<void(TouchAction /*action*/, const Math::Point2DI& /*position*/, int /*pointerId*/)> callback) = 0;
        virtual void setBackButtonCallback(std::function<void()> callback) = 0;
        virtual void setTerminationCallback(std::function<void()> callback) = 0;

        virtual void setPauseCallback(std::function<void()> callback) = 0;
        virtual void setResumeCallback(std::function<void()> callback) = 0;

        virtual void terminateApp() = 0;

        ///
        /// Enables device vibration for given period of time.
        /// @param vibrationDuration Vibration duration in seconds.
        ///
        virtual void vibrateDevice(float vibrationDuration) = 0;

        virtual void showInterstitialAd() = 0;

        virtual void showVideoAd() = 0;

        virtual void openUrl(const std::string & url) = 0;

        virtual void keepDeviceAwake(bool keep) = 0;

        virtual Math::Size2DI getScreenSize() const = 0;

        virtual std::string getLocaleName() const = 0;

        virtual ~NativeCoreInterface() = default;
    };
}

