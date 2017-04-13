#pragma once

#include <stdint.h>

namespace Graphics
{
    class NativeTextureShaderParameterData;

    ///
    /// Provides access to shader parameter value.
    ///
    class NativeShaderParameterSetter
    {
    public:
        ///
        /// Sets the boolean parameter values.
        ///
        /// \param bools New parameter values.
        virtual void setValues(const bool *bools) = 0;

        ///
        /// Sets the float parameter values.
        ///
        /// \param floats New parameter values.
        virtual void setValues(const float *floats) = 0;

        ///
        /// Sets the integer parameter values.
        ///
        /// \param ints New parameter values.
        virtual void setValues(const int32_t *ints) = 0;

        ///
        /// Sets the texture parameter values.
        ///
        /// \param textures New parameter values.
        virtual void setValues(const NativeTextureShaderParameterData *textures) = 0;

        virtual ~NativeShaderParameterSetter() = default;
    };
}

