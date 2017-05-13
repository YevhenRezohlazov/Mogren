using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Text;
using System.IO;
using System.Linq;

namespace ResCopy
{
    public class FontProcessor : SpecialProcessor
    {
        public FontProcessor()
            : base(".mf", ".ttf")
        {
        }

        public override string Process(string srcResPath, string destDirPath)
        {
            if (srcResPath.EndsWith(".ttf"))
            {
                Console.WriteLine("Ignoring source font file...");
                return null;
            }

            Console.WriteLine("Processing as Mogren font...");

            var outputFileName = Path.Combine(destDirPath, Path.GetFileName(srcResPath));

            var fontData = FontData.Load(srcResPath);
            var fontFile = Path.Combine(Path.GetDirectoryName(srcResPath), fontData.Name);

            FontFamily family;

            if (File.Exists(fontFile))
            {
                var fontCollection = new PrivateFontCollection();
                fontCollection.AddFontFile(fontFile);

                if (fontCollection.Families.Length == 0)
                {
                    throw new Exception(string.Format("Can't load font from {0}.", fontFile));
                }

                family = fontCollection.Families[0];
            }
            else
            {
                family = new FontFamily(fontData.Name);
            }

            var style = (FontStyle)Enum.Parse(typeof(FontStyle), fontData.Style, true);

            var font = new Font(family, (float)fontData.Size, style, GraphicsUnit.Pixel);
            var charsData = new List<CharData>();

            // get chars data
            {
                // fake bitmap
                var bitmap = new Bitmap(1, 1);
                var graphics = Graphics.FromImage(bitmap);
                graphics.TextRenderingHint = TextRenderingHint.SingleBitPerPixelGridFit;
                graphics.PageUnit = GraphicsUnit.Pixel;

                foreach (var ch in fontData.Alphabet)
                {
                    charsData.Add(new CharData(ch, font, graphics));
                }
            }

            var totalSquare = charsData.Sum(d => d.ContainerSize.Width * d.ContainerSize.Height);
            var initialMapWidth = (int)Math.Sqrt(totalSquare);
            var maxCharWidth = charsData.Max(cd => cd.ContainerSize.Width);

            if (maxCharWidth > initialMapWidth)
            {
                initialMapWidth = maxCharWidth;
            }

            var sortedCharsData = charsData.OrderByDescending(d => d.ContainerSize.Width).ToList();

            var curWidth = 0;
            var curHeight = 0;
            var maxLineHeight = 0;

            var maxMapWidth = 0;
            var maxMapHeight = 0;

            while (sortedCharsData.Count > 0)
            {
                var leftWidth = initialMapWidth - curWidth;

                var found = false;

                for (var i = 0; i < sortedCharsData.Count; ++i)
                {
                    var cd = sortedCharsData[i];

                    if (cd.ContainerSize.Width <= leftWidth)
                    {
                        cd.MapPosition = new Point(curWidth, curHeight);

                        if (cd.ContainerSize.Height > maxLineHeight)
                        {
                            maxLineHeight = cd.ContainerSize.Height;
                        }

                        if (curHeight + cd.ContainerSize.Height > maxMapHeight)
                        {
                            maxMapHeight = curHeight + cd.ContainerSize.Height;
                        }

                        sortedCharsData.RemoveAt(i);
                        curWidth += cd.ContainerSize.Width;

                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    curHeight += maxLineHeight;

                    if (curWidth > maxMapWidth)
                    {
                        maxMapWidth = curWidth;
                    }

                    curWidth = 0;
                    maxLineHeight = 0;
                }
            }

            var mapBitmap = new Bitmap(GetNearestPowerOfTwo(maxMapWidth), GetNearestPowerOfTwo(maxMapHeight));
            var mapBitmapGraphics = Graphics.FromImage(mapBitmap);
            mapBitmapGraphics.TextRenderingHint = TextRenderingHint.SingleBitPerPixelGridFit;

            foreach (var cd in charsData)
            {
                var str = new string(cd.Char, 1);
                mapBitmapGraphics.DrawString(str, font, Brushes.White, cd.MapPosition);
            }

            var mogrenFont = new MogrenFontData(font.Height, mapBitmap, charsData.ToArray());
            mogrenFont.Save(outputFileName, fontData.NoMipMaps);
            return outputFileName;
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
    }
}