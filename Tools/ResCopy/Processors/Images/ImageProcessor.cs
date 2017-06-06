using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ResCopy
{
    public class ImageProcessor : SpecialProcessor
    {
        public ImageProcessor()
            : base(".png")
        {
        }

        public override string Process(string srcResPath, string destDirPath)
        {
            var srcBitmap = new Bitmap(srcResPath);
            var outputFilePath = Path.Combine(destDirPath, Path.GetFileName(srcResPath));
            MPNGWriter.WriteMPNG(srcBitmap, new FileStream(outputFilePath, FileMode.Create), srcResPath.ToLower().EndsWith(".nn.png"));
            return outputFilePath;
        }
    }
}