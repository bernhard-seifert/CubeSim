

// ADCS - SUN


// Includes
#include "rotation.hpp"


// Preprocessor Directives
#pragma once


// Namespace ADCS
namespace ADCS
{
   // Class Sun
   class Sun;
}


// Class Sun
class ADCS::Sun
{
public:

   // Albedo [W/m^2]
   static const numeric_t& albedo(void);
   static const numeric_t albedo(const Rotation& spacecraft_rotation);

   // Compute Direction (Unit Vector, Body Frame)
   static const Vector direction(void);
   static const Vector direction(const Rotation& spacecraft_rotation, const numeric_t& albedo);

   // Predict Direction (Unit Vector, ECI Frame)
   static const Vector predict_direction(void);

private:

   // Number of Sensors
   static const uint8_t _SENSORS = 6;

   // Variables
   static numeric_t _albedo;

   // Friends
   friend class Spacecraft;
};


// Get Albedo [W/m^2]
inline const ADCS::numeric_t& ADCS::Sun::albedo(void)
{
   // Return Albedo
   return _albedo;
}


// Compute Direction (Unit Vector, Body Frame)
inline const ADCS::Vector ADCS::Sun::direction(void)
{
   // Compute and return Direction
   return direction(Rotation(), NUM(0.0));
}
