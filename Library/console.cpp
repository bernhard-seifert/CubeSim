

// CONSOLE 1.0.0


// Includes
#include <console.hpp>


// Colors
const uint8_t Console::COLOR_BLACK;
const uint8_t Console::COLOR_BLUE;
const uint8_t Console::COLOR_GREEN;
const uint8_t Console::COLOR_CYAN;
const uint8_t Console::COLOR_RED;
const uint8_t Console::COLOR_MAGENTA;
const uint8_t Console::COLOR_BROWN;
const uint8_t Console::COLOR_LIGHT_GRAY;
const uint8_t Console::COLOR_DARK_GRAY;
const uint8_t Console::COLOR_LIGHT_BLUE;
const uint8_t Console::COLOR_LIGHT_GREEN;
const uint8_t Console::COLOR_LIGHT_CYAN;
const uint8_t Console::COLOR_LIGHT_RED;
const uint8_t Console::COLOR_LIGHT_MAGENTA;
const uint8_t Console::COLOR_YELLOW;
const uint8_t Console::COLOR_WHITE;


// Set Background Color
void Console::background(uint8_t background)
{
   // Check Background Color
   if (15 < background)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Background Color
   if (!SetConsoleTextAttribute(_handle(), (background << 4) | color()))
   {
      // Exception
      throw Exception::Failed();
   }
}


// Set Text Color
void Console::color(uint8_t color)
{
   // Check Text Color
   if (15 < color)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Text Color
   if (!SetConsoleTextAttribute(_handle(), (background() << 4) | color))
   {
      // Exception
      throw Exception::Failed();
   }
}


// Set Cursor Position
void Console::position(const Point& position)
{
   // Get Size
   Size size = Console::size();

   // Check Column and Row
   if ((size.width() <= position.x()) || (size.height() <= position.y()))
   {
      // Exception
      throw Exception::Parameter();
   }

   // Cursor Coordinates
   COORD coord;

   // Set Cursor Coordinates
   coord.X = position.x();
   coord.Y = position.y();

   // Set Console Cursor Position
   if (!SetConsoleCursorPosition(_handle(), coord))
   {
      // Exception
      throw Exception::Failed();
   }
}


// Get Console Handle
inline const HANDLE Console::_handle(void)
{
   // Handle
   static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

   // Return Handle
   return handle;
}


// Get Console Screen Buffer Info
const CONSOLE_SCREEN_BUFFER_INFO Console::_info(void)
{
   // Console Screen Buffer Info
   CONSOLE_SCREEN_BUFFER_INFO info;

   // Get Console Screen Buffer Info
   if (!GetConsoleScreenBufferInfo(_handle(), &info))
   {
      // Exception
      throw Exception::Failed();
   }

   // Return Console Screen Buffer Info
   return info;
}
