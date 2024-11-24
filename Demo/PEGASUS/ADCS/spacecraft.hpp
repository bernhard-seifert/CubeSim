

// ADCS - SPACECRAFT


// Includes
#include "frame.hpp"
#include "orbit.hpp"
#include "task.hpp"


// Preprocessor Directives
#pragma once


// Namespace ADCS
namespace ADCS
{
   // Class Spacecraft
   class Spacecraft;
}


// Class Spacecraft
class ADCS::Spacecraft
{
public:

   // Compute angular Momentum (Body Frame)
   static const Vector angular_momentum(void);

   // Get angular Rate (Body Frame)
   static const Vector& angular_rate(void);

   // Compute Spacecraft Location (ECEF Frame)
   static const Location location(void);

   // Orbit
   static const Orbit& orbit(void);
   static void orbit(const numeric_t& semimajor_axis, const numeric_t& eccentricity,
      const numeric_t& argument_periapsis, const numeric_t& longitude_ascending, const numeric_t& inclination,
      const numeric_t& mean_anomaly, const double& time);

   // Compute Position (ECI Frame)
   static const Vector& position(void);

   // Get Rotation (ECI Frame)
   static const Rotation& rotation(void);

   // Compute Orientation (LO Frame)
   static const Rotation orientation(void);

   // Update Position and Rotation
   static void update(void);

   // Compute Velocity (ECI Frame)
   static const Vector& velocity(void);

private:

   // Class _Point
   class _Point;

   // Update Position
   static void _update_position(void);

   // Update Rotation
   static void _update_rotation(void);

   // Variables
   static Orbit _orbit;
   static Vector _angular_rate;
   static Rotation _rotation;
   static Rotation _target;
};


// Get angular Rate (Body Frame)
inline const ADCS::Vector& ADCS::Spacecraft::angular_rate(void)
{
   // Return angular Rate
   return _angular_rate;
}


// Compute Spacecraft Location (ECEF Frame)
inline const ADCS::Location ADCS::Spacecraft::location(void)
{
   // Transform into ECEF Frame and return Location
   return Location(Frame::ECI_ECEF(position()));
}


// Get Orbit
inline const ADCS::Orbit& ADCS::Spacecraft::orbit(void)
{
   // Return Orbit
   return _orbit;
}


// Compute Position (ECI Frame)
inline const ADCS::Vector& ADCS::Spacecraft::position(void)
{
   // Compute and return Position
   return _orbit.position();
}


// Compute Rotation (ECI Frame)
inline const ADCS::Rotation& ADCS::Spacecraft::rotation(void)
{
   // Return Rotation
   return _rotation;
}


// Update Position and Rotation
inline void ADCS::Spacecraft::update(void)
{
   // Update Position
   Spacecraft::_update_position();

   // Update Rotation
   Spacecraft::_update_rotation();
}


// Compute Velocity (ECI Frame)
inline const ADCS::Vector& ADCS::Spacecraft::velocity(void)
{
   // Compute and return Velocity
   return _orbit.velocity();
}
