using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace ResCopy
{
    public class ShaderProcessor : SpecialProcessor
    {
        private const string ShaderDelimeter = "-----";
        private const string IncludePrefix = "#include ";

        public ShaderProcessor()
            : base(".ms")
        {
        }

        public override string Process(string srcResPath, string destDirPath)
        {
            Console.WriteLine("Processing as Mogren shader...");

            var srcLines = LoadAndPreprocessSource(srcResPath);

            var splitIndex = srcLines.IndexOf(ShaderDelimeter);

            if (splitIndex == -1)
            {
                throw new Exception("Vertex or fragment shaders must be splitted by '-----'.");
            }

            var glslVertexCode = srcLines.Take(splitIndex).Aggregate((a, b) => a + "\n" + b);
            var glslFragmentCode = srcLines.Skip(splitIndex + 1).Aggregate((a, b) => a + "\n" + b);

            if (glslVertexCode.Trim().Length == 0 || glslFragmentCode.Trim().Length == 0)
            {
                throw new Exception("Vertex or fragment shader code is not available.");
            }

            //glslVertexCode = string.Format("#line 1 {0}\n", Path.GetFileName(srcResPath)) + glslVertexCode;

            glslFragmentCode =  @"#ifdef GL_ES
#ifdef GL_FRAGMENT_PRECISION_HIGH
   // Default precision
   precision highp float;
#else
   precision mediump float;
#endif
#endif
" + glslFragmentCode;
            
            var shader = new MogrenShader(glslVertexCode, glslFragmentCode);
            var outputFileName = Path.Combine(destDirPath, Path.GetFileName(srcResPath));
            shader.Save(outputFileName);
            return outputFileName;
        }

        /// <summary>
        /// Loads and preprocesses given source file
        /// </summary>
        /// <param name="path">Source file path</param>
        /// <returns>List of file lines</returns>
        private static List<string> LoadAndPreprocessSource(string path)
        {
            var srcDir = Path.GetDirectoryName(path);

            var srcLines = File.ReadAllLines(path);
            var resSrcLines = new List<string>();

            for (int i = 0; i < srcLines.Length; ++i)
            {
                var line = srcLines[i];

                if (line.StartsWith(IncludePrefix))
                {
                    var includeFileName = line.Remove(0, IncludePrefix.Length).Trim(' ', '"');
                    var includeFilePath = Path.Combine(srcDir, includeFileName);

                    if (!File.Exists(includeFilePath))
                    {
                        throw new Exception(string.Format("Can't find included file: {0}", includeFilePath));
                    }

                    var includeFileSrc = LoadAndPreprocessSource(includeFilePath);

                    //resSrcLines.Add(string.Format("#line 1 \"{1}\"", Path.GetFileName(includeFilePath)));
                    resSrcLines.AddRange(includeFileSrc);
                    //resSrcLines.Add(string.Format("#line {0} \"{1}\"", i + 1, Path.GetFileName(path)));
                }
                else
                {
                    resSrcLines.Add(line.Trim());
                }
            }

            return resSrcLines;
        }
    }
}