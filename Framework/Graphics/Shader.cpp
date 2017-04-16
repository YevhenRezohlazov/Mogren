#include "Shader.h"
#include "ShaderProgram.h"
#include "NativeInterface/NativeShaderProgram.h"
#include "NativeInterface/NativeShaderParameterSet.h"
#include "ShaderParameterSetterFactory.h"
#include <assert.h>

namespace Graphics
{
    Shader::Shader(std::shared_ptr<ShaderProgram> shaderProgram)
        : mWorldTransformParameter(nullptr)
        , mViewTransformParameter(nullptr)
        , mProjectionTransformParameter(nullptr)
        , mWorldViewTransformParameter(nullptr)
        , mViewProjectionTransformParameter(nullptr)
        , mWorldViewProjectionTransformParameter(nullptr)
    {
        mShaderProgram = std::move(shaderProgram);
        mShaderParameterSet = mShaderProgram->getNativeShaderProgram().createParameterSet();

        mWorldTransformParameter = getParameterSetter<Matrix4x4ShaderParameterSetter>("uWorld");
        mViewTransformParameter = getParameterSetter<Matrix4x4ShaderParameterSetter>("uView");
        mProjectionTransformParameter = getParameterSetter<Matrix4x4ShaderParameterSetter>("uProjection");
        mWorldViewTransformParameter = getParameterSetter<Matrix4x4ShaderParameterSetter>("uWorldView");
        mViewProjectionTransformParameter = getParameterSetter<Matrix4x4ShaderParameterSetter>("uViewProjection");
        mWorldViewProjectionTransformParameter = getParameterSetter<Matrix4x4ShaderParameterSetter>("uWorldViewProjection");
    }

    std::shared_ptr<const ShaderProgram> Shader::getProgram() const
    {
        return mShaderProgram;
    }

    std::shared_ptr<ShaderProgram> Shader::getProgram()
    {
        return mShaderProgram;
    }

    Matrix4x4ShaderParameterSetter* Shader::getWorldTransformParameter() const
    {
        return mWorldTransformParameter;
    }

    Matrix4x4ShaderParameterSetter* Shader::getViewTransformParameter() const
    {
        return mViewTransformParameter;
    }

    Matrix4x4ShaderParameterSetter* Shader::getProjectionTransformParameter() const
    {
        return mProjectionTransformParameter;
    }

    Matrix4x4ShaderParameterSetter* Shader::getWorldViewTransformParameter() const
    {
        return mWorldViewTransformParameter;
    }

    Matrix4x4ShaderParameterSetter* Shader::getViewProjectionTransformParameter() const
    {
        return mViewProjectionTransformParameter;
    }

    Matrix4x4ShaderParameterSetter* Shader::getWorldViewProjectionTransformParameter() const
    {
        return mWorldViewProjectionTransformParameter;
    }

    ShaderParameterSetter* Shader::getParameterSetter(const std::string &name, const ShaderParameterType & type) const
    {
        auto param = mParameterSetters.find(name);

        if (param == mParameterSetters.end())
        {
            auto nativeSetter = mShaderParameterSet->createParameterSetter(name, type);
            mParameterSetters[name] = nativeSetter ? ShaderParameterSetterFactory::create(type, std::move(nativeSetter)) : nullptr;
            param = mParameterSetters.find(name);
        }

        return param->second.get();
    }

    const NativeShaderParameterSet & Shader::getNativeParameterSet() const
    {
        return *mShaderParameterSet;
    }

    Shader::~Shader() = default;
}