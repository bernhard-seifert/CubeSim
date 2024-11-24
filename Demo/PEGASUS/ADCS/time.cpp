

// ADCS - TIME


// Includes
#include <algorithm>
#include "time.hpp"


// Get Days of Month
uint8_t ADCS::Time::days(uint16_t year, uint8_t month)
{
   // Days of Month
   uint8_t days = 0;

   // Check Month
   if (month == 2)
   {
      // Check if Leap Year
      days = leap(year) ? 29 : 28;
   }
   else if ((month == 4) || (month == 6) || (month == 9) || (month == 11))
   {
      // Set Days of Month
      days = 30;
   }
   else if ((1 <= month) && (month <= 12))
   {
      // Set Days of Month
      days = 31;
   }

   // Return Days of Month
   return days;
}


// Check if Leap Year
bool ADCS::Time::leap(uint16_t year)
{
   // Return Result
   return ((!(year % 4) && (year % 100)) || !(year % 400));
}


// Check if valid
bool ADCS::Time::valid(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second,
   uint16_t milli)
{
   // Return Result
   return ((1 <= month) && (month <= 12) && (1 <= day) && (hour <= 23) && (minute <= 59) && (second <= 59) &&
      (milli <= 999) && (day <= days(year, month)));
}


// Constructor
ADCS::Time::Time(void) : _day(1), _hour(), _minute(), _month(1), _second(), _milli(), _year()
{
}


// Constructor
ADCS::Time::Time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second,
   uint16_t milli)
{
   // Check if valid
   if (valid(year, month, day, hour, minute, second, milli))
   {
      // Initialize
      _year = year;
      _month = month;
      _day = day;
      _hour = hour;
      _minute = minute;
      _second = second;
      _milli = milli;
   }
   else
   {
      // Initialize
      _year = 0;
      _month = 1;
      _day = 1;
      _hour = 0;
      _minute = 0;
      _second = 0;
      _milli = 0;
   }
}


// Assign
ADCS::Time& ADCS::Time::operator =(int64_t time)
{
   // Set Time
   _time(time);

   // Return Reference
   return *this;
}


// Increment
ADCS::Time& ADCS::Time::operator +=(int64_t time)
{
   // Set Time
   _time(*this + time);

   // Return Reference
   return *this;
}


// Decrement
ADCS::Time& ADCS::Time::operator -=(int64_t time)
{
   // Set Time
   _time(*this - time);

   // Return Reference
   return *this;
}


// Set Day
bool ADCS::Time::day(uint8_t day)
{
   // Check if valid
   if (!valid(_year, _month, day))
   {
      // Error
      return false;
   }

   // Set Day
   _day = day;

   // Return
   return true;
}


// Set Month
bool ADCS::Time::month(uint8_t month)
{
   // Check if valid
   if (!valid(_year, month, _day))
   {
      // Error
      return false;
   }

   // Set Month
   _month = month;

   // Return
   return true;
}


// Set Year
bool ADCS::Time::year(uint16_t year)
{
   // Check if valid
   if (!valid(year, _month, _day))
   {
      // Error
      return false;
   }

   // Set Year
   _year = year;

   // Return
   return true;
}


// Compare
int8_t ADCS::Time::_compare(const Time& time) const
{
   // Check Year
   if (_year == time._year)
   {
      // Check Month
      if (_month == time._month)
      {
         // Check Day
         if (_day == time._day)
         {
            // Check Hour
            if (_hour == time._hour)
            {
               // Check Minute
               if (_minute == time._minute)
               {
                  // Check Second
                  if (_second == time._second)
                  {
                     // Check Milli-Second
                     if (_milli == time._milli)
                     {
                        // Return Result
                        return 0;
                     }
                     else if (_milli < time._milli)
                     {
                        // Return Result
                        return -1;
                     }
                  }
                  else if (_second < time._second)
                  {
                     // Return Result
                     return -1;
                  }
               }
               else if (_minute < time._minute)
               {
                  // Return Result
                  return -1;
               }
            }
            else if (_hour < time._hour)
            {
               // Return Result
               return -1;
            }
                  }
         else if (_day < time._day)
         {
            // Return Result
            return -1;
         }
      }
      else if (_month < time._month)
      {
         // Return Result
         return -1;
      }
   }
   else if (_year < time._year)
   {
      // Return Result
      return -1;
   }

   // Return Result
   return +1;
}


// Get Time Stamp
int64_t ADCS::Time::_time(void) const
{
   // Time, Year
   int64_t time = 0;
   uint16_t year = 0;

   // Check Year
   if (2000 <= _year)
   {
      // Update Time Stamp and Year
      time += 730485L;
      year = 2000;
   }

   // Parse Years and update Time Stamp
   for (; year < _year; time += (leap(year++) ? 366 : 365));

   // Parse Months and update Time Stamp
   for (uint8_t month = 1; month < _month; time += days(_year, month++));

   // Update Time Stamp
   time = ((((time + _day - 1) * 24 + _hour) * 60 + _minute) * 60 + _second) * 1000 + _milli;

   // Return Time Stamp
   return time;
}


// Set Time Stamp
void ADCS::Time::_time(int64_t time)
{
   // Limit Time Stamp
   time = std::min(std::max(time, static_cast<int64_t>(0)), static_cast<int64_t>(2068116364799999LL));

   // Set Milli-Second
   _milli = static_cast<uint16_t>(time % 1000);
   time /= 1000;

   // Set Second
   _second = static_cast<uint8_t>(time % 60);
   time /= 60;

   // Set Minute
   _minute = static_cast<uint8_t>(time % 60);
   time /= 60;

   // Set Hour
   _hour = static_cast<uint8_t>(time % 24);
   time /= 24;

   // Check Time Stamp
   if (730485L <= time)
   {
      // Update Time Stamp and set Year
      time -= 730485L;
      _year = 2000;
   }
   else
   {
      // Set Year
      _year = 0;
   }

   // Parse Years
   for (;; ++_year)
   {
      // Get Days of Month
      uint16_t days = leap(_year) ? 366 : 365;

      // Check Time Stamp
      if (time < days)
      {
         // Break
         break;
      }

      // Update Time Stamp
      time -= days;
   }

   // Parse Months
   for (_month = 1; ; ++_month)
   {
      // Get Days of Month
      uint16_t days = Time::days(_year, _month);

      // Check Time Stamp
      if (time < days)
      {
         // Break
         break;
      }

      // Update Time Stamp
      time -= days;
   }

   // Set Day
   _day = static_cast<uint8_t>(time) + 1;
}
