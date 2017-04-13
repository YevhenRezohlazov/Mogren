using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ResCopy
{
    internal class MogrenShader
    {
        private const uint FileSignature = 0x5FA6B220;

        public MogrenShader(Dictionary<string, string> options, Dictionary<string, UniformType> uniforms, string glslVertexCode, string glslFragmentCode, string hlslCode)
        {
            Options = options;
            Uniforms = uniforms;
            GLSLVertexCode = glslVertexCode;
            GLSLFragmentCode = glslFragmentCode;
            HLSLCode = hlslCode;
        }

        public Dictionary<string, string> Options { get; private set; }

        public Dictionary<string, UniformType> Uniforms { get; private set; }

        public string GLSLVertexCode { get; private set; }

        public string GLSLFragmentCode { get; private set; }

        public string HLSLCode { get; private set; }

        public void Save(string path)
        {
            using (var writer = new BinaryWriter(new FileStream(path, FileMode.Create)))
            {
                writer.Write(FileSignature);

                // write options
                writer.Write(Options.Count);

                foreach (var option in Options)
                {
                    writer.WriteASCIIString(option.Key); // name
                    writer.WriteASCIIString(option.Value); // value
                }

                writer.Write(Uniforms.Count);

                foreach (var uniform in Uniforms)
                {
                    writer.WriteASCIIString(uniform.Key); // name
                    uniform.Value.WriteTo(writer); // type
                }

                // HLSL data
                writer.WriteASCIIString(Options["vertex_func"]);
                writer.WriteASCIIString(Options["pixel_func"]);
                writer.WriteASCIIString(HLSLCode);

                // GLSL data
                writer.WriteASCIIString(GLSLVertexCode);
                writer.WriteASCIIString(GLSLFragmentCode);
            }
        }
    }
}