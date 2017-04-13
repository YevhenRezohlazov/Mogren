#pragma once

#include "MatrixShaderParameterSetter.h"

#include <memory>
#include <unordered_map>
#include <string>

namespace Graphics
{
    class ShaderParameterSetter;
    class ShaderProgram;
    class NativeShaderParameterSet;

    ///
    /// Shader for visualizing visual scene items
    ///
    class Shader
    {
    protected:
        ///
        /// Initializes a new instance of a Shader class.
        ///
        /// \param shaderProgram The shader program instance.
        explicit Shader(std::shared_ptr<ShaderProgram> shaderProgram);

    public:
        ///
        /// Gets the shader program instance.
        ///
        std::shared_ptr<const ShaderProgram> getProgram() const;
        std::shared_ptr<ShaderProgram> getProgram();

        ///
        /// Gets the shader parameter which will be set (if not null) with world transformation value (from scene item transformation).
        ///
        Matrix4x4ShaderParameterSetter* getWorldTransformParameter() const;

        ///
        /// Gets the shader parameter which will be set (if not null) with camera view transformation value.
        ///
        Matrix4x4ShaderParameterSetter* getViewTransformParameter() const;

        ///
        /// Gets the shader parameter which will be set (if not null) with camera projection transformation value.
        ///
        Matrix4x4ShaderParameterSetter* getProjectionTransformParameter() const;

        ///
        /// Gets the shader parameter which will be set (if not null) with multiplied world and view transformation matrices.
        ///
        Matrix4x4ShaderParameterSetter* getWorldViewTransformParameter() const;

        ///
        /// Gets the shader parameter which will be set (if not null) with multiplied view and projection transformation matrices.
        ///
        Matrix4x4ShaderParameterSetter* getViewProjectionTransformParameter() const;

        ///
        /// Gets the shader parameter which will be set (if not null) with multiplied world, view and projection transformation matrices.
        ///
        Matrix4x4ShaderParameterSetter* getWorldViewProjectionTransformParameter() const;

        const NativeShaderParameterSet& getNativeParameterSet() const;

        ~Shader();

    protected:
        ///
        /// Sets the shader parameter which will be set (if not null) with world transformation value (from scene item transformation).
        ///
        void setWorldTransformParameterName(const std::string & name);

        ///
        /// Sets the shader parameter which will be set (if not null) with camera view transformation value.
        ///
        void setViewTransformParameterName(const std::string & name);

        ///
        /// Sets the shader parameter which will be set (if not null) with camera projection transformation value.
        ///
        void setProjectionTransformParameterName(const std::string & name);

        ///
        /// Sets the shader parameter which will be set (if not null) with multiplied world and view transformation matrices.
        ///
        void setWorldViewTransformParameterName(const std::string & name);

        ///
        /// Sets the shader parameter which will be set (if not null) with multiplied view and projection transformation matrices.
        ///
        void setViewProjectionTransformParameterName(const std::string & name);

        ///
        /// Sets the shader parameter which will be set (if not null) with multiplied world, view and projection transformation matrices.
        ///
        void setWorldViewProjectionTransformParameterName(const std::string & name);

        ///
        /// Gets the shader parameter with specified name.
        /// InvalidOperationException is thrown when the parameter with such a name hasn't been found.
        ///
        /// \param name The parameter name.
        /// \returns ShaderParameter instance.
        ShaderParameterSetter* getParameterSetter(const std::string &name) const;

        ///
        /// Gets the shader parameter with specified name.
        ///
        /// \param name The parameter name.
        /// \returns ShaderParameter instance.
        template<typename TSetter>
        TSetter* getParameterSetter(const std::string &name) const;

    private:
        ///
        /// The shader program instance.
        ///
        std::shared_ptr<ShaderProgram> mShaderProgram;

        ///
        /// The shader parameter set instance.
        ///
        std::unique_ptr<NativeShaderParameterSet> mShaderParameterSet;

        ///
        /// The shader parameter setters map (name -> parameter)
        ///
        std::unordered_map<std::string, std::unique_ptr<ShaderParameterSetter>> mParameterSetters;

        ///
        /// The shader parameter which will be set (if not null) with world transformation value (from scene item transformation).
        ///
        Matrix4x4ShaderParameterSetter* mWorldTransformParameter;

        ///
        /// The shader parameter which will be set (if not null) with camera view transformation value.
        ///
        Matrix4x4ShaderParameterSetter* mViewTransformParameter;

        ///
        /// The shader parameter which will be set (if not null) with camera projection transformation value.
        ///
        Matrix4x4ShaderParameterSetter* mProjectionTransformParameter;

        ///
        /// The shader parameter which will be set (if not null) with multiplied world and view transformation matrices.
        ///
        Matrix4x4ShaderParameterSetter* mWorldViewTransformParameter;

        ///
        /// The shader parameter which will be set (if not null) with multiplied view and projection transformation matrices.
        ///
        Matrix4x4ShaderParameterSetter* mViewProjectionTransformParameter;

        ///
        /// The shader parameter which will be set (if not null) with multiplied world, view and projection transformation matrices.
        ///
        Matrix4x4ShaderParameterSetter* mWorldViewProjectionTransformParameter;

    };

    template<typename TSetter>
    inline TSetter * Shader::getParameterSetter(const std::string & name) const
    {
        return dynamic_cast<TSetter*>(getParameterSetter(name));
    }
}

