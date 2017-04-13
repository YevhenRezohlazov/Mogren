#include "ShaderProgramImpl.h"
#include "ShaderParameterSetImpl.h"

#include <Mogren/Framework/App/App.h>
#include <Mogren/Framework/Logging/Logger.h>
#include <Mogren/Framework/IO/BinaryReader.h>

#include <functional>
#include <unordered_map>
#include <assert.h>

namespace Graphics
{
    namespace
    {
        std::string readASCIIString(IO::BinaryReader &reader)
        {
            auto len = reader.read<uint32_t>();
            return reader.readString(len);
        }
    }

    ShaderProgramImpl::ShaderProgramImpl(IO::InputStream & shaderInputStream)
    {
        IO::BinaryReader reader(shaderInputStream);
        readASCIIString(reader); // skip HLSL vertex func name
        readASCIIString(reader); // skip HLSL pixel func name
        readASCIIString(reader); // skip HLSL code

        mVertexShader = readASCIIString(reader);
        mFragmentShader = readASCIIString(reader);
    }

    const GLProgram& ShaderProgramImpl::getGLProgram() const
    {
        return mGLProgram;
    }

    std::unique_ptr<NativeShaderParameterSet> ShaderProgramImpl::createParameterSet() const
    {
        return std::make_unique<ShaderParameterSetImpl>(*this);
    }

    void ShaderProgramImpl::finalize()
    {
        auto initialized = mGLProgram.init(mVertexShader, mFragmentShader);
        mVertexShader.clear();
        mVertexShader.shrink_to_fit();
        mFragmentShader.clear();
        mFragmentShader.shrink_to_fit();

        auto attributes = mGLProgram.getVertexAttributes();
        assert(initialized);

        for (int i = 0; i < VertexAttributeUsageCount; ++i)
        {
            for (int j = 0; j < VertexAttributeUsageIndexCount; ++j)
            {
                mAttributeMatrix[i][j] = -1;
            }
        }

        std::string prefix("xlat_attrib_");

        for (auto attrib : attributes)
        {
            bool unknownAttribute = false;
            auto attribName = attrib.first;
            std::string usageName;
            int usageIndex = -1;

            if (attribName.find(prefix) == 0)
            {
                auto nameWithoutPrefix = attribName.substr(prefix.length());

                if (nameWithoutPrefix.length() < 2)
                    unknownAttribute = true;
                else
                {
                    auto lastChar = nameWithoutPrefix[nameWithoutPrefix.length() - 1];
                    if (lastChar < L'0' || lastChar > '9')
                        unknownAttribute = true;
                    else
                    {
                        auto prevChar = nameWithoutPrefix[nameWithoutPrefix.length() - 2];
                        if (prevChar < L'0' || prevChar > '9')
                        {
                            usageIndex = lastChar - L'0';
                            usageName = nameWithoutPrefix.substr(0, nameWithoutPrefix.length() - 1);
                        }
                        else
                        {
                            usageIndex = (prevChar - L'0') * 10 + (lastChar - L'0');
                            usageName = nameWithoutPrefix.substr(0, nameWithoutPrefix.length() - 2);
                        }
                    }
                }
            }
            else
                unknownAttribute = true;

            if (!unknownAttribute)
            {
                if (usageIndex >= VertexAttributeUsageIndexCount)
                {
                    Logging::Logger::writeWarning("Attribute usage should be in range 0..15: %s", attrib.first.c_str());
                }

                bool found = false;
                for (int i = 0; i < VertexAttributeUsageCount; ++i)
                {
                    if (VertexAttributeUsageNames[i] == usageName)
                    {
                        mAttributeMatrix[i][usageIndex] = attrib.second;
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    Logging::Logger::writeWarning("Unrecognized shader attribute usage: %s", attrib.first.c_str());
                }
            }
            else
            {
                Logging::Logger::writeWarning("Unrecognized shader attribute: %s", attrib.first.c_str());
            }
        }
    }

    const std::string ShaderProgramImpl::VertexAttributeUsageNames[VertexAttributeUsageCount] =
    {
        "POSITION",
        "TEXCOORD",
        "NORMAL",
        "TANGENT",
        "BINORMAL",
        "COLOR",
        "BLENDINDICES",
        "BLENDWEIGHT",
    };

    const GLint ShaderProgramImpl::getAttributeLocation(Graphics::VertexAttributeUsage attribUsage, int attribUsageIndex) const
    {
        return mAttributeMatrix[static_cast<int>(attribUsage)][attribUsageIndex];
    }
}