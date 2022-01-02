

// TIME 2.3.5


// Includes
#include <algorithm>
#include <time.hpp>


// Get Days of Month
uint8_t Time::days(uint16_t year, uint8_t month)
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
bool Time::leap(uint16_t year)
{
   // Return Result
   return ((!(year % 4) && (year % 100)) || !(year % 400));
}


// Check if valid
bool Time::valid(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second,
   uint16_t milli)
{
   // Return Result
   return ((1 <= month) && (month <= 12) && (1 <= day) && (hour <= 23) && (minute <= 59) && (second <= 59) &&
      (milli <= 999) && (day <= days(year, month)));
}


// Constructor
Time::Time(void) : _day(1), _hour(), _minute(), _month(1), _second(), _milli(), _year()
{
}


// Constructor
Time::Time(int64_t time)
{
   // Initialize
   _time(time);
}


// Constructor
Time::Time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint16_t milli)
{
   // Check if valid
   if (!valid(year, month, day, hour, minute, second, milli))
   {
      // Exception
      throw Exception::Parameter();
   }

   // Initialize
   _year = year;
   _month = month;
   _day = day;
   _hour = hour;
   _minute = minute;
   _second = second;
   _milli = milli;
}


// Convert to Time Stamp
Time::operator int64_t(void) const
{
   // Return Time Stamp
   return _time();
}


// Compare
bool Time::operator ==(const Time& time) const
{
   // Return Result
   return !_compare(time);
}


// Compare
bool Time::operator !=(const Time& time) const
{
   // Return Result
   return _compare(time);
}


// Compare
bool Time::operator <(const Time& time) const
{
   // Return Result
   return (_compare(time) < 0);
}


// Compare
bool Time::operator <=(const Time& time) const
{
   // Return Result
   return (_compare(time) <= 0);
}


// Compare
bool Time::operator >(const Time& time) const
{
   // Return Result
   return (_compare(time) > 0);
}


// Compare
bool Time::operator >=(const Time& time) const
{
   // Return Result
   return (_compare(time) >= 0);
}


// Assign
Time& Time::operator =(int64_t time)
{
   // Set Time
   _time(time);

   // Return Reference
   return *this;
}


// Increment
Time& Time::operator +=(int64_t time)
{
   // Set Time
   _time(_time() + time);

   // Return Reference
   return *this;
}


// Decrement
Time& Time::operator -=(int64_t time)
{
   // Set Time
   _time(_time() - time);

   // Return Reference
   return *this;
}


// Get Day
uint8_t Time::day(void) const
{
   // Return Day
   return _day;
}


// Set Day
void Time::day(uint8_t day)
{
   // Check if valid
   if (!valid(_year, _month, day))
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Day
   _day = day;
}


// Get Hour
uint8_t Time::hour(void) const
{
   // Return Hour
   return _hour;
}


// Set Hour
void Time::hour(uint8_t hour)
{
   // Check if valid
   if (23 < hour)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Hour
   _hour = hour;
}


// Get Milli-Second
uint16_t Time::milli(void) const
{
   // Return Milli-Second
   return _milli;
}


// Set Milli-Second
void Time::milli(uint16_t milli)
{
   // Check if valid
   if (999 < milli)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Milli-Second
   _milli = milli;
}


// Get Minute
uint8_t Time::minute(void) const
{
   // Return Minute
   return _minute;
}


// Set Minute
void Time::minute(uint8_t minute)
{
   // Check if valid
   if (59 < minute)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Minute
   _minute = minute;
}


// Get Month
uint8_t Time::month(void) const
{
   // Return Month
   return _month;
}


// Set Month
void Time::month(uint8_t month)
{
   // Check if valid
   if (!valid(_year, month, _day))
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Month
   _month = month;
}


// Get Second
uint8_t Time::second(void) const
{
   // Return Second
   return _second;
}


// Set Second
void Time::second(uint8_t second)
{
   // Check if valid
   if (59 < second)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Second
   _second = second;
}


// Get Year
uint16_t Time::year(void) const
{
   // Return Year
   return _year;
}


// Set Year
void Time::year(uint16_t year)
{
   // Check if valid
   if (!valid(year, _month, _day))
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Year
   _year = year;
}


// Compare
int8_t Time::_compare(const Time& time) const
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
   return 1;
}


// Get Time Stamp
int64_t Time::_time(void) const
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
void Time::_time(int64_t time)
{
   // Limit Time Stamp
   time = std::min<int64_t>(std::max<int64_t>(time, 0), 2068116364799999LL);

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
