

// CONSOLE 1.0.0


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
#include <utility>
#include <stdint.h>
#include <windows.h>


// Preprocessor Directives
#pragma once


// Class Console
class Console
{
public:

   // Class Exception
   class Exception;

   // Class Point
   class Point;

   // Class Size
   class Size;

   // Colors
   static const uint8_t COLOR_BLACK = 0;
   static const uint8_t COLOR_BLUE = 1;
   static const uint8_t COLOR_GREEN = 2;
   static const uint8_t COLOR_CYAN = 3;
   static const uint8_t COLOR_RED = 4;
   static const uint8_t COLOR_MAGENTA = 5;
   static const uint8_t COLOR_BROWN = 6;
   static const uint8_t COLOR_LIGHT_GRAY = 7;
   static const uint8_t COLOR_DARK_GRAY = 8;
   static const uint8_t COLOR_LIGHT_BLUE = 9;
   static const uint8_t COLOR_LIGHT_GREEN = 10;
   static const uint8_t COLOR_LIGHT_CYAN = 11;
   static const uint8_t COLOR_LIGHT_RED = 12;
   static const uint8_t COLOR_LIGHT_MAGENTA = 13;
   static const uint8_t COLOR_YELLOW = 14;
   static const uint8_t COLOR_WHITE = 15;

   // Background Color
   static uint8_t background(void);
   static void background(uint8_t background);

   // Text Color
   static uint8_t color(void);
   static void color(uint8_t color);

   // Cursor Position
   static const Point position(void);
   static void position(uint8_t x, uint8_t y);
   static void position(const Point& position);

   // Get Size
   static const Size size(void);

private:

   // Get Console Handle
   static const HANDLE _handle(void);

   // Get Console Screen Buffer Info
   static const CONSOLE_SCREEN_BUFFER_INFO _info(void);
};


// Class Exception
class Console::Exception
{
public:

   // Class Failed
   class Failed;

   // Class Parameter
   class Parameter;

private:

   // Virtual Function for RTTI
   virtual void _func() {}
};


// Class Point
class Console::Point
{
public:

   // Constructor
   Point(void);
   Point(uint8_t x, uint8_t y);

   // Compare
   bool operator ==(const Point& point) const;
   bool operator !=(const Point& point) const;

   // X Coordinate
   uint8_t x(void) const;
   void x(uint8_t x);

   // Y Coordinate
   uint8_t y(void) const;
   void y(uint8_t y);

private:

   // Variables
   uint8_t _x;
   uint8_t _y;
};


// Class Size
class Console::Size
{
public:

   // Constructor
   Size(void);
   Size(uint8_t width, uint8_t height);

   // Compare
   bool operator ==(const Size& size) const;
   bool operator !=(const Size& size) const;

   // Height
   uint8_t height(void) const;
   void height(uint8_t height);

   // Width
   uint8_t width(void) const;
   void width(uint8_t width);

private:

   // Variables
   uint8_t _height;
   uint8_t _width;
};


// Class Failed
class Console::Exception::Failed : public Console::Exception
{
};


// Class Parameter
class Console::Exception::Parameter : public Console::Exception
{
};


// Get Background Color
inline uint8_t Console::background(void)
{
   // Return Background Color
   return static_cast<uint8_t>((_info().wAttributes >> 4) & 0x0F);
}


// Get Text Color
inline uint8_t Console::color(void)
{
   // Return Text Color
   return static_cast<uint8_t>(_info().wAttributes & 0x0F);
}


// Get Cursor Position
inline const Console::Point Console::position(void)
{
   // Get Console Screen Buffer Info
   CONSOLE_SCREEN_BUFFER_INFO info = _info();

   // Return Cursor Position
   return Point(static_cast<uint8_t>(info.dwCursorPosition.X), static_cast<uint8_t>(info.dwCursorPosition.Y));
}


// Set Cursor Position
inline void Console::position(uint8_t x, uint8_t y)
{
   // Set Cursor Position
   position(Point(x, y));
}


// Get Size
inline const Console::Size Console::size(void)
{
   // Get Console Screen Buffer Info
   CONSOLE_SCREEN_BUFFER_INFO info = _info();

   // Return Size
   return Size(static_cast<uint8_t>(info.dwSize.X), static_cast<uint8_t>(info.dwSize.Y));
}


// Constructor
inline Console::Point::Point(void) : _x(), _y()
{
}


// Constructor
inline Console::Point::Point(uint8_t x, uint8_t y)
{
   // Initialize
   this->x(x);
   this->y(y);
}


// Compare
inline bool Console::Point::operator ==(const Point& point) const
{
   // Return Result
   return ((point._x == _x) && (point._y == _y));
}


// Compare
inline bool Console::Point::operator !=(const Point& point) const
{
   // Return Result
   return !(point == *this);
}


// Get X Coordinate
inline uint8_t Console::Point::x(void) const
{
   // Return X Coordinate
   return _x;
}


// Set X Coordinate
inline void Console::Point::x(uint8_t x)
{
   // Set X Coordinate
   _x = x;
}


// Get Y Coordinate
inline uint8_t Console::Point::y(void) const
{
   // Return Y Coordinate
   return _y;
}


// Set Y Coordinate
inline void Console::Point::y(uint8_t y)
{
   // Set Y Coordinate
   _y = y;
}


// Constructor
inline Console::Size::Size(void) : _width(), _height()
{
}


// Constructor
inline Console::Size::Size(uint8_t width, uint8_t height)
{
   // Initialize
   this->width(width);
   this->height(height);
}


// Compare
inline bool Console::Size::operator ==(const Size& size) const
{
   // Return Result
   return ((size._width == _width) && (size._height == _height));
}


// Compare
inline bool Console::Size::operator !=(const Size& size) const
{
   // Return Result
   return !(size == *this);
}


// Get Height
inline uint8_t Console::Size::height(void) const
{
   // Return Height
   return _height;
}


// Set Height
inline void Console::Size::height(uint8_t height)
{
   // Set Height
   _height = height;
}


// Get Width
inline uint8_t Console::Size::width(void) const
{
   // Return Width
   return _width;
}


// Set Width
inline void Console::Size::width(uint8_t width)
{
   // Set Width
   _width = width;
}
