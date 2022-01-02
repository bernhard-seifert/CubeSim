

// COLOR 1.0.2


// Includes
#include <color.hpp>


// Convert to String
Color::operator const std::string(void) const
{
   // String
   char str[16];

   // Format String
   sprintf_s(str, sizeof(str), "#%02X%02X%02X", _red, _green, _blue);

   // Return String
   return str;
}


// Default Colors
const Color Color::ALICEBLUE = Color(240, 248, 255);
const Color Color::ANTIQUEWHITE = Color(250, 235, 215);
const Color Color::AQUA = Color(0, 255, 255);
const Color Color::AQUAMARINE = Color(127, 255, 212);
const Color Color::AZURE = Color(240, 255, 255);
const Color Color::BEIGE = Color(245, 245, 220);
const Color Color::BISQUE = Color(255, 228, 196);
const Color Color::BLACK = Color(0, 0, 0);
const Color Color::BLANCHEDALMOND = Color(255, 235, 205);
const Color Color::BLUE = Color(0, 0, 255);
const Color Color::BLUEVIOLET = Color(138, 43, 226);
const Color Color::BROWN = Color(165, 42, 42);
const Color Color::BURLYWOOD = Color(222, 184, 135);
const Color Color::CADETBLUE = Color(95, 158, 160);
const Color Color::CHARTREUSE = Color(127, 255, 0);
const Color Color::CHOCOLATE = Color(210, 105, 30);
const Color Color::CORAL = Color(255, 127, 80);
const Color Color::CORNFLOWERBLUE = Color(100, 149, 237);
const Color Color::CORNSILK = Color(255, 248, 220);
const Color Color::CRIMSON = Color(220, 20, 60);
const Color Color::CYAN = Color(0, 255, 255);
const Color Color::DARKBLUE = Color(0, 0, 139);
const Color Color::DARKCYAN = Color(0, 139, 139);
const Color Color::DARKGOLDENROD = Color(184, 134, 11);
const Color Color::DARKGRAY = Color(169, 169, 169);
const Color Color::DARKGREEN = Color(0, 100, 0);
const Color Color::DARKKHAKI = Color(189, 183, 107);
const Color Color::DARKMAGENTA = Color(139, 0, 139);
const Color Color::DARKOLIVEGREEN = Color(85, 107, 47);
const Color Color::DARKORANGE = Color(255, 140, 0);
const Color Color::DARKORCHID = Color(153, 50, 204);
const Color Color::DARKRED = Color(139, 0, 0);
const Color Color::DARKSALMON = Color(233, 150, 122);
const Color Color::DARKSEAGREEN = Color(143, 188, 143);
const Color Color::DARKSLATEBLUE = Color(72, 61, 139);
const Color Color::DARKSLATEGRAY = Color(47, 79, 79);
const Color Color::DARKTURQUOISE = Color(0, 206, 209);
const Color Color::DARKVIOLET = Color(148, 0, 211);
const Color Color::DEEPPINK = Color(255, 20, 147);
const Color Color::DEEPSKYBLUE = Color(0, 191, 255);
const Color Color::DIMGRAY = Color(105, 105, 105);
const Color Color::DODGERBLUE = Color(30, 144, 255);
const Color Color::FIREBRICK = Color(178, 34, 34);
const Color Color::FLORALWHITE = Color(255, 250, 240);
const Color Color::FORESTGREEN = Color(34, 139, 34);
const Color Color::FUCHSIA = Color(255, 0, 255);
const Color Color::GAINSBORO = Color(220, 220, 220);
const Color Color::GHOSTWHITE = Color(248, 248, 255);
const Color Color::GOLD = Color(255, 215, 0);
const Color Color::GOLDENROD = Color(218, 165, 32);
const Color Color::GRAY = Color(128, 128, 128);
const Color Color::GREEN = Color(0, 128, 0);
const Color Color::GREENYELLOW = Color(173, 255, 47);
const Color Color::HONEYDEW = Color(240, 255, 240);
const Color Color::HOTPINK = Color(255, 105, 180);
const Color Color::INDIANRED = Color(205, 92, 92);
const Color Color::INDIGO = Color(75, 0, 130);
const Color Color::IVORY = Color(255, 255, 240);
const Color Color::KHAKI = Color(240, 230, 140);
const Color Color::LAVENDER = Color(230, 230, 250);
const Color Color::LAVENDERBLUSH = Color(255, 240, 245);
const Color Color::LAWNGREEN = Color(124, 252, 0);
const Color Color::LEMONCHIFFON = Color(255, 250, 205);
const Color Color::LIGHTBLUE = Color(173, 216, 230);
const Color Color::LIGHTCORAL = Color(240, 128, 128);
const Color Color::LIGHTCYAN = Color(224, 255, 255);
const Color Color::LIGHTGOLDENRODYELLOW = Color(250, 250, 210);
const Color Color::LIGHTGRAY = Color(211, 211, 211);
const Color Color::LIGHTGREEN = Color(144, 238, 144);
const Color Color::LIGHTPINK = Color(255, 182, 193);
const Color Color::LIGHTSALMON = Color(255, 160, 122);
const Color Color::LIGHTSEAGREEN = Color(32, 178, 170);
const Color Color::LIGHTSKYBLUE = Color(135, 206, 250);
const Color Color::LIGHTSLATEGRAY = Color(119, 136, 153);
const Color Color::LIGHTSTEELBLUE = Color(176, 196, 222);
const Color Color::LIGHTYELLOW = Color(255, 255, 224);
const Color Color::LIME = Color(0, 255, 0);
const Color Color::LIMEGREEN = Color(50, 205, 50);
const Color Color::LINEN = Color(250, 240, 230);
const Color Color::MAGENTA = Color(255, 0, 255);
const Color Color::MAROON = Color(128, 0, 0);
const Color Color::MEDIUMAQUAMARINE = Color(102, 205, 170);
const Color Color::MEDIUMBLUE = Color(0, 0, 205);
const Color Color::MEDIUMORCHID = Color(186, 85, 211);
const Color Color::MEDIUMPURPLE = Color(147, 112, 219);
const Color Color::MEDIUMSEAGREEN = Color(60, 179, 113);
const Color Color::MEDIUMSLATEBLUE = Color(123, 104, 238);
const Color Color::MEDIUMSPRINGGREEN = Color(0, 250, 154);
const Color Color::MEDIUMTURQUOISE = Color(72, 209, 204);
const Color Color::MEDIUMVIOLETRED = Color(199, 21, 133);
const Color Color::MIDNIGHTBLUE = Color(25, 25, 112);
const Color Color::MINTCREAM = Color(245, 255, 250);
const Color Color::MISTYROSE = Color(255, 228, 225);
const Color Color::MOCCASIN = Color(255, 228, 181);
const Color Color::NAVAJOWHITE = Color(255, 222, 173);
const Color Color::NAVY = Color(0, 0, 128);
const Color Color::OLDLACE = Color(253, 245, 230);
const Color Color::OLIVE = Color(128, 128, 0);
const Color Color::OLIVEDRAB = Color(107, 142, 35);
const Color Color::ORANGE = Color(255, 165, 0);
const Color Color::ORANGERED = Color(255, 69, 0);
const Color Color::ORCHID = Color(218, 112, 214);
const Color Color::PALEGOLDENROD = Color(238, 232, 170);
const Color Color::PALEGREEN = Color(152, 251, 152);
const Color Color::PALETURQUOISE = Color(175, 238, 238);
const Color Color::PALEVIOLETRED = Color(219, 112, 147);
const Color Color::PAPAYAWHIP = Color(255, 239, 213);
const Color Color::PEACHPUFF = Color(255, 218, 185);
const Color Color::PERU = Color(205, 133, 63);
const Color Color::PINK = Color(255, 192, 203);
const Color Color::PLUM = Color(221, 160, 221);
const Color Color::POWDERBLUE = Color(176, 224, 230);
const Color Color::PURPLE = Color(128, 0, 128);
const Color Color::RED = Color(255, 0, 0);
const Color Color::ROSYBROWN = Color(188, 143, 143);
const Color Color::ROYALBLUE = Color(65, 105, 225);
const Color Color::SADDLEBROWN = Color(139, 69, 19);
const Color Color::SALMON = Color(250, 128, 114);
const Color Color::SANDYBROWN = Color(244, 164, 96);
const Color Color::SEAGREEN = Color(46, 139, 87);
const Color Color::SEASHELL = Color(255, 245, 238);
const Color Color::SIENNA = Color(160, 82, 45);
const Color Color::SILVER = Color(192, 192, 192);
const Color Color::SKYBLUE = Color(135, 206, 235);
const Color Color::SLATEBLUE = Color(106, 90, 205);
const Color Color::SLATEGRAY = Color(112, 128, 144);
const Color Color::SNOW = Color(255, 250, 250);
const Color Color::SPRINGGREEN = Color(0, 255, 127);
const Color Color::STEELBLUE = Color(70, 130, 180);
const Color Color::TAN = Color(210, 180, 140);
const Color Color::TEAL = Color(0, 128, 128);
const Color Color::THISTLE = Color(216, 191, 216);
const Color Color::TOMATO = Color(255, 99, 71);
const Color Color::TURQUOISE = Color(64, 224, 208);
const Color Color::VIOLET = Color(238, 130, 238);
const Color Color::WHEAT = Color(245, 222, 179);
const Color Color::WHITE = Color(255, 255, 255);
const Color Color::WHITESMOKE = Color(245, 245, 245);
const Color Color::YELLOW = Color(255, 255, 0);
const Color Color::YELLOWGREEN = Color(154, 205, 50);
