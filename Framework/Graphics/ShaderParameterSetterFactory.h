#pragma once

#include "PrimitiveTypes/ShaderParameterType.h"
#include <memory>

namespace Graphics
{
    class ShaderParameterSetter;
    class NativeShaderParameterSetter;

    ///
    /// Factory for creating shader parameter setters
    ///
    class ShaderParameterSetterFactory final
    {
    public:
        // disallow creating instance
        ShaderParameterSetterFactory() = delete;

        ///
        /// Creates setter corresponding to the given parameter type
        ///
        static std::unique_ptr<ShaderParameterSetter> create(
            ShaderParameterType parameterType,
            std::unique_ptr<NativeShaderParameterSetter> nativeSetter);
    };
}

