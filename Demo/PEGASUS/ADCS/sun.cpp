

// ADCS - SUN POSITION


// Includes
#include <algorithm>
#include <vector>
#include "constant.hpp"
#include "interface.hpp"
#include "location.hpp"
#include "spacecraft.hpp"
#include "sun.hpp"


// Compute Albedo [W/m^2]
const ADCS::numeric_t ADCS::Sun::albedo(const Rotation& spacecraft_rotation)
{
   // Get Sun Direction and Spacecraft Position (ECI Frame)
   Vector sun_direction = predict_direction();
   Vector spacecraft_position = Spacecraft::position();

   // Create List of Irradiances
   std::vector<numeric_t> irradiance(_SENSORS);
   irradiance[0] = Interface::irradiance(Interface::SIDE_XM);
   irradiance[1] = Interface::irradiance(Interface::SIDE_XP);
   irradiance[2] = Interface::irradiance(Interface::SIDE_YM);
   irradiance[3] = Interface::irradiance(Interface::SIDE_YP);
   irradiance[4] = Interface::irradiance(Interface::SIDE_ZM);
   irradiance[5] = Interface::irradiance(Interface::SIDE_ZP);

   // Create List of Sensor Directions (Body Frame)
   std::vector<Vector> direction(_SENSORS);
   direction[0] = -Vector::X;
   direction[1] = Vector::X;
   direction[2] = -Vector::Y;
   direction[3] = Vector::Y;
   direction[4] = -Vector::Z;
   direction[5] = Vector::Z;

   // Number of Sensors not pointing towards the Sun but towards Earth, Albedo
   size_t n = 0;
   numeric_t albedo = NUM(0.0);

   // Parse Sensors List
   for (size_t i = 0; i < direction.size(); ++i)
   {
      // Compute Sensor Direction in ECI Frame
      direction[i] += spacecraft_rotation;

      // Compute Angle towards Sun
      numeric_t angle = direction[i] % sun_direction;

      // Check Angle (greater than 110°) to verify it's not exposed to the Sun
      if (DEG_RAD(110.0) <= angle)
      {
         // Compute Angle towards Earth
         angle = direction[i] % -spacecraft_position;

         // Check Angle (less than 90°)
         if (angle <= DEG_RAD(90.0))
         {
            // Update Albedo (Approximation valid for LEO)
            albedo += irradiance[i] * std::exp(angle * angle / NUM(2.1));
            ++n;
         }
      }
   }

   // Check Number of valid Sensors
   if (!n)
   {
      // Return
      return NAN;
   }

   // Compute and return mean Albedo
   return (albedo / n);
}


// Compute Direction (Unit Vector, Body Frame)
const ADCS::Vector ADCS::Sun::direction(const Rotation& spacecraft_rotation, const numeric_t& albedo)
{
   // Create List of Irradiances
   std::vector<numeric_t> irradiance(_SENSORS);
   irradiance[0] = Interface::irradiance(Interface::SIDE_XM);
   irradiance[1] = Interface::irradiance(Interface::SIDE_XP);
   irradiance[2] = Interface::irradiance(Interface::SIDE_YM);
   irradiance[3] = Interface::irradiance(Interface::SIDE_YP);
   irradiance[4] = Interface::irradiance(Interface::SIDE_ZM);
   irradiance[5] = Interface::irradiance(Interface::SIDE_ZP);

   // Create List of Sensor Directions (Body Frame)
   std::vector<Vector> direction(_SENSORS);
   direction[0] = -Vector::X;
   direction[1] = Vector::X;
   direction[2] = -Vector::Y;
   direction[3] = Vector::Y;
   direction[4] = -Vector::Z;
   direction[5] = Vector::Z;

   // Sun Direction (Body Frame)
   Vector direction_;

   // Check Albedo
   if (NUM(0.0) < albedo)
   {
      // Get Spacecraft Position (ECEF Frame)
      Vector spacecraft_position = Spacecraft::position();

      // Parse Sensor List
      for (size_t i = 0; i < direction.size(); ++i)
      {
         // Compute Angle towards Earth
         numeric_t angle = (direction[i] + spacecraft_rotation) % -spacecraft_position;

         // Compensate Albedo and update Sun Direction (Body Frame)
         direction_ += direction[i] * (irradiance[i] - albedo / std::exp(angle * angle / NUM(2.1)));
      }
   }
   else
   {
      // Parse Sensor List
      for (size_t i = 0; i < direction.size(); ++i)
      {
         // Update Sun Direction (Body Frame)
         direction_ += direction[i] * irradiance[i];
      }
   }

   // Check Irradiance to detect Eclipse
   if (direction_.norm() < (Constant::SOLAR_IRRADIANCE / NUM(2.0)))
   {
      // Return
      return Vector(NAN, NAN, NAN);
   }

   // Return Sun Direction (Unity Vector, Body Frame)
   return direction_.unit();
}


// Predict Direction (Unit Vector, ECI Frame)
const ADCS::Vector ADCS::Sun::predict_direction(void)
{
   // Get relative Time of the Year [rad]
   numeric_t time = std::fmod(static_cast<numeric_t>(Interface::time() / Constant::EARTH_YEAR), NUM(1.0)) * NUM(2.0) *
      Constant::PI;

   // Compute Latitude and Longitude (ECI Frame)
   numeric_t latitude = Constant::EARTH_AXIS_TILT * std::cos(time + NUM(3.311924));
   numeric_t longitude = time + NUM(4.882726);

   // Compute and return Sun Direction
    return static_cast<Vector>(Location(latitude, longitude, NUM(0.0))).unit();
}


// Variables
ADCS::numeric_t ADCS::Sun::_albedo;
