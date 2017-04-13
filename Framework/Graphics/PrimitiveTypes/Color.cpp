#include "Color.h"

namespace Graphics
{
    Color::Color() : r(0.0f), g(0.0f), b(0.0f), a(0.0f)
    {
    }

    Color::Color(uint32_t color)
    {
        a = (color >> 24 & 0xFF) / 255.0f;
        r = (color >> 16 & 0xFF) / 255.0f;
        g = (color >> 8 & 0xFF) / 255.0f;
        b = (color >> 0 & 0xFF) / 255.0f;
    }

    Color::Color(float r, float g, float b, float a /*= 1.0f*/) : r(r), g(g), b(b), a(a)
    {
    }

    Color::Color(const Color &color, float a /*= 1.0f*/)
        : r(color.r), g(color.g), b(color.b), a(a)
    {
    }

    const Color Color::Pink(0xFFFFC0CB);
    const Color Color::LightPink(0xFFFFB6C1);
    const Color Color::HotPink(0xFFFF69B4);
    const Color Color::DeepPink(0xFFFF1493);
    const Color Color::PaleVioletRed(0xFFDB7093);
    const Color Color::MediumVioletRed(0xFFC71585);
    const Color Color::LightSalmon(0xFFFFA07A);
    const Color Color::Salmon(0xFFFA8072);
    const Color Color::DarkSalmon(0xFFE9967A);
    const Color Color::LightCoral(0xFFF08080);
    const Color Color::IndianRed(0xFFCD5C5C);
    const Color Color::Crimson(0xFFDC143C);
    const Color Color::FireBrick(0xFFB22222);
    const Color Color::DarkRed(0xFF8B0000);
    const Color Color::Red(0xFFFF0000);
    const Color Color::OrangeRed(0xFFFF4500);
    const Color Color::Tomato(0xFFFF6347);
    const Color Color::Coral(0xFFFF7F50);
    const Color Color::DarkOrange(0xFFFF8C00);
    const Color Color::Orange(0xFFFFA500);
    const Color Color::Gold(0xFFFFD700);
    const Color Color::Yellow(0xFFFFFF00);
    const Color Color::LightYellow(0xFFFFFFE0);
    const Color Color::LemonChiffon(0xFFFFFACD);
    const Color Color::LightGoldenrodYellow(0xFFFAFAD2);
    const Color Color::PapayaWhip(0xFFFFEFD5);
    const Color Color::Moccasin(0xFFFFE4B5);
    const Color Color::PeachPuff(0xFFFFDAB9);
    const Color Color::PaleGoldenrod(0xFFEEE8AA);
    const Color Color::Khaki(0xFFF0E68C);
    const Color Color::DarkKhaki(0xFFBDB76B);
    const Color Color::Cornsilk(0xFFFFF8DC);
    const Color Color::BlanchedAlmond(0xFFFFEBCD);
    const Color Color::Bisque(0xFFFFE4C4);
    const Color Color::NavajoWhite(0xFFFFDEAD);
    const Color Color::Wheat(0xFFF5DEB3);
    const Color Color::BurlyWood(0xFFDEB887);
    const Color Color::Tan(0xFFD2B48C);
    const Color Color::RosyBrown(0xFFBC8F8F);
    const Color Color::SandyBrown(0xFFF4A460);
    const Color Color::Goldenrod(0xFFDAA520);
    const Color Color::DarkGoldenrod(0xFFB8860B);
    const Color Color::Peru(0xFFCD853F);
    const Color Color::Chocolate(0xFFD2691E);
    const Color Color::SaddleBrown(0xFF8B4513);
    const Color Color::Sienna(0xFFA0522D);
    const Color Color::Brown(0xFFA52A2A);
    const Color Color::Maroon(0xFF800000);
    const Color Color::DarkOliveGreen(0xFF556B2F);
    const Color Color::Olive(0xFF808000);
    const Color Color::OliveDrab(0xFF6B8E23);
    const Color Color::YellowGreen(0xFF9ACD32);
    const Color Color::LimeGreen(0xFF32CD32);
    const Color Color::Lime(0xFF00FF00);
    const Color Color::LawnGreen(0xFF7CFC00);
    const Color Color::Chartreuse(0xFF7FFF00);
    const Color Color::GreenYellow(0xFFADFF2F);
    const Color Color::SpringGreen(0xFF00FF7F);
    const Color Color::MediumSpringGreen(0xFF00FA9A);
    const Color Color::LightGreen(0xFF90EE90);
    const Color Color::PaleGreen(0xFF98FB98);
    const Color Color::DarkSeaGreen(0xFF8FBC8F);
    const Color Color::MediumSeaGreen(0xFF3CB371);
    const Color Color::SeaGreen(0xFF2E8B57);
    const Color Color::ForestGreen(0xFF228B22);
    const Color Color::Green(0xFF008000);
    const Color Color::DarkGreen(0xFF006400);
    const Color Color::MediumAquamarine(0xFF66CDAA);
    const Color Color::Aqua(0xFF00FFFF);
    const Color Color::Cyan(0xFF00FFFF);
    const Color Color::LightCyan(0xFFE0FFFF);
    const Color Color::PaleTurquoise(0xFFAFEEEE);
    const Color Color::Aquamarine(0xFF7FFFD4);
    const Color Color::Turquoise(0xFF40E0D0);
    const Color Color::MediumTurquoise(0xFF48D1CC);
    const Color Color::DarkTurquoise(0xFF00CED1);
    const Color Color::LightSeaGreen(0xFF20B2AA);
    const Color Color::CadetBlue(0xFF5F9EA0);
    const Color Color::DarkCyan(0xFF008B8B);
    const Color Color::Teal(0xFF008080);
    const Color Color::LightSteelBlue(0xFFB0C4DE);
    const Color Color::PowderBlue(0xFFB0E0E6);
    const Color Color::LightBlue(0xFFADD8E6);
    const Color Color::SkyBlue(0xFF87CEEB);
    const Color Color::LightSkyBlue(0xFF87CEFA);
    const Color Color::DeepSkyBlue(0xFF00BFFF);
    const Color Color::DodgerBlue(0xFF1E90FF);
    const Color Color::CornflowerBlue(0xFF6495ED);
    const Color Color::SteelBlue(0xFF4682B4);
    const Color Color::RoyalBlue(0xFF4169E1);
    const Color Color::Blue(0xFF0000FF);
    const Color Color::MediumBlue(0xFF0000CD);
    const Color Color::DarkBlue(0xFF00008B);
    const Color Color::Navy(0xFF000080);
    const Color Color::MidnightBlue(0xFF191970);
    const Color Color::Lavender(0xFFE6E6FA);
    const Color Color::Thistle(0xFFD8BFD8);
    const Color Color::Plum(0xFFDDA0DD);
    const Color Color::Violet(0xFFEE82EE);
    const Color Color::Orchid(0xFFDA70D6);
    const Color Color::Fuchsia(0xFFFF00FF);
    const Color Color::Magenta(0xFFFF00FF);
    const Color Color::MediumOrchid(0xFFBA55D3);
    const Color Color::MediumPurple(0xFF9370DB);
    const Color Color::BlueViolet(0xFF8A2BE2);
    const Color Color::DarkViolet(0xFF9400D3);
    const Color Color::DarkOrchid(0xFF9932CC);
    const Color Color::DarkMagenta(0xFF8B008B);
    const Color Color::Purple(0xFF800080);
    const Color Color::Indigo(0xFF4B0082);
    const Color Color::DarkSlateBlue(0xFF483D8B);
    const Color Color::SlateBlue(0xFF6A5ACD);
    const Color Color::MediumSlateBlue(0xFF7B68EE);
    const Color Color::White(0xFFFFFFFF);
    const Color Color::Snow(0xFFFFFAFA);
    const Color Color::Honeydew(0xFFF0FFF0);
    const Color Color::MintCream(0xFFF5FFFA);
    const Color Color::Azure(0xFFF0FFFF);
    const Color Color::AliceBlue(0xFFF0F8FF);
    const Color Color::GhostWhite(0xFFF8F8FF);
    const Color Color::WhiteSmoke(0xFFF5F5F5);
    const Color Color::Seashell(0xFFFFF5EE);
    const Color Color::Beige(0xFFF5F5DC);
    const Color Color::OldLace(0xFFFDF5E6);
    const Color Color::FloralWhite(0xFFFFFAF0);
    const Color Color::Ivory(0xFFFFFFF0);
    const Color Color::AntiqueWhite(0xFFFAEBD7);
    const Color Color::Linen(0xFFFAF0E6);
    const Color Color::LavenderBlush(0xFFFFF0F5);
    const Color Color::MistyRose(0xFFFFE4E1);
    const Color Color::Gainsboro(0xFFDCDCDC);
    const Color Color::LightGray(0xFFD3D3D3);
    const Color Color::Silver(0xFFC0C0C0);
    const Color Color::DarkGray(0xFFA9A9A9);
    const Color Color::Gray(0xFF808080);
    const Color Color::DimGray(0xFF696969);
    const Color Color::LightSlateGray(0xFF778899);
    const Color Color::SlateGray(0xFF708090);
    const Color Color::DarkSlateGray(0xFF2F4F4F);
    const Color Color::Black(0xFF000000);
    const Color Color::TransparentBlack(0x0000000);
    const Color Color::TransparentWhite(0x00FFFFFF);
}