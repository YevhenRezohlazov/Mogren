#pragma once

namespace Graphics
{
    class NativeRenderTarget
    {
    public:
        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;

        virtual ~NativeRenderTarget() = default;
    };
}

