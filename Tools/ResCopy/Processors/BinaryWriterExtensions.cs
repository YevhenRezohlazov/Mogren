using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ResCopy
{
    internal static class BinaryWriterExtensions
    {
        public static void WriteASCIIString(this BinaryWriter writer, string str)
        {
            var bytes = Encoding.ASCII.GetBytes(str);

            writer.Write(bytes.Length);
            writer.Write(bytes);
        }
    }
}