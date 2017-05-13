using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Text;

namespace ResCopy
{
    internal class MogrenFontData
    {
        public int FontHeight { get; private set; }

        public Bitmap MapBitmap { get; private set; }

        public CharData[] CharsData { get; private set; }

        public MogrenFontData(int fontHeight, Bitmap mapBitmap, CharData[] charsData)
        {
            FontHeight = fontHeight;
            MapBitmap = mapBitmap;
            CharsData = charsData;
        }

        public void Save(string fileName, bool noMipMaps)
        {
            using (var writer = new BinaryWriter(new FileStream(fileName, FileMode.Create), Encoding.Unicode))
            {
                float mapWidth = (float)MapBitmap.Width;
                float mapHeight = (float)MapBitmap.Height;

                // 5 bytes - header
                var headerBytes = Encoding.ASCII.GetBytes("MGFNT");
                writer.Write(headerBytes);

                // 4 bytes float - font size relative to texture size
                writer.Write(FontHeight / mapHeight);

                // 4 bytes integer - chars data count
                writer.Write(CharsData.Length);

                foreach (var ch in CharsData)
                {
                    // 2 bytes - char
                    writer.Write(ch.Char);

                    // 4 bytes float - map position x
                    writer.Write(ch.MapPosition.X / mapWidth);

                    // 4 bytes float - map position y
                    writer.Write(ch.MapPosition.Y / mapHeight);

                    // 4 bytes float - container width
                    writer.Write(ch.ContainerSize.Width / mapWidth);

                    // 4 bytes float - container height
                    writer.Write(ch.ContainerSize.Height / mapHeight);

                    // 4 bytes float - region position x
                    writer.Write(ch.Region.X / mapWidth);

                    // 4 bytes float - region position y
                    writer.Write(ch.Region.Y / mapHeight);

                    // 4 bytes float - region width
                    writer.Write(ch.Region.Width / mapWidth);

                    // 4 bytes float - region height
                    writer.Write(ch.Region.Height / mapHeight);
                }

                var mapStream = new MemoryStream();
                MPNGWriter.WriteMPNG(MapBitmap, mapStream, noMipMaps);

                // 4 bytes integer - map image size in bytes
                writer.Write((int)mapStream.Length);

                // write map bitmap image
                mapStream.Position = 0;
                mapStream.CopyTo(writer.BaseStream);
            }
        }
    }
}