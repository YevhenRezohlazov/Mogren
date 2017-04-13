using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace ResCopy
{
    public class StringsProcessor : SpecialProcessor
    {
        public StringsProcessor()
            : base("str")
        {
        }

        public override string Process(string srcResPath, string destDirPath)
        {
            Console.WriteLine("Processing \"{0}\" as localization strings file.", srcResPath);

            var lines = File.ReadAllLines(srcResPath);

            var localizedStrings = new Dictionary<string, List<string>>();

            foreach (var line in lines)
            {
                if (!line.Contains(':'))
                {
                    Console.WriteLine("WARNING: Line \"{0}\" does not contain colon.", line);
                }
                else
                {
                    var parts = line.Split(new[] { ':' }, 2);
                    var key = parts[0];
                    var value = parts[1];

                    if (!localizedStrings.ContainsKey(key))
                    {
                        localizedStrings[key] = new List<string>();
                    }

                    localizedStrings[key].Add(value);
                }
            }

            var outputFilePath = Path.Combine(destDirPath, Path.GetFileName(srcResPath));

            using (var writer = new BinaryWriter(new FileStream(outputFilePath, FileMode.Create)))
            {
                // 4 bytes - count strings
                writer.Write(localizedStrings.Count);

                foreach (var pair in localizedStrings)
                {
                    var keyBytes = Encoding.UTF8.GetBytes(pair.Key);

                    writer.Write(keyBytes.Length);
                    writer.Write(keyBytes);

                    writer.Write(pair.Value.Count);

                    foreach (var value in pair.Value)
                    {
                        var valueBytes = Encoding.UTF8.GetBytes(value);
                        writer.Write(valueBytes.Length);
                        writer.Write(valueBytes);
                    }
                }
            }

            return outputFilePath;
        }
    }
}