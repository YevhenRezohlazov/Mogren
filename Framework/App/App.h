#pragma once

#include <memory>
#include <functional>

namespace Common
{
    class TimeManager;
}

namespace ResourceManagement
{
    class ResourceManager;
}

namespace Animation
{
    class AnimationManager;
}

namespace Graphics
{
    class RenderTarget;
}

namespace App
{
    const Common::TimeManager& getTimeManager();
    const ResourceManagement::ResourceManager& getResourceManager();
    Animation::AnimationManager& getAnimationManager();
    std::shared_ptr<Graphics::RenderTarget> getDisplayRenderTarget();
}
