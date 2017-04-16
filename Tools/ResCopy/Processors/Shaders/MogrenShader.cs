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

        public MogrenShader(string glslVertexCode, string glslFragmentCode)
        {
            GLSLVertexCode = glslVertexCode;
            GLSLFragmentCode = glslFragmentCode;
        }

        public string GLSLVertexCode { get; private set; }

        public string GLSLFragmentCode { get; private set; }
        
        public void Save(string path)
        {
            using (var writer = new BinaryWriter(new FileStream(path, FileMode.Create)))
            {
                writer.Write(FileSignature);
                writer.WriteASCIIString(GLSLVertexCode);
                writer.WriteASCIIString(GLSLFragmentCode);
            }
        }
    }
}