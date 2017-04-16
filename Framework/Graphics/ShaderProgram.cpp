#include "ShaderProgram.h"
#include "NativeInterface/NativeShaderProgram.h"
#include <assert.h>

namespace Graphics
{
    ShaderProgram::ShaderProgram(std::unique_ptr<NativeShaderProgram> nativeShaderProgram)
    {
        mNativeShaderProgram = std::move(nativeShaderProgram);
        assert(mNativeShaderProgram != nullptr);
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