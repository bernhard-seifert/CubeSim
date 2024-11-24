

// ADCS - FLOAT16


// Includes
#include <limits>
#include "float16.h"


// Convert Half-Precision Float to Single-Precision Float
float float16_float(float16_t x)
{
   // Get Sign, Exponent, Mantissa
   uint16_t s = x & 0x8000;
   uint16_t e = x & 0x7C00;
   uint16_t m = x & 0x03FF;

   // Check Exponent
   if (e == 0x7C00)
   {
      // Check Mantissa and Sign
      if (m)
      {
         // Return NaN
         return std::numeric_limits<float>::quiet_NaN();
      }
      else if (s)
      {
         // Return -Infinity
         return -std::numeric_limits<float>::infinity();
      }
      else
      {
         // Return +Infinity
         return std::numeric_limits<float>::infinity();
      }
   }

   // Compute Value
   uint32_t y = (static_cast<uint32_t>(s) << 16) + (static_cast<uint32_t>(e + m) << 13) + 0x38000000;

   // Return Value
   return *reinterpret_cast<float*>(&y);
}


// Convert Single-Precision Float to Half-Precision Float
float16_t float_float16(const float& x)
{
   // Get Sign, Exponent, Mantissa
   uint32_t s = *reinterpret_cast<const uint32_t*>(&x) & 0x80000000;
   uint32_t e = *reinterpret_cast<const uint32_t*>(&x) & 0x7F800000;
   uint32_t m = *reinterpret_cast<const uint32_t*>(&x) & 0x007FFFFF;

   // Check Exponent
   if (e == 0x7F800000)
   {
      // Check Mantissa and Sign
      if (m)
      {
         // Return NaN
         return 0x7C01;
      }
      else if (s)
      {
         // Return -Infinity
         return 0xFC00;
      }
      else
      {
         // Return +Infinity
         return 0x7C00;
      }
   }
   else if (0x47000000 < e)
   {
      // Check Sign
      if (s)
      {
         // Return -Infinity
         return 0xFC00;
      }
      else
      {
         // Return +Infinity
         return 0x7C00;
      }
   }
   else if (e < 0x38000000)
   {
      // Compute and return Value
      return (s >> 16);
   }

   // Compute and return Value
   return ((s >> 16) + ((e + m - 0x38000000) >> 13));
}
