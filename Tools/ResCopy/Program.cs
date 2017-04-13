using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace ResCopy
{
    internal class Program
    {
        private static List<SpecialProcessor> _specialProcessors
            = new List<SpecialProcessor>
            {
                new ShaderProcessor(),
                new FontProcessor(),
                new ImageProcessor(),
                new StringsProcessor()
            };

        private static List<string> _ResFileNames = new List<string>();

        public static int Main(string[] args)
        {
            if (args.Length < 2)
            {
                Console.WriteLine(@"Usage: ResCopy path\to\src_dir path\to\dest\dir [[paths to additional resource processors]]");
                return 1;
            }

            var srcDir = args[0];
            var destDir = args[1];

            for (int i = 2; i < args.Length; ++i)
            {
                var processorAssemblyPath = args[i];

                try
                {
                    var processorAssembly = Assembly.LoadFrom(processorAssemblyPath);
                    var processors = processorAssembly.GetTypes().Where(t => typeof(SpecialProcessor).IsAssignableFrom(t)).Select(t => (SpecialProcessor)Activator.CreateInstance(t));

                    foreach (var processor in processors)
                    {
                        _specialProcessors.Add(processor);
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine("Can't create processor from {0}: {1}", processorAssemblyPath, e.Message);
                    return 1;
                }
            }

            if (!Directory.Exists(srcDir))
            {
                Console.WriteLine(@"Source directory doesn't exist.");
                return 1;
            }

#if !DEBUG
            try
            {
#endif
                if (!Directory.Exists(destDir))
                {
                    Directory.CreateDirectory(destDir);
                }

                ProcessDirectory(srcDir, destDir);

                var fullDestDirPath = Path.GetFullPath(destDir) + "\\";

                var resListFileName = Path.Combine(destDir, "ResList.bin");

                using (var writer = new BinaryWriter(new FileStream(resListFileName, FileMode.Create)))
                {
                    // 4 bytes - resource count
                    writer.Write(_ResFileNames.Where(fn => !string.IsNullOrEmpty(fn)).Count());

                    foreach (var resFileName in _ResFileNames.Where(fn => !string.IsNullOrEmpty(fn)))
                    {
                        var fullPath = Path.GetFullPath(resFileName);
                        var relPath = fullPath.Remove(0, fullDestDirPath.Length).Replace('\\', '/');
                        var pathBytes = Encoding.UTF8.GetBytes(relPath);

                        // 4 bytes - res path length
                        writer.Write(pathBytes.Length);

                        // N bytes - res path
                        writer.Write(pathBytes);
                    }
                }
#if !DEBUG
            }
            catch (Exception e)
            {
                Console.WriteLine("Error: {0}", e.Message);
                return 1;
            }
#endif

            return 0;
        }

        private static void ProcessDirectory(string srcDir, string destDir)
        {
            var files = Directory.EnumerateFiles(srcDir);

            foreach (var file in files)
            {
                var processor = _specialProcessors.FirstOrDefault(p => p.ResExtensions.Any(e => file.EndsWith(e)));

                if (processor == null)
                {
                    Console.WriteLine("Copying {0}...", file);
                    var destFileName = Path.Combine(destDir, Path.GetFileName(file));
                    File.Copy(file, destFileName, true);
                    _ResFileNames.Add(destFileName);
                }
                else
                {
                    Console.WriteLine("Processing {0}...", file);

                    var resFileName = processor.Process(file, destDir);

                    if (resFileName != null)
                    {
                        _ResFileNames.Add(resFileName);
                    }
                }
            }

            var dirs = Directory.EnumerateDirectories(srcDir);

            foreach (var dir in dirs)
            {
                var newDestDir = Path.Combine(destDir, Path.GetFileName(dir));

                if (!Directory.Exists(newDestDir))
                {
                    Directory.CreateDirectory(newDestDir);
                }

                ProcessDirectory(dir, newDestDir);
            }
        }
    }
}