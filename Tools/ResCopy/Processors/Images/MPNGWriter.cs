using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;

namespace ResCopy
{
    public static class MPNGWriter
    {
        private struct ResBitmapData
        {
            public System.Drawing.Size BitmapSize;
            public MemoryStream BitmapStream;
        }

        public static void WriteMPNG(Bitmap srcBitmap, Stream targetStream, bool nearestNeighbour = false)
        {
            var potWidth = GetNearestPowerOfTwo(srcBitmap.Width);
            var potHeight = GetNearestPowerOfTwo(srcBitmap.Height);

            var resBitmaps = new List<ResBitmapData>();

            for (; potWidth > 0 && potHeight > 0; potWidth >>= 1, potHeight >>= 1)
            {
                var resBirmapStream = new MemoryStream();
                var resBitmap = CreateResizedImage(srcBitmap, potWidth, potHeight, nearestNeighbour);
                resBitmap.RotateFlip(RotateFlipType.RotateNoneFlipY);
                resBitmap.Save(resBirmapStream, ImageFormat.Png);

                resBitmaps.Add(new ResBitmapData { BitmapStream = resBirmapStream, BitmapSize = new System.Drawing.Size(potWidth, potHeight) });

                if (nearestNeighbour)
                {
                    break;
                }
            }

            var writer = new BinaryWriter(targetStream);
            var signatureBytes = new[] { (byte)'M', (byte)'P', (byte)'N', (byte)'G' };
            writer.Write(signatureBytes);

            // source image size
            writer.Write((ushort)srcBitmap.Width);
            writer.Write((ushort)srcBitmap.Height);

            // count of bitmaps
            writer.Write((ushort)resBitmaps.Count);

            uint fileShift = 10U + (uint)resBitmaps.Count * 12U;

            foreach (var resBitmap in resBitmaps)
            {
                // image size
                writer.Write((ushort)resBitmap.BitmapSize.Width);
                writer.Write((ushort)resBitmap.BitmapSize.Height);
                writer.Write(fileShift);
                writer.Write((uint)resBitmap.BitmapStream.Length);
                fileShift += (uint)resBitmap.BitmapStream.Length;
            }

            foreach (var resBitmap in resBitmaps)
            {
                resBitmap.BitmapStream.Position = 0;
                resBitmap.BitmapStream.CopyTo(writer.BaseStream);
            }
        }

        private static int GetNearestPowerOfTwo(int val)
        {
            int res = 1;

            while (res < val)
            {
                res <<= 1;
            }

            return res;
        }

        public static Bitmap CreateResizedImage(Image image, int width, int height, bool noStretch)
        {
            var destRect = noStretch
                ? new Rectangle(0, height - image.Height, image.Width, image.Height)
                : new Rectangle(0, 0, width, height);

            var destImage = new Bitmap(width, height);

            using (var graphics = Graphics.FromImage(destImage))
            {
                graphics.CompositingMode = CompositingMode.SourceCopy;
                graphics.CompositingQuality = CompositingQuality.HighQuality;
                graphics.InterpolationMode = InterpolationMode.HighQualityBicubic;
                graphics.SmoothingMode = SmoothingMode.HighQuality;
                graphics.PixelOffsetMode = PixelOffsetMode.HighQuality;
                graphics.DrawImage(image, destRect);
            }

            return destImage;
        }

    }
}