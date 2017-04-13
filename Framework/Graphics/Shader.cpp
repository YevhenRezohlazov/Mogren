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

        for (auto param : mShaderProgram->getParameters())
        {
            auto paramName = param.first;
            auto paramType = param.second;

            auto nativeSetter = mShaderParameterSet->createParameterSetter(paramName, paramType);
            mParameterSetters[paramName] = ShaderParameterSetterFactory::create(paramType, std::move(nativeSetter));
        }
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

    void Shader::setWorldTransformParameterName(const std::string & name)
    {
        mWorldTransformParameter = dynamic_cast<Matrix4x4ShaderParameterSetter*>(mParameterSetters[name].get());
        assert(mWorldTransformParameter != nullptr);
    }

    Matrix4x4ShaderParameterSetter* Shader::getViewTransformParameter() const
    {
        return mViewTransformParameter;
    }

    void Shader::setViewTransformParameterName(const std::string & name)
    {
        mViewTransformParameter = dynamic_cast<Matrix4x4ShaderParameterSetter*>(mParameterSetters[name].get());
        assert(mViewTransformParameter != nullptr);
    }

    Matrix4x4ShaderParameterSetter* Shader::getProjectionTransformParameter() const
    {
        return mProjectionTransformParameter;
    }

    void Shader::setProjectionTransformParameterName(const std::string & name)
    {
        mProjectionTransformParameter = dynamic_cast<Matrix4x4ShaderParameterSetter*>(mParameterSetters[name].get());
        assert(mProjectionTransformParameter != nullptr);
    }

    Matrix4x4ShaderParameterSetter* Shader::getWorldViewTransformParameter() const
    {
        return mWorldViewTransformParameter;
    }

    void Shader::setWorldViewTransformParameterName(const std::string & name)
    {
        mWorldViewTransformParameter = dynamic_cast<Matrix4x4ShaderParameterSetter*>(mParameterSetters[name].get());
        assert(mWorldViewTransformParameter != nullptr);
    }

    Matrix4x4ShaderParameterSetter* Shader::getViewProjectionTransformParameter() const
    {
        return mViewProjectionTransformParameter;
    }

    void Shader::setViewProjectionTransformParameterName(const std::string & name)
    {
        mViewProjectionTransformParameter = dynamic_cast<Matrix4x4ShaderParameterSetter*>(mParameterSetters[name].get());
        assert(mViewProjectionTransformParameter != nullptr);
    }

    Matrix4x4ShaderParameterSetter* Shader::getWorldViewProjectionTransformParameter() const
    {
        return mWorldViewProjectionTransformParameter;
    }

    void Shader::setWorldViewProjectionTransformParameterName(const std::string & name)
    {
        mWorldViewProjectionTransformParameter = dynamic_cast<Matrix4x4ShaderParameterSetter*>(mParameterSetters[name].get());
        assert(mWorldViewProjectionTransformParameter != nullptr);
    }

    ShaderParameterSetter* Shader::getParameterSetter(const std::string &name) const
    {
        auto param = mParameterSetters.find(name);
        assert(param != mParameterSetters.end());
        return param->second.get();
    }
    const NativeShaderParameterSet & Shader::getNativeParameterSet() const
    {
        return *mShaderParameterSet;
    }
    Shader::~Shader() = default;
}