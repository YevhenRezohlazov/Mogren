#include "ShaderParameterSetterFactory.h"

#include "ScalarShaderParameterSetter.h"
#include "VectorShaderParameterSetter.h"
#include "MatrixShaderParameterSetter.h"
#include "NativeInterface/NativeShaderParameterSetter.h"
#include <assert.h>

namespace Graphics
{
    std::unique_ptr<ShaderParameterSetter> ShaderParameterSetterFactory::create(
        ShaderParameterType paramType, std::unique_ptr<NativeShaderParameterSetter> nativeSetter)
    {
        std::unique_ptr<ShaderParameterSetter> setter;

        if (paramType.getArraySize() != -1) // array
        {
            assert("Not supported");
        }
        else
        {
            if (paramType.getMDimension() != -1) // matrix
            {
                if (paramType.getNDimension() == 2 && paramType.getMDimension() == 2) setter = std::make_unique<Matrix2x2ShaderParameterSetter>(std::move(nativeSetter));
                else if (paramType.getNDimension() == 3 && paramType.getMDimension() == 3) setter = std::make_unique<Matrix3x3ShaderParameterSetter>(std::move(nativeSetter));
                else if (paramType.getNDimension() == 4 && paramType.getMDimension() == 4) setter = std::make_unique<Matrix4x4ShaderParameterSetter>(std::move(nativeSetter));
            }
            else if (paramType.getNDimension() != -1) // vector
            {
                if (paramType.getNDimension() == 2 && paramType.getBaseType() == BaseShaderParameterType::Boolean) setter = std::make_unique<VectorShaderParameterSetter<Math::Vector2DB>>(std::move(nativeSetter));
                else if (paramType.getNDimension() == 2 && paramType.getBaseType() == BaseShaderParameterType::Float) setter = std::make_unique<VectorShaderParameterSetter<Math::Vector2DF>>(std::move(nativeSetter));
                else if (paramType.getNDimension() == 2 && paramType.getBaseType() == BaseShaderParameterType::Integer) setter = std::make_unique<VectorShaderParameterSetter<Math::Vector2DI>>(std::move(nativeSetter));
                else if (paramType.getNDimension() == 3 && paramType.getBaseType() == BaseShaderParameterType::Boolean) setter = std::make_unique<VectorShaderParameterSetter<Math::Vector3DB>>(std::move(nativeSetter));
                else if (paramType.getNDimension() == 3 && paramType.getBaseType() == BaseShaderParameterType::Float) setter = std::make_unique<VectorShaderParameterSetter<Math::Vector3DF>>(std::move(nativeSetter));
                else if (paramType.getNDimension() == 3 && paramType.getBaseType() == BaseShaderParameterType::Integer) setter = std::make_unique<VectorShaderParameterSetter<Math::Vector3DI>>(std::move(nativeSetter));
                else if (paramType.getNDimension() == 4 && paramType.getBaseType() == BaseShaderParameterType::Boolean) setter = std::make_unique<VectorShaderParameterSetter<Math::Vector4DB>>(std::move(nativeSetter));
                else if (paramType.getNDimension() == 4 && paramType.getBaseType() == BaseShaderParameterType::Float) setter = std::make_unique<VectorShaderParameterSetter<Math::Vector4DF>>(std::move(nativeSetter));
                else if (paramType.getNDimension() == 4 && paramType.getBaseType() == BaseShaderParameterType::Integer) setter = std::make_unique<VectorShaderParameterSetter<Math::Vector4DI>>(std::move(nativeSetter));
            }
            else // scalar
            {
                if (paramType.getBaseType() == BaseShaderParameterType::Boolean) setter = std::make_unique<BoolShaderParameterSetter>(std::move(nativeSetter));
                else if (paramType.getBaseType() == BaseShaderParameterType::Float) setter = std::make_unique<FloatShaderParameterSetter>(std::move(nativeSetter));
                else if (paramType.getBaseType() == BaseShaderParameterType::Integer) setter = std::make_unique<IntShaderParameterSetter>(std::move(nativeSetter));
                else if (paramType.getBaseType() == BaseShaderParameterType::Texture) setter = std::make_unique<TextureShaderParameterSetter>(std::move(nativeSetter));
            }
        }

        return setter;
    }
}