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

        if (!initialized)
        {
            Logging::Logger::writeError("Vertex shader:\n%s", mVertexShader.c_str());
            Logging::Logger::writeError("Fragment shader:\n%s", mFragmentShader.c_str());
        }

        assert(initialized);
        mVertexShader.clear();
        mVertexShader.shrink_to_fit();
        mFragmentShader.clear();
        mFragmentShader.shrink_to_fit();

        mAttributesMap = mGLProgram.getVertexAttributes();
    }

    GLint ShaderProgramImpl::getAttributeLocation(const std::string & attribName) const
    {
        auto result = mAttributesMap.find(attribName);
        return result == mAttributesMap.end() ? -1 : result->second;
    }
}