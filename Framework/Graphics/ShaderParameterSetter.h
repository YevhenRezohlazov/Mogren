#pragma once

#include "NativeInterface/NativeShaderParameterSetter.h"
#include <memory>

namespace Graphics
{
    class NativeTextureShaderParameterData;

    ///
    /// Base class for shader parameter setters
    ///
    class ShaderParameterSetter
    {
    protected:
        ///
        /// Initializes a new instance of the ShaderParameter class.
        ///
        /// \param nativeParameter The native shader parameter.
        explicit ShaderParameterSetter(std::unique_ptr<NativeShaderParameterSetter> nativeParameterSetter);

    public:
        ///
        /// Gets the native shader parameter.
        ///
        NativeShaderParameterSetter& getNativeParameter();

        virtual ~ShaderParameterSetter();

    protected:
        void setValues(const bool *bools);

        void setValues(const float *floats);

        void setValues(const int32_t *ints);

        void setValues(const NativeTextureShaderParameterData *textures);

    protected:
        std::unique_ptr<NativeShaderParameterSetter> mNativeParameterSetter;
    };
}

