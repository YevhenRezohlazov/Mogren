#include "App.h"
#include "Application.h"

namespace App
{
    const Common::TimeManager & getTimeManager()
    {
        return Application::getInstance().getTimeManager();
    }

    const ResourceManagement::ResourceManager & getResourceManager()
    {
        return Application::getInstance().getResourceManager();
    }

    Animation::AnimationManager & getAnimationManager()
    {
        return Application::getInstance().getAnimationManager();
    }

    std::shared_ptr<Graphics::RenderTarget> getDisplayRenderTarget()
    {
        return Application::getInstance().getDisplayRenderTarget();
    }
}