#include "ShaderProgramLoader.h"
#include "ShaderProgram.h"

#include "NativeInterface/NativeGraphicsInterface.h"
#include "NativeInterface/NativeShaderProgram.h"

#include <Mogren/Framework/IO/InputStream.h>
#include <Mogren/Framework/IO/BinaryReader.h>
#include <Mogren/Framework/Common/ImplementationProvider.h>
#include <Mogren/Framework/Logging/FunctionLoggingGuard.h>

#include <assert.h>
#include <unordered_map>

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

    ShaderProgramLoader::ShaderProgramLoader()
    {
    }

    const std::vector<std::string> ShaderProgramLoader::getResourceExtensions() const
    {
        return { "ms" };
    }

    std::unique_ptr<ResourceManagement::Resource> ShaderProgramLoader::loadResource(IO::InputStream & stream) const
    {
        DECLARE_FUNCTION_LOGGING_GUARD();
        
        IO::BinaryReader reader(stream);

        if (reader.read<uint32_t>() != FileSignature)
        {
            assert(false && "Given resource is not a compiled Mogren shader.");
        }

        std::unordered_map<std::string, std::string> options;
        auto optionsCount = reader.read<uint32_t>();

        for (uint32_t i = 0; i < optionsCount; ++i)
        {
            const auto &key = readASCIIString(reader);
            auto value = readASCIIString(reader);

            options[key] = std::move(value);
        }

        std::unordered_map<std::string, ShaderParameterType> uniforms;
        auto uniformsCount = reader.read<uint32_t>();

        for (uint32_t i = 0; i < uniformsCount; ++i)
        {
            auto name = readASCIIString(reader);
            ShaderParameterType type = reader.read<ShaderParameterType>();
            uniforms.insert(std::make_pair(std::move(name), type));
        }

        auto nativeProgram = Common::getImpl<NativeGraphicsInterface>().compileShaderProgram(
            stream, stream.getLength() - stream.getPosition());
        assert(nativeProgram);
        return std::make_unique<ShaderProgram>(options, uniforms, std::move(nativeProgram));
    }
}