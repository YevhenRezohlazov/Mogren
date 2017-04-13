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
        private const string SetPrefix = "#set ";
        private const string IncludePrefix = "#include ";

        public ShaderProcessor()
            : base(".ms")
        {
        }

        public override string Process(string srcResPath, string destDirPath)
        {
            Console.WriteLine("Processing as Mogren shader...");

            var srcLines = LoadAndPreprocessSource(srcResPath);

            var shaderOptions = new Dictionary<string, string>();

            for (int i = srcLines.Count - 1; i >= 0; --i)
            {
                var line = srcLines[i];

                if (line.StartsWith(SetPrefix))
                {
                    srcLines[i] = string.Empty;

                    line = line.Substring(SetPrefix.Length);

                    var parts = line.Split(new[] { ' ' }, 2, StringSplitOptions.RemoveEmptyEntries);

                    if (parts.Length != 2)
                    {
                        throw new Exception(string.Format("Wrong #set declaration (line {0}): {1}\nRight syntax is #set option value", i, line));
                    }

                    shaderOptions.Add(parts[0].Trim(), parts[1].Trim());

                    Console.WriteLine("Set option \"{0}\" to value \"{1}\"", parts[0], parts[1]);
                }
            }

            if (!shaderOptions.ContainsKey("vertex_func") || !shaderOptions.ContainsKey("pixel_func"))
            {
                Console.WriteLine("Shader doesn't specify vertex and pixel shader functions. Shader is ignored (but may be included into other shaders)."
                    + "Vertex and pixel shader functions can be specified by setting "
                    + "vertex_func and pixel_func options, "
                    + "for example:\n#set vertex_func VS_Main\n#set pixel_func PS_Main\n");
                return null;
            }

            var vertexFunc = shaderOptions["vertex_func"];
            var pixelFunc = shaderOptions["pixel_func"];

            if (!Regex.Match(vertexFunc, @"^[a-zA-Z_][a-zA-Z0-9_]*$").Success)
            {
                throw new Exception(string.Format("\"{0}\" is not a valid identifier name.", vertexFunc));
            }

            if (!Regex.Match(pixelFunc, @"^[a-zA-Z_][a-zA-Z0-9_]*$").Success)
            {
                throw new Exception(string.Format("\"{0}\" is not a valid identifier name.", pixelFunc));
            }

            var hlslCode = string.Join("\n", srcLines);

            var hlslFileName = Path.GetTempFileName();
            var glslVertexFileName = Path.GetTempFileName();
            var glslFragmentFileName = Path.GetTempFileName();
            var glslUniformsFileName = Path.GetTempFileName();
            File.WriteAllText(hlslFileName, hlslCode);

            var hlsl2glslPath = Path.Combine(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location), "HLSL2GLSL.exe");
            var attribConfigPath = Path.Combine(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location), "attrib.cfg");

            var processStartInfo = new ProcessStartInfo(
                hlsl2glslPath,
                string.Format(
                    "-f {4} -v {5} -ov \"{1}\" -of \"{2}\" -ou \"{6}\" -a \"{3}\" -u \"{0}\"",
                    hlslFileName,
                    glslVertexFileName,
                    glslFragmentFileName,
                    attribConfigPath,
                    pixelFunc,
                    vertexFunc,
                    glslUniformsFileName));
            processStartInfo.UseShellExecute = false;

            var process = System.Diagnostics.Process.Start(processStartInfo);
            process.WaitForExit();

            if (process.ExitCode != 0)
            {
                throw new Exception("HLSL2GLSL returned non-zero status.");
            }

            var glslVertexCode = File.ReadAllText(glslVertexFileName);
            var glslFragmentCode = File.ReadAllText(glslFragmentFileName);

            // invert vertical texture coordinates
            {
                glslFragmentCode = Regex.Replace(
                    glslFragmentCode,
                    @"(texture2D\s*\(.*?,)((?:(?<C>\()|(?<-C>\)|)|[^\(\)])*)(?(C)(?!)|\))",
                    "$1 vec2(($2).x, 1.0 - ($2).y))");
            }

            glslFragmentCode = @"#ifdef GL_ES
#ifdef GL_FRAGMENT_PRECISION_HIGH
   // Default precision
   precision highp float;
#else
   precision mediump float;
#endif
#endif
" + glslFragmentCode;

            var uniformStrings = File.ReadAllLines(glslUniformsFileName);

            var uniforms = new Dictionary<string, UniformType>();

            foreach (var us in uniformStrings)
            {
                var parts = us.Split(' ');
                uniforms.Add(parts[1], new UniformType(parts[0]));
            }

            File.Delete(hlslFileName);
            File.Delete(glslVertexFileName);
            File.Delete(glslFragmentFileName);
            File.Delete(glslUniformsFileName);

            var shader = new MogrenShader(shaderOptions, uniforms, glslVertexCode, glslFragmentCode, hlslCode);
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

                    resSrcLines.Add(string.Format("#line {0} \"{1}\"", 0, Path.GetFileName(includeFilePath)));
                    resSrcLines.AddRange(includeFileSrc);
                    resSrcLines.Add(string.Format("#line {0} \"{1}\"", i, Path.GetFileName(path)));
                }
                else
                {
                    resSrcLines.Add(line);
                }
            }

            return resSrcLines;
        }
    }
}