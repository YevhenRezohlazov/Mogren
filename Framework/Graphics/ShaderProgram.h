#pragma once

#include "PrimitiveTypes/ShaderParameterType.h"
#include <Mogren/Framework/ResourceManagement/Resource.h>
#include <unordered_map>
#include <string>
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
        ShaderProgram(
            const std::unordered_map<std::string, std::string> &options,
            const std::unordered_map<std::string, ShaderParameterType> &parameters,
            std::unique_ptr<NativeShaderProgram> nativeShaderProgram);

        ///
        /// Gets map of shader options and their values
        ///
        const std::unordered_map<std::string, std::string>& getOptions() const;

        ///
        /// Gets map of shader parameter names and their types
        ///
        const std::unordered_map<std::string, ShaderParameterType>& getParameters() const;

        ///
        /// Gets the native shader implementation.
        ///
        const NativeShaderProgram& getNativeShaderProgram() const;

        ~ShaderProgram();

    protected:
        virtual void finalize() override;

    private:
        std::unordered_map<std::string, std::string> mOptions;
        std::unordered_map<std::string, ShaderParameterType> mParameters;
        std::unique_ptr<NativeShaderProgram> mNativeShaderProgram;
    };
}

