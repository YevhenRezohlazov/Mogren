#pragma once

#include "PrimitiveTypes/ShaderParameterType.h"
#include <Mogren/Framework/ResourceManagement/Resource.h>
#include <memory>

namespace Graphics
{
    class NativeShaderProgram;

    ///
    /// Contains compiled shader program (loaded using ResourceManager)
    ///
    class ShaderProgram final : public ResourceManagement::Resource
    {
    public:
        ///
        /// Initializes a new instance of the ShaderProgram class.
        ///
        /// \param options The map of shader options.
        /// \param uniforms The map of shader uniforms with their types.
        /// \param nativeShader The native shader implementation.
        explicit ShaderProgram(std::unique_ptr<NativeShaderProgram> nativeShaderProgram);

        ///
        /// Gets the native shader implementation.
        ///
        const NativeShaderProgram& getNativeShaderProgram() const;

        virtual ~ShaderProgram();

    protected:
        virtual void finalize() override;

    private:
        std::unique_ptr<NativeShaderProgram> mNativeShaderProgram;
    };
}

