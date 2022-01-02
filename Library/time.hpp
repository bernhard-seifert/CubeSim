

// TIME 2.3.5


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
