

// ADCS - ORBIT


// Includes
#include "rotation.hpp"


// Preprocessor Directives
#pragma once


// Namespace ADCS
namespace ADCS
{
   // Class Orbit
   class Orbit;
}


// Class Orbit
class ADCS::Orbit
{
public:

   // Constructor
   Orbit(void);
   Orbit(const numeric_t& central_mass, const Vector& position, const Vector& velocity, const double& time);
   Orbit(const numeric_t& central_mass, const numeric_t& semimajor_axis, const numeric_t& eccentricity,
      const numeric_t& argument_periapsis, const numeric_t& longitude_ascending, const numeric_t& inclination,
      const numeric_t& mean_anomaly, const double& time);

   // Get Apoapsis
   const numeric_t& apoapsis(void) const;

   // Get Argument of Periapsis
   const numeric_t& argument_periapsis(void) const;

   // Get central Body Mass
   const numeric_t& central_mass(void) const;

   // Get eccentric Anomaly
   const numeric_t& eccentric_anomaly(void) const;

   // Get Eccentricity
   const numeric_t& eccentricity(void) const;

   // Get Epoch
   const double& epoch(void) const;

   // Get Inclination
   const numeric_t& inclination(void) const;

   // Get Longitude of the ascending Node
   const numeric_t& longitude_ascending(void) const;

   // Get mean Anomaly
   const numeric_t& mean_anomaly(void) const;

   // Get Periapsis
   const numeric_t& periapsis(void) const;

   // Get Period
   const numeric_t& period(void) const;

   // Get Position
   const Vector& position(void) const;

   // Get Semi-major Axis
   const numeric_t& semimajor_axis(void) const;

   // Time [s]
   const double& time(void) const;
   void time(const double& time);

   // Get true Anomaly
   const numeric_t& true_anomaly(void) const;

   // Get Velocity
   const Vector& velocity(void) const;

private:

   // Invalidate
   void _invalidate(void);

   // Variables
   double _epoch;
   double _time;
   numeric_t _apoapsis;
   numeric_t _argument_periapsis;
   numeric_t _central_mass;
   numeric_t _eccentric_anomaly;
   numeric_t _eccentricity;
   numeric_t _inclination;
   numeric_t _longitude_ascending;
   numeric_t _mean_anomaly;
   numeric_t _periapsis;
   numeric_t _period;
   numeric_t _semimajor_axis;
   numeric_t _true_anomaly;
   Vector _position;
   Vector _velocity;
   Rotation _rotation;
};


// Constructor
inline ADCS::Orbit::Orbit(void)
{
   // Invalidate
   _invalidate();
}


// Get Apoapsis
inline const ADCS::numeric_t& ADCS::Orbit::apoapsis(void) const
{
   // Return Apoapsis
   return _apoapsis;
}


// Get Argument of Periapsis
inline const ADCS::numeric_t& ADCS::Orbit::argument_periapsis(void) const
{
   // Return Argument of Periapsis
   return _argument_periapsis;
}


// Get central Body Mass
inline const ADCS::numeric_t& ADCS::Orbit::central_mass(void) const
{
   // Return central Body Mass
   return _central_mass;
}


// Get eccentric Anomaly
inline const ADCS::numeric_t& ADCS::Orbit::eccentric_anomaly(void) const
{
   // Return eccentric Anomaly
   return _eccentric_anomaly;
}


// Get Eccentricity
inline const ADCS::numeric_t& ADCS::Orbit::eccentricity(void) const
{
   // Return Eccentricity
   return _eccentricity;
}


// Get Epoch
inline const double& ADCS::Orbit::epoch(void) const
{
   // Return Epoch
   return _epoch;
}


// Get Inclination
inline const ADCS::numeric_t& ADCS::Orbit::inclination(void) const
{
   // Return Inclination
   return _inclination;
}


// Get Longitude of the ascending Node
inline const ADCS::numeric_t& ADCS::Orbit::longitude_ascending(void) const
{
   // Return Longitude of the ascending Node
   return _longitude_ascending;
}


// Get mean Anomaly
inline const ADCS::numeric_t& ADCS::Orbit::mean_anomaly(void) const
{
   // Return mean Anomaly
   return _mean_anomaly;
}


// Get Periapsis
inline const ADCS::numeric_t& ADCS::Orbit::periapsis(void) const
{
   // Return Periapsis
   return _periapsis;
}


// Get Period
inline const ADCS::numeric_t& ADCS::Orbit::period(void) const
{
   // Return Period
   return _period;
}


// Get Position
inline const ADCS::Vector& ADCS::Orbit::position(void) const
{
   // Return Position
   return _position;
}


// Get Semi-major Axis
inline const ADCS::numeric_t& ADCS::Orbit::semimajor_axis(void) const
{
   // Return Semi-major Axis
   return _semimajor_axis;
}


// Get Time [s]
inline const double& ADCS::Orbit::time(void) const
{
   // Return Time
   return _time;
}


// Get true Anomaly
inline const ADCS::numeric_t& ADCS::Orbit::true_anomaly(void) const
{
   // Return true Anomaly
   return _true_anomaly;
}


// Get Velocity
inline const ADCS::Vector& ADCS::Orbit::velocity(void) const
{
   // Return Velocity
   return _velocity;
}
