#include "ShaderProgram.h"
#include "NativeInterface/NativeShaderProgram.h"
#include <assert.h>

namespace Graphics
{
    ShaderProgram::ShaderProgram(
        const std::unordered_map<std::string, std::string> &options,
        const std::unordered_map<std::string, ShaderParameterType> &parameters,
        std::unique_ptr<NativeShaderProgram> nativeShaderProgram)
    {
        mOptions = options;
        mParameters = parameters;
        mNativeShaderProgram = std::move(nativeShaderProgram);
        assert(mNativeShaderProgram != nullptr);
    }

    const std::unordered_map<std::string, std::string>& ShaderProgram::getOptions() const
    {
        return mOptions;
    }

    const std::unordered_map<std::string, ShaderParameterType>& ShaderProgram::getParameters() const
    {
        return mParameters;
    }

    const NativeShaderProgram& ShaderProgram::getNativeShaderProgram() const
    {
        return *mNativeShaderProgram;
    }

    ShaderProgram::~ShaderProgram() = default;

    void ShaderProgram::finalize()
    {
        mNativeShaderProgram->finalize();
    }

}