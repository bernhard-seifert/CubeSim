

// ADCS - OPERATION


// Includes
#include "info.hpp"
#include "task.hpp"
#include "vector.hpp"


// Preprocessor Directives
#pragma once


// Namespace ADCS
namespace ADCS
{
   // Class Operation
   class Operation;
}


// Class Operation
class ADCS::Operation
{
public:

   // Status
   static const uint8_t STATUS_DISABLED = 0;
   static const uint8_t STATUS_DETUMBLING = 1;
   static const uint8_t STATUS_CONTROL = 2;

   // South Atlantic Anomaly
   static const uint8_t SAA_UNKNOWN = 0;
   static const uint8_t SAA_INSIDE = 1;
   static const uint8_t SAA_OUTSIDE = 2;

   // Disable
   static void disable(void);

   // Enable
   static void enable(void);

   // Get Info
   static const Info& info(void);

   // Get Status
   static uint8_t status(void);

   // Check if inside South Atlantic Anomaly
   static uint8_t SAA(void);

private:

   // South Atlantic Anomaly Limits
   static float _SAA_LATITUDE_MIN;
   static float _SAA_LATITUDE_MAX;
   static float _SAA_LONGITUDE_MIN;
   static float _SAA_LONGITUDE_MAX;

   // Variables
   static bool _enable;
   static Info _info;
   static uint8_t _status;

   // Friends
   friend class Spacecraft;
   friend void ADCS::task(void);
};


// Disable
inline void ADCS::Operation::disable(void)
{
   // Update Enable Flag
   _enable = false;
}


// Enable
inline void ADCS::Operation::enable(void)
{
   // Update Enable Flag
   _enable = true;
}


// Get Status
inline uint8_t ADCS::Operation::status(void)
{
   // Return Status
   return _status;
}
