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
        constexpr Color();

        ///
        /// Initializes a new instance of the Color class with given color value (in format 0xAARRGGBB).
        ///
        constexpr explicit Color(uint32_t color) noexcept;

        ///
        /// Initializes a new instance of the Color class with given color component values.
        ///
        constexpr Color(float r, float g, float b, float a = 1.0f);

        ///
        /// Initializes a new instance of the Color class with given color component values.
        ///
        constexpr Color(const Color &color, float a);

        ///
        /// Gets the vector containing color values
        ///
        constexpr Math::Vector4DF toVector4DF() const
        {
            return Math::Vector4DF(r, g, b, a);
        }

        ///
        /// Gets the vector containing color values (except alpha value)
        ///
        constexpr Math::Vector3DF toVector3DF() const
        {
            return Math::Vector3DF(r, g, b);
        }
    };

    constexpr Color::Color() : r(0.0f), g(0.0f), b(0.0f), a(0.0f)
    {
    }

    constexpr Color::Color(uint32_t color) noexcept
        : r((color >> 16 & 0xFF) / 255.0f)
        , g((color >> 8 & 0xFF) / 255.0f)
        , b((color >> 0 & 0xFF) / 255.0f)
        , a((color >> 24 & 0xFF) / 255.0f)
    {
    }

    constexpr Color::Color(float r, float g, float b, float a /*= 1.0f*/) : r(r), g(g), b(b), a(a)
    {
    }

    constexpr Color::Color(const Color &color, float a /*= 1.0f*/)
        : r(color.r), g(color.g), b(color.b), a(a)
    {
    }

    namespace Colors
    {
        constexpr Color Pink = Color(0xFFFFC0CB);
        constexpr Color LightPink(0xFFFFB6C1);
        constexpr Color HotPink(0xFFFF69B4);
        constexpr Color DeepPink(0xFFFF1493);
        constexpr Color PaleVioletRed(0xFFDB7093);
        constexpr Color MediumVioletRed(0xFFC71585);
        constexpr Color LightSalmon(0xFFFFA07A);
        constexpr Color Salmon(0xFFFA8072);
        constexpr Color DarkSalmon(0xFFE9967A);
        constexpr Color LightCoral(0xFFF08080);
        constexpr Color IndianRed(0xFFCD5C5C);
        constexpr Color Crimson(0xFFDC143C);
        constexpr Color FireBrick(0xFFB22222);
        constexpr Color DarkRed(0xFF8B0000);
        constexpr Color Red(0xFFFF0000);
        constexpr Color OrangeRed(0xFFFF4500);
        constexpr Color Tomato(0xFFFF6347);
        constexpr Color Coral(0xFFFF7F50);
        constexpr Color DarkOrange(0xFFFF8C00);
        constexpr Color Orange(0xFFFFA500);
        constexpr Color Gold(0xFFFFD700);
        constexpr Color Yellow(0xFFFFFF00);
        constexpr Color LightYellow(0xFFFFFFE0);
        constexpr Color LemonChiffon(0xFFFFFACD);
        constexpr Color LightGoldenrodYellow(0xFFFAFAD2);
        constexpr Color PapayaWhip(0xFFFFEFD5);
        constexpr Color Moccasin(0xFFFFE4B5);
        constexpr Color PeachPuff(0xFFFFDAB9);
        constexpr Color PaleGoldenrod(0xFFEEE8AA);
        constexpr Color Khaki(0xFFF0E68C);
        constexpr Color DarkKhaki(0xFFBDB76B);
        constexpr Color Cornsilk(0xFFFFF8DC);
        constexpr Color BlanchedAlmond(0xFFFFEBCD);
        constexpr Color Bisque(0xFFFFE4C4);
        constexpr Color NavajoWhite(0xFFFFDEAD);
        constexpr Color Wheat(0xFFF5DEB3);
        constexpr Color BurlyWood(0xFFDEB887);
        constexpr Color Tan(0xFFD2B48C);
        constexpr Color RosyBrown(0xFFBC8F8F);
        constexpr Color SandyBrown(0xFFF4A460);
        constexpr Color Goldenrod(0xFFDAA520);
        constexpr Color DarkGoldenrod(0xFFB8860B);
        constexpr Color Peru(0xFFCD853F);
        constexpr Color Chocolate(0xFFD2691E);
        constexpr Color SaddleBrown(0xFF8B4513);
        constexpr Color Sienna(0xFFA0522D);
        constexpr Color Brown(0xFFA52A2A);
        constexpr Color Maroon(0xFF800000);
        constexpr Color DarkOliveGreen(0xFF556B2F);
        constexpr Color Olive(0xFF808000);
        constexpr Color OliveDrab(0xFF6B8E23);
        constexpr Color YellowGreen(0xFF9ACD32);
        constexpr Color LimeGreen(0xFF32CD32);
        constexpr Color Lime(0xFF00FF00);
        constexpr Color LawnGreen(0xFF7CFC00);
        constexpr Color Chartreuse(0xFF7FFF00);
        constexpr Color GreenYellow(0xFFADFF2F);
        constexpr Color SpringGreen(0xFF00FF7F);
        constexpr Color MediumSpringGreen(0xFF00FA9A);
        constexpr Color LightGreen(0xFF90EE90);
        constexpr Color PaleGreen(0xFF98FB98);
        constexpr Color DarkSeaGreen(0xFF8FBC8F);
        constexpr Color MediumSeaGreen(0xFF3CB371);
        constexpr Color SeaGreen(0xFF2E8B57);
        constexpr Color ForestGreen(0xFF228B22);
        constexpr Color Green(0xFF008000);
        constexpr Color DarkGreen(0xFF006400);
        constexpr Color MediumAquamarine(0xFF66CDAA);
        constexpr Color Aqua(0xFF00FFFF);
        constexpr Color Cyan(0xFF00FFFF);
        constexpr Color LightCyan(0xFFE0FFFF);
        constexpr Color PaleTurquoise(0xFFAFEEEE);
        constexpr Color Aquamarine(0xFF7FFFD4);
        constexpr Color Turquoise(0xFF40E0D0);
        constexpr Color MediumTurquoise(0xFF48D1CC);
        constexpr Color DarkTurquoise(0xFF00CED1);
        constexpr Color LightSeaGreen(0xFF20B2AA);
        constexpr Color CadetBlue(0xFF5F9EA0);
        constexpr Color DarkCyan(0xFF008B8B);
        constexpr Color Teal(0xFF008080);
        constexpr Color LightSteelBlue(0xFFB0C4DE);
        constexpr Color PowderBlue(0xFFB0E0E6);
        constexpr Color LightBlue(0xFFADD8E6);
        constexpr Color SkyBlue(0xFF87CEEB);
        constexpr Color LightSkyBlue(0xFF87CEFA);
        constexpr Color DeepSkyBlue(0xFF00BFFF);
        constexpr Color DodgerBlue(0xFF1E90FF);
        constexpr Color CornflowerBlue(0xFF6495ED);
        constexpr Color SteelBlue(0xFF4682B4);
        constexpr Color RoyalBlue(0xFF4169E1);
        constexpr Color Blue(0xFF0000FF);
        constexpr Color MediumBlue(0xFF0000CD);
        constexpr Color DarkBlue(0xFF00008B);
        constexpr Color Navy(0xFF000080);
        constexpr Color MidnightBlue(0xFF191970);
        constexpr Color Lavender(0xFFE6E6FA);
        constexpr Color Thistle(0xFFD8BFD8);
        constexpr Color Plum(0xFFDDA0DD);
        constexpr Color Violet(0xFFEE82EE);
        constexpr Color Orchid(0xFFDA70D6);
        constexpr Color Fuchsia(0xFFFF00FF);
        constexpr Color Magenta(0xFFFF00FF);
        constexpr Color MediumOrchid(0xFFBA55D3);
        constexpr Color MediumPurple(0xFF9370DB);
        constexpr Color BlueViolet(0xFF8A2BE2);
        constexpr Color DarkViolet(0xFF9400D3);
        constexpr Color DarkOrchid(0xFF9932CC);
        constexpr Color DarkMagenta(0xFF8B008B);
        constexpr Color Purple(0xFF800080);
        constexpr Color Indigo(0xFF4B0082);
        constexpr Color DarkSlateBlue(0xFF483D8B);
        constexpr Color SlateBlue(0xFF6A5ACD);
        constexpr Color MediumSlateBlue(0xFF7B68EE);
        constexpr Color White(0xFFFFFFFF);
        constexpr Color Snow(0xFFFFFAFA);
        constexpr Color Honeydew(0xFFF0FFF0);
        constexpr Color MintCream(0xFFF5FFFA);
        constexpr Color Azure(0xFFF0FFFF);
        constexpr Color AliceBlue(0xFFF0F8FF);
        constexpr Color GhostWhite(0xFFF8F8FF);
        constexpr Color WhiteSmoke(0xFFF5F5F5);
        constexpr Color Seashell(0xFFFFF5EE);
        constexpr Color Beige(0xFFF5F5DC);
        constexpr Color OldLace(0xFFFDF5E6);
        constexpr Color FloralWhite(0xFFFFFAF0);
        constexpr Color Ivory(0xFFFFFFF0);
        constexpr Color AntiqueWhite(0xFFFAEBD7);
        constexpr Color Linen(0xFFFAF0E6);
        constexpr Color LavenderBlush(0xFFFFF0F5);
        constexpr Color MistyRose(0xFFFFE4E1);
        constexpr Color Gainsboro(0xFFDCDCDC);
        constexpr Color LightGray(0xFFD3D3D3);
        constexpr Color Silver(0xFFC0C0C0);
        constexpr Color DarkGray(0xFFA9A9A9);
        constexpr Color Gray(0xFF808080);
        constexpr Color DimGray(0xFF696969);
        constexpr Color LightSlateGray(0xFF778899);
        constexpr Color SlateGray(0xFF708090);
        constexpr Color DarkSlateGray(0xFF2F4F4F);
        constexpr Color Black(0xFF000000);
        constexpr Color TransparentBlack(0x0000000);
        constexpr Color TransparentWhite(0x00FFFFFF);
    }
}

