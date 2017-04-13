#pragma once

#include <Mogren/Framework/Math/Vector3D.h>
#include <Mogren/Framework/Math/Vector4D.h>

namespace Graphics
{
    ///
    /// Represents 32-bit color value.
    ///
    class Color
    {
    public:
        float r;
        float g;
        float b;
        float a;

        ///
        /// Initializes a new instance of the Color class with black color value.
        ///
        Color();

        ///
        /// Initializes a new instance of the Color class with given color value (in format 0xAARRGGBB).
        ///
        Color(uint32_t color);

        ///
        /// Initializes a new instance of the Color class with given color component values.
        ///
        Color(float r, float g, float b, float a = 1.0f);

        ///
        /// Initializes a new instance of the Color class with given color component values.
        ///
        Color(const Color &color, float a = 1.0f);

        ///
        /// Gets the vector containing color values
        ///
        Math::Vector4DF toVector4DF() const
        {
            return Math::Vector4DF(r, g, b, a);
        }

        ///
        /// Gets the vector containing color values (except alpha value)
        ///
        Math::Vector3DF toVector3DF() const
        {
            return Math::Vector3DF(r, g, b);
        }

        static const Color Pink;
        static const Color LightPink;
        static const Color HotPink;
        static const Color DeepPink;
        static const Color PaleVioletRed;
        static const Color MediumVioletRed;
        static const Color LightSalmon;
        static const Color Salmon;
        static const Color DarkSalmon;
        static const Color LightCoral;
        static const Color IndianRed;
        static const Color Crimson;
        static const Color FireBrick;
        static const Color DarkRed;
        static const Color Red;
        static const Color OrangeRed;
        static const Color Tomato;
        static const Color Coral;
        static const Color DarkOrange;
        static const Color Orange;
        static const Color Gold;
        static const Color Yellow;
        static const Color LightYellow;
        static const Color LemonChiffon;
        static const Color LightGoldenrodYellow;
        static const Color PapayaWhip;
        static const Color Moccasin;
        static const Color PeachPuff;
        static const Color PaleGoldenrod;
        static const Color Khaki;
        static const Color DarkKhaki;
        static const Color Cornsilk;
        static const Color BlanchedAlmond;
        static const Color Bisque;
        static const Color NavajoWhite;
        static const Color Wheat;
        static const Color BurlyWood;
        static const Color Tan;
        static const Color RosyBrown;
        static const Color SandyBrown;
        static const Color Goldenrod;
        static const Color DarkGoldenrod;
        static const Color Peru;
        static const Color Chocolate;
        static const Color SaddleBrown;
        static const Color Sienna;
        static const Color Brown;
        static const Color Maroon;
        static const Color DarkOliveGreen;
        static const Color Olive;
        static const Color OliveDrab;
        static const Color YellowGreen;
        static const Color LimeGreen;
        static const Color Lime;
        static const Color LawnGreen;
        static const Color Chartreuse;
        static const Color GreenYellow;
        static const Color SpringGreen;
        static const Color MediumSpringGreen;
        static const Color LightGreen;
        static const Color PaleGreen;
        static const Color DarkSeaGreen;
        static const Color MediumSeaGreen;
        static const Color SeaGreen;
        static const Color ForestGreen;
        static const Color Green;
        static const Color DarkGreen;
        static const Color MediumAquamarine;
        static const Color Aqua;
        static const Color Cyan;
        static const Color LightCyan;
        static const Color PaleTurquoise;
        static const Color Aquamarine;
        static const Color Turquoise;
        static const Color MediumTurquoise;
        static const Color DarkTurquoise;
        static const Color LightSeaGreen;
        static const Color CadetBlue;
        static const Color DarkCyan;
        static const Color Teal;
        static const Color LightSteelBlue;
        static const Color PowderBlue;
        static const Color LightBlue;
        static const Color SkyBlue;
        static const Color LightSkyBlue;
        static const Color DeepSkyBlue;
        static const Color DodgerBlue;
        static const Color CornflowerBlue;
        static const Color SteelBlue;
        static const Color RoyalBlue;
        static const Color Blue;
        static const Color MediumBlue;
        static const Color DarkBlue;
        static const Color Navy;
        static const Color MidnightBlue;
        static const Color Lavender;
        static const Color Thistle;
        static const Color Plum;
        static const Color Violet;
        static const Color Orchid;
        static const Color Fuchsia;
        static const Color Magenta;
        static const Color MediumOrchid;
        static const Color MediumPurple;
        static const Color BlueViolet;
        static const Color DarkViolet;
        static const Color DarkOrchid;
        static const Color DarkMagenta;
        static const Color Purple;
        static const Color Indigo;
        static const Color DarkSlateBlue;
        static const Color SlateBlue;
        static const Color MediumSlateBlue;
        static const Color White;
        static const Color Snow;
        static const Color Honeydew;
        static const Color MintCream;
        static const Color Azure;
        static const Color AliceBlue;
        static const Color GhostWhite;
        static const Color WhiteSmoke;
        static const Color Seashell;
        static const Color Beige;
        static const Color OldLace;
        static const Color FloralWhite;
        static const Color Ivory;
        static const Color AntiqueWhite;
        static const Color Linen;
        static const Color LavenderBlush;
        static const Color MistyRose;
        static const Color Gainsboro;
        static const Color LightGray;
        static const Color Silver;
        static const Color DarkGray;
        static const Color Gray;
        static const Color DimGray;
        static const Color LightSlateGray;
        static const Color SlateGray;
        static const Color DarkSlateGray;
        static const Color Black;
        static const Color TransparentBlack;
        static const Color TransparentWhite;
    };
}

