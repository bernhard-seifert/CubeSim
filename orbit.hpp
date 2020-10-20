

// CUBESIM - ORBIT


// Includes
#include <set>
#include "rigid_body.hpp"
#include "time.hpp"


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class CelestialBody
   class CelestialBody;

   // Class Orbit
   class Orbit;
}


// Class Orbit
class CubeSim::Orbit
{
public:

   // Reference Frames
   static const Rotation REFERENCE_ECLIPTIC;
   static const Rotation REFERENCE_ECI;
   
   // Constructor
   Orbit(double semimajor_axis, double eccentricity, double argument_periapsis, double longitude_ascending,
      double inclination, double mean_anomaly, double period, const Time& time, const Rotation& reference =
      REFERENCE_ECLIPTIC);
   Orbit(const CelestialBody& central, double semimajor_axis, double eccentricity, double argument_periapsis,
      double longitude_ascending, double inclination, double mean_anomaly, const Time& time, const Rotation& reference =
      REFERENCE_ECLIPTIC);
   Orbit(const std::set<const CelestialBody*>& central, double semimajor_axis, double eccentricity,
      double argument_periapsis, double longitude_ascending, double inclination, double mean_anomaly, const Time& time,
      const Rotation& reference = REFERENCE_ECLIPTIC);
   Orbit(const CelestialBody& central, const RigidBody& rigid_body, const Rotation& reference = REFERENCE_ECLIPTIC);
   Orbit(const std::set<const CelestialBody*>& central, const RigidBody& rigid_body, const Rotation& reference =
      REFERENCE_ECLIPTIC);

   // Get Apoapsis [m]
   double apoapsis(void) const;

   // Get Argument of Periapsis [rad]
   double argument_periapsis(void) const;

   // Get eccentric Anomaly [rad]
   double eccentric_anomaly(void) const;

   // Get Eccentricity
   double eccentricity(void) const;

   // Get Epoch
   const Time& epoch(void) const;

   // Get standard gravitational Parameter [m^3/s^2]
   double gravitational_parameter(void) const;

   // Get Inclination [rad]
   double inclination(void) const;

   // Get Longitude of the ascending Node [rad]
   double longitude_ascending(void) const;

   // Get mean Anomaly [rad]
   double mean_anomaly(void) const;

   // Get Periapsis [m]
   double periapsis(void) const;

   // Compute Perimeter (Travel Distance for one Revolution) [m]
   double perimeter(void) const;

   // Get Period [s]
   double period(void) const;

   // Get Position relative to Barycenter [m]
   const Vector3D position(void) const;

   // Reference Frame
   const Rotation& reference(void) const;
   void reference(const Rotation& reference);

   // Get semi-major Axis [m]
   double semimajor_axis(void) const;

   // Time
   const Time& time(void) const;
   void time(const Time& time);

   // Get true Anomaly [rad]
   double true_anomaly(void) const;

   // Get Velocity relative to Barycenter [m/s]
   const Vector3D velocity(void) const;

private:

   // Wrap Angle into [0; 2*pi) Interval
   static double _wrap(double angle);

   // Initialize
   void _init(double gravitational_parameter, double semimajor_axis, double eccentricity, double argument_periapsis,
      double longitude_ascending, double inclination, double mean_anomaly, double period, const Time& time,
      const Rotation& reference);
   
   // Variables
   double _apoapsis;
   double _argument_periapsis;
   double _eccentric_anomaly;
   double _eccentricity;
   double _gravitational_parameter;
   double _inclination;
   double _longitude_ascending;
   double _mean_anomaly;
   double _periapsis;
   double _period;
   double _semimajor_axis;
   double _true_anomaly;
   Time _epoch;
   Time _time_;
   Rotation _reference;
   Rotation _rotation;
};


// Constructor
inline CubeSim::Orbit::Orbit(const CelestialBody& central, double semimajor_axis, double eccentricity,
   double argument_periapsis, double longitude_ascending, double inclination, double mean_anomaly, const Time& time,
   const Rotation& reference) : Orbit(std::set<const CelestialBody*>({&central}), semimajor_axis, eccentricity,
   argument_periapsis, longitude_ascending, inclination, mean_anomaly, time, reference)
{
}


// Constructor
inline CubeSim::Orbit::Orbit(const CelestialBody& central, const RigidBody& rigid_body, const Rotation& reference) :
   Orbit({&central}, rigid_body, reference)
{
}


// Get Apoapsis [m]
inline double CubeSim::Orbit::apoapsis(void) const
{
   // Return Apoapsis
   return _apoapsis;
}


// Get Argument of Periapsis [rad]
inline double CubeSim::Orbit::argument_periapsis(void) const
{
   // Return Argument of Periapsis
   return _argument_periapsis;
}


// Get eccentric Anomaly [rad]
inline double CubeSim::Orbit::eccentric_anomaly(void) const
{
   // Return eccentric Anomaly
   return _eccentric_anomaly;
}


// Get Eccentricity
inline double CubeSim::Orbit::eccentricity(void) const
{
   // Return Eccentricity
   return _eccentricity;
}


// Get Epoch
inline const CubeSim::Time& CubeSim::Orbit::epoch(void) const
{
   // Return Epoch
   return _epoch;
}


// Get standard gravitational Parameter [m^3/s^2]
inline double CubeSim::Orbit::gravitational_parameter(void) const
{
   // Return standard gravitational Parameter
   return _gravitational_parameter;
}


// Get Inclination [rad]
inline double CubeSim::Orbit::inclination(void) const
{
   // Return Inclination
   return _inclination;
}


// Get Longitude of the ascending Node [rad]
inline double CubeSim::Orbit::longitude_ascending(void) const
{
   // Return Longitude of the ascending Node
   return _longitude_ascending;
}


// Get mean Anomaly [rad]
inline double CubeSim::Orbit::mean_anomaly(void) const
{
   // Return mean Anomaly
   return _mean_anomaly;
}


// Get Periapsis [m]
inline double CubeSim::Orbit::periapsis(void) const
{
   // Return Periapsis
   return _periapsis;
}


// Get Period [s]
inline double CubeSim::Orbit::period(void) const
{
   // Return Period
   return _period;
}


// Get Reference Frame
inline const CubeSim::Rotation& CubeSim::Orbit::reference(void) const
{
   // Return Reference Frame
   return _reference;
}


// Set Reference Frame
inline void CubeSim::Orbit::reference(const Rotation& reference)
{
   // Set Reference Frame
   _reference = reference;
}

// Get semi-major Axis [m]
inline double CubeSim::Orbit::semimajor_axis(void) const
{
   // Return semi-major Axis
   return _semimajor_axis;
}


// Get Time
inline const CubeSim::Time& CubeSim::Orbit::time(void) const
{
   // Return Time
   return _time_;
}


// Get true Anomaly [rad]
inline double CubeSim::Orbit::true_anomaly(void) const
{
   // Return true Anomaly
   return _true_anomaly;
}
