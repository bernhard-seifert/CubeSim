

// ADCS - STATUS


// Includes
#include <stdint.h>


// Preprocessor Directives
#pragma once


// Namespace ADCS
namespace ADCS
{
   // Class Status
   class Status;
}


// Class Status
class ADCS::Status
{
public:

   // Modes
   static const uint8_t MODE_DISABLED = 0;
   static const uint8_t MODE_DETUMBLE = 1;
   static const uint8_t MODE_CONTROL = 2;

private:

   // Variables
   static uint8_t _mode;
   static float _sensor_angle;

   // Friends
   friend class Spacecraft;
   friend void task(void);
};
