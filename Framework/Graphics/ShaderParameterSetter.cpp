#include "ShaderParameterSetter.h"
#include "NativeInterface/NativeShaderParameterSetter.h"
#include <assert.h>

namespace Graphics
{
    ShaderParameterSetter::ShaderParameterSetter(std::unique_ptr<NativeShaderParameterSetter> nativeParameterSetter)
        : mNativeParameterSetter(std::move(nativeParameterSetter))
    {
        assert(mNativeParameterSetter != nullptr);
    }
    
    NativeShaderParameterSetter & ShaderParameterSetter::getNativeParameter()
    {
        return *mNativeParameterSetter;
    }

    ShaderParameterSetter::~ShaderParameterSetter() = default;

    void ShaderParameterSetter::setValues(const bool *bools)
    {
        mNativeParameterSetter->setValues(bools);
    }

    void ShaderParameterSetter::setValues(const float *floats)
    {
        mNativeParameterSetter->setValues(floats);
    }

    void ShaderParameterSetter::setValues(const int32_t *ints)
    {
        mNativeParameterSetter->setValues(ints);
    }

    void ShaderParameterSetter::setValues(const NativeTextureShaderParameterData *textures)
    {
        mNativeParameterSetter->setValues(textures);
    }
}