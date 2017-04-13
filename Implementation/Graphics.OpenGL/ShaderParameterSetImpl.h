#pragma once

#include <Mogren/Framework/Graphics/NativeInterface/NativeShaderParameterSet.h>
#include <memory>
#include <vector>

namespace Graphics
{
    class ShaderProgramImpl;
    class ShaderParameterSetterImpl;

    class ShaderParameterSetImpl : public NativeShaderParameterSet
    {
    public:
        explicit ShaderParameterSetImpl(const ShaderProgramImpl &shaderProgramImpl);

        virtual std::unique_ptr<NativeShaderParameterSetter> createParameterSetter(
            const std::string& name, ShaderParameterType type) override;

        // sets all OpenGL uniforms set by parameter setters
        void applyUniforms() const;

    private:
        const ShaderProgramImpl& mShaderProgramImpl;
        std::vector<std::shared_ptr<ShaderParameterSetterImpl>> mSetters;
    };
}

