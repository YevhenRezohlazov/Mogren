#pragma once

#include <Mogren/Framework/ResourceManagement/NativeInterface/NativeResource.h>

namespace Graphics
{
    class NativeTexture : public ResourceManagement::NativeResource
    {
    public:
        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;

        virtual ~NativeTexture() = default;
    };
}

