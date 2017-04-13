#include "EasingFunctions.h"
#include <Mogren/Framework/Math/Functions.h>

namespace Animation
{
    float EasingFunctions::linear(float t)
    {
        return t;
    }

    float EasingFunctions::easeInQuad(float t)
    {
        return t * t;
    }

    float EasingFunctions::easeOutQuad(float t)
    {
        return -t * (t - 2);
    }

    float EasingFunctions::easeInOutQuad(float t)
    {
        t *= 2.0f;
        if (t < 1.0f) return 0.5f * t * t;
        t -= 1.0f;
        return -0.5f * (t * (t - 2.0f) - 1.0f);
    }

    float EasingFunctions::easeInCubic(float t)
    {
        return t * t * t;
    }

    float EasingFunctions::easeOutCubic(float t)
    {
        t -= 1.0f;
        return t * t * t + 1.0f;
    }

    float EasingFunctions::easeInOutCubic(float t)
    {
        t *= 2.0f;
        if (t < 1.0f) return 0.5f * t * t * t;
        t -= 2.0f;
        return 0.5f * (t * t * t + 2.0f);
    }

    float EasingFunctions::easeInQuart(float t)
    {
        return t * t * t * t;
    }

    float EasingFunctions::easeOutQuart(float t)
    {
        t -= 1.0f;
        return -(t * t * t * t - 1.0f);
    }

    float EasingFunctions::easeInOutQuart(float t)
    {
        t *= 2.0f;
        if (t < 1.0f) return 0.5f * t * t * t * t;
        t -= 2.0f;
        return -0.5f * (t * t * t * t - 2);
    }

    float EasingFunctions::easeInQuint(float t)
    {
        return t * t * t * t * t;
    }

    float EasingFunctions::easeOutQuint(float t)
    {
        t -= 1.0f;
        return t * t * t * t * t + 1.0f;
    }

    float EasingFunctions::easeInOutQuint(float t)
    {
        t *= 2.0f;
        if (t < 1.0f) return 0.5f * t * t * t * t * t;
        t -= 2.0f;
        return 0.5f * (t * t * t * t * t + 2.0f);
    }

    float EasingFunctions::easeInSine(float t)
    {
        return -Math::cos(t * Math::PI * 0.5f) + 1.0f;
    }

    float EasingFunctions::easeOutSine(float t)
    {
        return Math::sin(t * Math::PI * 0.5f);
    }

    float EasingFunctions::easeInOutSine(float t)
    {
        return -0.5f * (Math::cos(Math::PI*t) - 1.0f);
    }

    float EasingFunctions::easeInExpo(float t)
    {
        return (t == 0.0f) ? 0.0f : Math::pow(2.0f, 10.0f * (t - 1.0f));
    }

    float EasingFunctions::easeOutExpo(float t)
    {
        return (t == 1.0f) ? 1.0f : (-Math::pow(2.0f, -10.0f * t) + 1.0f);
    }

    float EasingFunctions::easeInOutExpo(float t)
    {
        if (t == 0) return 0.0f;
        if (t == 1.0f) return 1.0f;
        t *= 2.0f;
        if (t < 1) return 0.5f * Math::pow(2.0f, 10.0f * (t - 1.0f));
        t -= 1.0f;
        return 0.5f * (-Math::pow(2.0f, -10.0f * t) + 2.0f);
    }

    float EasingFunctions::easeInCirc(float t)
    {
        return -(Math::sqrt(1.0f - t * t) - 1.0f);
    }

    float EasingFunctions::easeOutCirc(float t)
    {
        t -= 1.0f;
        return Math::sqrt(1.0f - t*t);
    }

    float EasingFunctions::easeInOutCirc(float t)
    {
        t *= 2.0f;
        if (t < 1.0f) return -0.5f * (Math::sqrt(1.0f - t * t) - 1.0f);
        t -= 2.0f;
        return 0.5f * (Math::sqrt(1.0f - t * t) + 1.0f);
    }

    float EasingFunctions::easeInElastic(float t)
    {
        const float p = 0.3f;
        if (t == 0.0f) return 0.0f;
        if (t == 1) return 1.0f;
        const float s = p / (2.0f * Math::PI) * Math::Half_PI;
        t -= 1.0f;
        return -(Math::pow(2.0f, 10.0f * t) * Math::sin((t * 1.0f - s) * (2.0f * Math::PI) / p));
    }

    float EasingFunctions::easeOutElastic(float t)
    {
        const float p = 0.3f;
        if (t == 0.0f) return 0.0f;
        if (t == 1.0f) return 1.0f;
        const float s = p / (2.0f * Math::PI) * Math::Half_PI;
        return Math::pow(2.0f, -10.0f * t) * Math::sin((t * 1.0f - s) * (2.0f * Math::PI) / p) + 1.0f;
    }

    float EasingFunctions::easeInOutElastic(float t)
    {
        if (t == 0.0f) return 0.0f;
        t *= 2.0f;
        if (t == 2.0f) return 1.0f;
        const float p = 0.3f * 1.5f;
        const float s = p / (2.0f * Math::PI) * Math::Half_PI;

        t -= 1.0f;
        if (t < 1.0f)
            return -0.5f * (Math::pow(2.0f, 10.0f * t) * Math::sin( (t * 1.0f - s) * (2.0f * Math::PI) / p));
        return Math::pow(2.0f, -10.0f*t) * Math::sin((t - s) * (2.0f * Math::PI) / p) * 0.5f + 1.0f;
    }

    float EasingFunctions::easeInBack(float t)
    {
        const float s = 1.70158f;
        return t * t * ((s + 1.0f) * t - s);
    }

    float EasingFunctions::easeOutBack(float t)
    {
        const float s = 1.70158f;
        t -= 1.0f;
        return 1.0f * (t * t * ((s + 1.0f) * t + s) + 1.0f);
    }

    float EasingFunctions::easeInOutBack(float t)
    {
        const float s = 1.70158f * 1.525f;
        t *= 2.0f;
        if (t < 1.0f) return 0.5f * (t * t * ((s + 1.0f) * t - s));
        t -= 2.0f;
        return 0.5f * (t * t * ((s + 1) * t + s) + 2.0f);
    }

    float EasingFunctions::easeInBounce(float t)
    {
        return 1.0f - easeOutBounce(1.0f - t);
    }

    float EasingFunctions::easeOutBounce(float t)
    {
        if (t < (1.0f / 2.75f))
        {
            return (7.5625f * t * t);
        }
        else if (t < (2.0f / 2.75f))
        {
            t -= 1.5f / 2.75f;
            return 1.0f * (7.5625f * t * t + .75f) + 0.0f;
        }
        else if (t < (2.5f / 2.75f))
        {
            t -= 2.25f / 2.75f;
            return 7.5625f * t * t + 0.9375f;
        }
        else
        {
            t -= 2.625f / 2.75f;
            return (7.5625f * t) * t + 0.984375f;
        }
    }

    float EasingFunctions::easeInOutBounce(float t)
    {
        if (t < 0.5f) return easeInBounce (t * 2) * 0.5f;
        return easeOutBounce (t * 2.0f - 1.0f) * 0.5f + 0.5f;
    }
}