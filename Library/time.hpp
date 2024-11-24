

// TIME 2.3.6


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
#include <stdint.h>


// Preprocessor Directives
#pragma once


// Class Time
class Time
{
public:

   // Class Exception
   class Exception;

   // Get Days of Month
   static uint8_t days(uint16_t year, uint8_t month);

   // Check if Leap Year
   static bool leap(uint16_t year);

   // Check if valid
   static bool valid(uint16_t year, uint8_t month, uint8_t day, uint8_t hour = 0, uint8_t minute = 0,
      uint8_t second = 0, uint16_t milli = 0);

   // Constructor
   Time(void);
   Time(int64_t time);
   Time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour = 0, uint8_t minute = 0, uint8_t second = 0,
      uint16_t milli = 0);

   // Convert to Time Stamp
   operator int64_t(void) const;

   // Compare
   bool operator ==(const Time& time) const;
   bool operator !=(const Time& time) const;
   bool operator <(const Time& time) const;
   bool operator <=(const Time& time) const;
   bool operator >(const Time& time) const;
   bool operator >=(const Time& time) const;

   // Assign
   Time& operator =(int64_t time);

   // Increment
   Time& operator +=(int64_t time);

   // Decrement
   Time& operator -=(int64_t time);

   // Day
   uint8_t day(void) const;
   void day(uint8_t day);

   // Hour
   uint8_t hour(void) const;
   void hour(uint8_t hour);

   // Milli-Second
   uint16_t milli(void) const;
   void milli(uint16_t milli);

   // Minute
   uint8_t minute(void) const;
   void minute(uint8_t minute);

   // Month
   uint8_t month(void) const;
   void month(uint8_t month);

   // Second
   uint8_t second(void) const;
   void second(uint8_t second);

   // Year
   uint16_t year(void) const;
   void year(uint16_t year);

private:

   // Compare
   int8_t _compare(const Time& time) const;

   // Time Stamp
   int64_t _time(void) const;
   void _time(int64_t time);

   // Variables
   uint8_t _day;
   uint8_t _hour;
   uint8_t _minute;
   uint8_t _month;
   uint8_t _second;
   uint16_t _milli;
   uint16_t _year;
};


// Class Exception
class Time::Exception
{
public:

   // Class Parameter
   class Parameter;

private:

   // Virtual Function for RTTI
   virtual void _func() {}
};


// Class Parameter
class Time::Exception::Parameter : public Time::Exception
{
};
