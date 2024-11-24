

// TIME 2.1.8


// Includes
#include <stdint.h>


// Preprocessor Directives
#pragma once


// Namespace ADCS
namespace ADCS
{
   // Class Time
   class Time;
}


// Class Time
class ADCS::Time
{
public:

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
   bool day(uint8_t day);

   // Hour
   uint8_t hour(void) const;
   bool hour(uint8_t hour);

   // Milli-Second
   uint16_t milli(void) const;
   bool milli(uint16_t milli);

   // Minute
   uint8_t minute(void) const;
   bool minute(uint8_t minute);

   // Month
   uint8_t month(void) const;
   bool month(uint8_t month);

   // Second
   uint8_t second(void) const;
   bool second(uint8_t second);

   // Year
   uint16_t year(void) const;
   bool year(uint16_t year);

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


// Constructor
inline ADCS::Time::Time(int64_t time)
{
   // Initialize
   _time(time);
}


// Convert to Time Stamp
inline ADCS::Time::operator int64_t(void) const
{
   // Return Time Stamp
   return _time();
}


// Compare
inline bool ADCS::Time::operator ==(const Time& time) const
{
   // Return Result
   return !_compare(time);
}


// Compare
inline bool ADCS::Time::operator !=(const Time& time) const
{
   // Return Result
   return _compare(time);
}


// Compare
inline bool ADCS::Time::operator <(const Time& time) const
{
   // Return Result
   return (_compare(time) < 0);
}


// Compare
inline bool ADCS::Time::operator <=(const Time& time) const
{
   // Return Result
   return (_compare(time) <= 0);
}


// Compare
inline bool ADCS::Time::operator >(const Time& time) const
{
   // Return Result
   return (_compare(time) > 0);
}


// Compare
inline bool ADCS::Time::operator >=(const Time& time) const
{
   // Return Result
   return (_compare(time) >= 0);
}


// Get Day
inline uint8_t ADCS::Time::day(void) const
{
   // Return Day
   return _day;
}


// Get Hour
inline uint8_t ADCS::Time::hour(void) const
{
   // Return Hour
   return _hour;
}


// Set Hour
inline bool ADCS::Time::hour(uint8_t hour)
{
   // Check if valid
   if (23 < hour)
   {
      // Error
      return false;
   }

   // Set Hour
   _hour = hour;

   // Return
   return true;
}


// Get Milli-Second
inline uint16_t ADCS::Time::milli(void) const
{
   // Return Milli-Second
   return _milli;
}


// Set Milli-Second
inline bool ADCS::Time::milli(uint16_t milli)
{
   // Check if valid
   if (999 < milli)
   {
      // Error
      return false;
   }

   // Error
   return true;
}


// Get Minute
inline uint8_t ADCS::Time::minute(void) const
{
   // Return Minute
   return _minute;
}


// Set Minute
inline bool ADCS::Time::minute(uint8_t minute)
{
   // Check if valid
   if (59 < minute)
   {
      // Error
      return false;
   }

   // Set Minute
   _minute = minute;

   // Return
   return true;
}


// Get Month
inline uint8_t ADCS::Time::month(void) const
{
   // Return Month
   return _month;
}


// Get Second
inline uint8_t ADCS::Time::second(void) const
{
   // Return Second
   return _second;
}


// Set Second
inline bool ADCS::Time::second(uint8_t second)
{
   // Check if valid
   if (59 < second)
   {
      // Error
      return false;
   }

   // Set Second
   _second = second;

   // Return
   return true;
}


// Get Year
inline uint16_t ADCS::Time::year(void) const
{
   // Return Year
   return _year;
}
