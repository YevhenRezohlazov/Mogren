#pragma once

#include <Mogren/Framework/Common/TouchAction.h>
#include <Mogren/Framework/Common/TimeManager.h>
#include <Mogren/Framework/Animation/AnimationManager.h>
#include <Mogren/Framework/ResourceManagement/ResourceManager.h>

#include <Mogren/Framework/Math/Vector2D.h>
#include <vector>
#include <memory>
#include <functional>
#include <mutex>

namespace Graphics
{
    class RenderTarget;
}

namespace App
{
    ///
    /// Base Mogren application class.
    ///
    class Application
    {
    protected:
        ///
        /// Creates a new instance of Application class.
        ///
        Application();

        ///
        /// Terminates the application.
        ///
        void terminate();

    public:
        ///
        /// Called before rendering a frame
        ///
        virtual void prerender();

        ///
        /// Called to render a frame
        ///
        virtual void render();

        ///
        /// Called after rendering a frame
        ///
        virtual void postrender();

        ///
        /// When implemented in derived class, processes touch events. The method can be called from non-main thread.
        /// \param touchAction The touch action.
        /// \param position The touch position in screen coordinates.
        /// \param pointerId The touch pointer index.
        ///
        virtual void onTouch(Common::TouchAction touchAction, const Math::Point2DI &position, int pointerId);

        ///
        /// Called when the application is paused.
        ///
        virtual void onPause();

        ///
        /// Called when the application is resumed.
        ///
        virtual void onResume();

        ///
        /// When implemented in derived class, processes back button press action.
        ///
        virtual void onBackButtonPress();

        void keepDeviceAwake(bool keep);
        void vibrateDevice(float vibrationDuration);

        virtual const Common::TimeManager& getTimeManager() const;
        virtual Common::TimeManager& getTimeManager();
        virtual const ResourceManagement::ResourceManager& getResourceManager() const;
        virtual ResourceManagement::ResourceManager& getResourceManager();
        virtual const Animation::AnimationManager& getAnimationManager() const;
        virtual Animation::AnimationManager& getAnimationManager();
        std::shared_ptr<Graphics::RenderTarget> getDisplayRenderTarget();

        virtual ~Application();

        static void setup(std::function< std::unique_ptr<Application>() > applicationCreator);
        static Application & getInstance();

    protected:
        Common::TimeManager mTimeManager;
        ResourceManagement::ResourceManager mResourceManager;
        Animation::AnimationManager mAnimationManager;
        std::shared_ptr<Graphics::RenderTarget> mDisplayRenderTarget;

    private:
        static std::unique_ptr<Application> mInstance;
        static Application* mRawInstance;
    };
}
