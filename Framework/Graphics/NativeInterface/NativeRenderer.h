#pragma once

#include "../PrimitiveTypes/Viewport.h"
#include "../PrimitiveTypes/Color.h"

namespace Graphics
{
    class NativeGeometry;
    class NativeShaderProgram;
    class NativeShaderParameterSet;
    class NativeRenderTarget;

    ///
    /// The native renderer interface
    ///
    class NativeRenderer
    {
    public:
        ///
        /// Prepares render and clears the render target if needed.
        ///
        virtual void prepareRender(
            const NativeRenderTarget& renderTarget,
            const Viewport &viewport,
            bool clear,
            const Color &clearColor) = 0;

        ///
        /// Renders the current geometry using the current shader to the current render target.
        ///
        virtual void render(
            const NativeGeometry &geometry,
            const NativeShaderProgram &shaderProgram,
            const NativeShaderParameterSet& shaderParameterSet) = 0;

        virtual void finishRender() = 0;

        virtual ~NativeRenderer() = default;
    };
}

