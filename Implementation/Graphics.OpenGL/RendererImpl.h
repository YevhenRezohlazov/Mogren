#pragma once

#include <Mogren/Framework/Graphics/NativeInterface/NativeRenderer.h>

namespace Graphics
{
    class RendererImpl : public NativeRenderer
    {
    public:
        RendererImpl();

        virtual void prepareRender(
            const NativeRenderTarget& renderTarget,
            const Viewport &viewport,
            bool clear,
            const Color &clearColor) override;

        virtual void render(
            const NativeGeometry &geometry,
            const NativeShaderProgram &shaderProgram,
            const NativeShaderParameterSet& shaderParameterSet) override;

        virtual void finishRender() override;
    };
}

