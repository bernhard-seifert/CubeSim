

// CUBESIM - SYSTEM - GNSS


// Includes
#include "gnss.hpp"
#include "../simulation.hpp"


// Get Location
const CubeSim::Location CubeSim::System::GNSS::location(void) const
{
   // Check Earth
   if (!_earth)
   {
      // Check Simulation
      if (!simulation())
      {
         // Exception
         throw Exception::Failed();
      }

      // Parse Celestial Body List
      for (auto celestial_body = simulation()->celestial_body().begin(); celestial_body !=
         simulation()->celestial_body().end(); ++celestial_body)
      {
         // Check Celestial Body
         if (dynamic_cast<CelestialBody::Earth*>(celestial_body->second))
         {
            // Set Earth
            _earth = celestial_body->second;
            break;
         }
      }

      // Check Earth
      if (!_earth)
      {
         // Exception
         throw Exception::Failed();
      }
   }

   // Check if enabled
   if (!is_enabled())
   {
      // Return invalid Location
      return Location(*_earth, NAN, NAN, NAN);
   }

   // Get Spacecraft Position (ECEF Frame)
   Vector3D position = spacecraft()->position() - _earth->position() - _earth->rotation();

   // Consider spatial Accuracy
   position.x(position.x() + _distribution(_generator) * _spatial_accuracy_ / sqrt(3.0));
   position.y(position.y() + _distribution(_generator) * _spatial_accuracy_ / sqrt(3.0));
   position.z(position.z() + _distribution(_generator) * _spatial_accuracy_ / sqrt(3.0));

   // Get Time (consider temporal Accuracy)
   Time time = simulation()->time() + static_cast<int64_t>(_distribution(_generator) * _temporal_accuracy_ * 1000.0);

   // Return Location (ECEF Frame)
   return Location(*_earth, position, time);
}


// Default spatial Accuracy [m]
const double CubeSim::System::GNSS::_SPATIAL_ACCURACY = 0.0;

// Default temporal Accuracy [s]
const double CubeSim::System::GNSS::_TEMPORAL_ACCURACY = 0.0;
