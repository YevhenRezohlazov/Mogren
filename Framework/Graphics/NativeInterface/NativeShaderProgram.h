#pragma once

#include <Mogren/Framework/ResourceManagement/NativeInterface/NativeResource.h>
#include <memory>

namespace Graphics
{
    class NativeShaderParameterSet;
    ///
    /// Native shader interface
    ///
    class NativeShaderProgram : public ResourceManagement::NativeResource
    {
    public:
        ///
        /// Creates new instance of the shader parameter set.
        ///
        virtual std::unique_ptr<NativeShaderParameterSet> createParameterSet() const = 0;

        virtual ~NativeShaderProgram() = default;
    };
}

