#pragma once

#include "NativeShaderParameterSetter.h"
#include "../PrimitiveTypes/ShaderParameterType.h"
#include <string>
#include <memory>

namespace Graphics
{
    class NativeShaderParameterSetter;

    class NativeShaderParameterSet
    {
    public:
        ///
        /// Gets the shader parameters collections.
        ///
        virtual std::unique_ptr<NativeShaderParameterSetter> createParameterSetter(
            const std::string& name, ShaderParameterType type) = 0;

        virtual ~NativeShaderParameterSet() = default;
    };
}
