#include "ShaderParameterSetImpl.h"
#include "ShaderParameterSetterImpl.h"
#include "TextureImpl.h"
#include <Mogren/Framework/Graphics/NativeInterface/NativeTextureShaderParameterData.h>
#include <assert.h>

namespace Graphics
{
    ShaderParameterSetImpl::ShaderParameterSetImpl(const ShaderProgramImpl & shaderProgramImpl)
        : mShaderProgramImpl(shaderProgramImpl)
    {
    }

    std::unique_ptr<NativeShaderParameterSetter> ShaderParameterSetImpl::createParameterSetter(
        const std::string & name, ShaderParameterType type)
    {
        auto result = std::make_unique<ShaderParameterSetterWrapper>(mShaderProgramImpl, name, type);
        mSetters.push_back(result->mImpl);
        return result;
    }

    void ShaderParameterSetImpl::applyUniforms() const
    {
        int currentTextureIndex = 0;

        const int settersCount = mSetters.size();

        for (int i = 0; i < settersCount; ++i)
        {
            auto setter = mSetters[i].get();

            switch (setter->mUniformSetterType)
            {
            case UniformSetterType::Float1Array:
                glUniform1fv(setter->mUniformLocation, setter->mDataSize / sizeof(float), setter->mDataF);
                break;
            case UniformSetterType::Float2Array:
                glUniform2fv(setter->mUniformLocation, setter->mDataSize / (sizeof(float) * 2), setter->mDataF);
                break;
            case UniformSetterType::Float3Array:
                glUniform3fv(setter->mUniformLocation, setter->mDataSize / (sizeof(float) * 3), setter->mDataF);
                break;
            case UniformSetterType::Float4Array:
                glUniform4fv(setter->mUniformLocation, setter->mDataSize / (sizeof(float) * 4), setter->mDataF);
                break;

            case UniformSetterType::Int1Array:
                glUniform1iv(setter->mUniformLocation, setter->mDataSize / sizeof(float), setter->mDataI);
                break;
            case UniformSetterType::Int2Array:
                glUniform2iv(setter->mUniformLocation, setter->mDataSize / (sizeof(float) * 2), setter->mDataI);
                break;
            case UniformSetterType::Int3Array:
                glUniform3iv(setter->mUniformLocation, setter->mDataSize / (sizeof(float) * 3), setter->mDataI);
                break;
            case UniformSetterType::Int4Array:
                glUniform4iv(setter->mUniformLocation, setter->mDataSize / (sizeof(float) * 4), setter->mDataI);
                break;

            case UniformSetterType::Matrix2x2: glUniformMatrix2fv(setter->mUniformLocation, setter->mDataSize / (sizeof(float) * 2 * 2), GL_FALSE, setter->mDataF); break;
            case UniformSetterType::Matrix3x3: glUniformMatrix3fv(setter->mUniformLocation, setter->mDataSize / (sizeof(float) * 3 * 3), GL_FALSE, setter->mDataF); break;
            case UniformSetterType::Matrix4x4: glUniformMatrix4fv(setter->mUniformLocation, setter->mDataSize / (sizeof(float) * 4 * 4), GL_FALSE, setter->mDataF); break;

            case UniformSetterType::TextureArray:
                {
                    uint32_t texturesCount = setter->mDataSize / sizeof(NativeTextureShaderParameterData);

                    assert(texturesCount <= 8);

                    int32_t values[8];

                    for (uint32_t ti = 0; ti < texturesCount; ++ti)
                    {
                        auto texture = static_cast<const TextureImpl*>(setter->mDataT[ti].mNativeTexture);

                        if (texture)
                        {
                            glActiveTexture(GL_TEXTURE0 + currentTextureIndex);
                            texture->getGLTexture().bind();
                            texture->getGLTexture().setParameters(
                                setter->mDataT[ti].mMinFilter,
                                setter->mDataT[ti].mMagFilter,
                                setter->mDataT[ti].mWrapModeU,
                                setter->mDataT[ti].mWrapModeV);

                            values[ti] = currentTextureIndex;
                            currentTextureIndex += 1;
                        }
                    }

                    glUniform1iv(setter->mUniformLocation, texturesCount, values);
                }

            default: break;
            }
        }
    }
}