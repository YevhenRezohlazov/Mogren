using System.Drawing;

namespace ResCopy
{
    internal class CharData
    {
        public char Char;

        public Size ContainerSize;

        public Rectangle Region;

        public Point MapPosition;

        public CharData(char ch, Font font, Graphics graphics)
        {
            Char = ch;

            var str = new string(ch, 1);
            ContainerSize = graphics.MeasureString(str, font).ToSize();

            if (ch != ' ')
            {
                var fmt = new StringFormat();
                fmt.SetMeasurableCharacterRanges(new[] { new CharacterRange(0, 1) });

                var ranges = graphics.MeasureCharacterRanges(str, font, new RectangleF(0.0f, 0.0f, float.MaxValue, float.MaxValue), fmt);
                var regionF = ranges[0].GetBounds(graphics);
                Region = new Rectangle((int)regionF.X, (int)regionF.Y, (int)regionF.Width, (int)regionF.Height);
            }
            else
            {
                Region = new Rectangle(new Point(), ContainerSize);
            }
        }
    }
}