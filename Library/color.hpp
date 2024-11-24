

// COLOR 1.0.2


// Copyright (c) 2022 Bernhard Seifert
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sub-license, and / or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
// Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
// OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


// Includes
#include <string>
#include <stdint.h>


// Preprocessor Directives
#pragma once


// Class Color
class Color
{
public:

   // Default Colors
   static const Color ALICEBLUE;
   static const Color ANTIQUEWHITE;
   static const Color AQUA;
   static const Color AQUAMARINE;
   static const Color AZURE;
   static const Color BEIGE;
   static const Color BISQUE;
   static const Color BLACK;
   static const Color BLANCHEDALMOND;
   static const Color BLUE;
   static const Color BLUEVIOLET;
   static const Color BROWN;
   static const Color BURLYWOOD;
   static const Color CADETBLUE;
   static const Color CHARTREUSE;
   static const Color CHOCOLATE;
   static const Color CORAL;
   static const Color CORNFLOWERBLUE;
   static const Color CORNSILK;
   static const Color CRIMSON;
   static const Color CYAN;
   static const Color DARKBLUE;
   static const Color DARKCYAN;
   static const Color DARKGOLDENROD;
   static const Color DARKGRAY;
   static const Color DARKGREEN;
   static const Color DARKKHAKI;
   static const Color DARKMAGENTA;
   static const Color DARKOLIVEGREEN;
   static const Color DARKORANGE;
   static const Color DARKORCHID;
   static const Color DARKRED;
   static const Color DARKSALMON;
   static const Color DARKSEAGREEN;
   static const Color DARKSLATEBLUE;
   static const Color DARKSLATEGRAY;
   static const Color DARKTURQUOISE;
   static const Color DARKVIOLET;
   static const Color DEEPPINK;
   static const Color DEEPSKYBLUE;
   static const Color DIMGRAY;
   static const Color DODGERBLUE;
   static const Color FIREBRICK;
   static const Color FLORALWHITE;
   static const Color FORESTGREEN;
   static const Color FUCHSIA;
   static const Color GAINSBORO;
   static const Color GHOSTWHITE;
   static const Color GOLD;
   static const Color GOLDENROD;
   static const Color GRAY;
   static const Color GREEN;
   static const Color GREENYELLOW;
   static const Color HONEYDEW;
   static const Color HOTPINK;
   static const Color INDIANRED;
   static const Color INDIGO;
   static const Color IVORY;
   static const Color KHAKI;
   static const Color LAVENDER;
   static const Color LAVENDERBLUSH;
   static const Color LAWNGREEN;
   static const Color LEMONCHIFFON;
   static const Color LIGHTBLUE;
   static const Color LIGHTCORAL;
   static const Color LIGHTCYAN;
   static const Color LIGHTGOLDENRODYELLOW;
   static const Color LIGHTGRAY;
   static const Color LIGHTGREEN;
   static const Color LIGHTPINK;
   static const Color LIGHTSALMON;
   static const Color LIGHTSEAGREEN;
   static const Color LIGHTSKYBLUE;
   static const Color LIGHTSLATEGRAY;
   static const Color LIGHTSTEELBLUE;
   static const Color LIGHTYELLOW;
   static const Color LIME;
   static const Color LIMEGREEN;
   static const Color LINEN;
   static const Color MAGENTA;
   static const Color MAROON;
   static const Color MEDIUMAQUAMARINE;
   static const Color MEDIUMBLUE;
   static const Color MEDIUMORCHID;
   static const Color MEDIUMPURPLE;
   static const Color MEDIUMSEAGREEN;
   static const Color MEDIUMSLATEBLUE;
   static const Color MEDIUMSPRINGGREEN;
   static const Color MEDIUMTURQUOISE;
   static const Color MEDIUMVIOLETRED;
   static const Color MIDNIGHTBLUE;
   static const Color MINTCREAM;
   static const Color MISTYROSE;
   static const Color MOCCASIN;
   static const Color NAVAJOWHITE;
   static const Color NAVY;
   static const Color OLDLACE;
   static const Color OLIVE;
   static const Color OLIVEDRAB;
   static const Color ORANGE;
   static const Color ORANGERED;
   static const Color ORCHID;
   static const Color PALEGOLDENROD;
   static const Color PALEGREEN;
   static const Color PALETURQUOISE;
   static const Color PALEVIOLETRED;
   static const Color PAPAYAWHIP;
   static const Color PEACHPUFF;
   static const Color PERU;
   static const Color PINK;
   static const Color PLUM;
   static const Color POWDERBLUE;
   static const Color PURPLE;
   static const Color RED;
   static const Color ROSYBROWN;
   static const Color ROYALBLUE;
   static const Color SADDLEBROWN;
   static const Color SALMON;
   static const Color SANDYBROWN;
   static const Color SEAGREEN;
   static const Color SEASHELL;
   static const Color SIENNA;
   static const Color SILVER;
   static const Color SKYBLUE;
   static const Color SLATEBLUE;
   static const Color SLATEGRAY;
   static const Color SNOW;
   static const Color SPRINGGREEN;
   static const Color STEELBLUE;
   static const Color TAN;
   static const Color TEAL;
   static const Color THISTLE;
   static const Color TOMATO;
   static const Color TURQUOISE;
   static const Color VIOLET;
   static const Color WHEAT;
   static const Color WHITE;
   static const Color WHITESMOKE;
   static const Color YELLOW;
   static const Color YELLOWGREEN;

   // Constructor
   Color(void);
   Color(uint8_t red, uint8_t green, uint8_t blue);

   // Convert to String
   operator const std::string(void) const;

   // Blue
   uint8_t blue(void) const;
   void blue(uint8_t blue);

   // Green
   uint8_t green(void) const;
   void green(uint8_t green);

   // Red
   uint8_t red(void) const;
   void red(uint8_t red);

private:

   // Variables
   uint8_t _blue;
   uint8_t _green;
   uint8_t _red;
};


// Constructor
inline Color::Color(void) : _blue(), _green(), _red()
{
}


// Constructor
inline Color::Color(uint8_t red, uint8_t green, uint8_t blue) : _blue(blue), _green(green), _red(red)
{
}


// Get Blue
inline uint8_t Color::blue(void) const
{
   // Return Blue
   return _blue;
}


// Set Blue
inline void Color::blue(uint8_t blue)
{
   // Set Blue
   _blue = blue;
}


// Get Green
inline uint8_t Color::green(void) const
{
   // Return Green
   return _green;
}


// Set Green
inline void Color::green(uint8_t green)
{
   // Set Green
   _green = green;
}


// Get Red
inline uint8_t Color::red(void) const
{
   // Return Red
   return _red;
}


// Set Red
inline void Color::red(uint8_t red)
{
   // Set Red
   _red = red;
}
