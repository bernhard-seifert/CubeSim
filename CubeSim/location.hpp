

// CUBESIM - LOCATION


// Includes
#include "time.hpp"
#include "vector.hpp"


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class CelestialBody
   class CelestialBody;

   // Class Location
   class Location;
}


// Class Location
class CubeSim::Location
{
public:

   // Constructor
   Location(const CelestialBody& celestial_body, const Vector3D& point = Vector3D(), const Time& time = Time());
   Location(const CelestialBody& celestial_body, double latitude, double longitude, double altitude,
      const Time& time = Time());

   // Convert to Vector3D
   operator const Vector3D(void) const;

   // Altitude [m]
   double altitude(void) const;
   void altitude(double altitude);

   // Celestial Body
   const CelestialBody& celestial_body(void) const;
   void celectial_body(const CelestialBody& celestial_body);

   // Latitude [rad]
   double latitude(void) const;
   void latitude(double latitude);

   // Longitude [rad]
   double longitude(void) const;
   void longitude(double longitude);

   // Point
   const Vector3D point(void) const;
   void point(const Vector3D& point);

   // Radius [m]
   double radius(void) const;
   void radius(double radius);

   // Time
   const Time& time(void) const;
   void time(const Time& time);

private:

   // Compute Normal (Distance from the Surface to the Z-Axis along the Ellipsoid Normal)
   double _normal(void) const;

   // Variables
   double _altitude;
   double _latitude;
   double _longitude;
   Time _time;
   const CelestialBody* _celestial_body;
};


// Constructor
inline CubeSim::Location::Location(const CelestialBody& celestial_body, const Vector3D& point, const Time& time)
{
   // Initialize
   this->celectial_body(celestial_body);
   this->point(point);
   this->time(time);
}


// Constructor
inline CubeSim::Location::Location(const CelestialBody& celestial_body, double latitude, double longitude,
   double altitude, const Time& time)
{
   // Initialize
   this->celectial_body(celestial_body);
   this->latitude(latitude);
   this->longitude(longitude);
   this->altitude(altitude);
   this->time(time);
}


// Convert to Vector3D
inline CubeSim::Location::operator const CubeSim::Vector3D(void) const
{
   // Return Point
   return point();
}


// Get Altitude [m]
inline double CubeSim::Location::altitude(void) const
{
   // Return Altitude
   return _altitude;
}


// Set Altitude [m]
inline void CubeSim::Location::altitude(double altitude)
{
   // Set Altitude
   _altitude = altitude;
}


// Get Celestial Body
inline const CubeSim::CelestialBody& CubeSim::Location::celestial_body(void) const
{
   // Return Celestial Body
   return *_celestial_body;
}


// Set Celestial Body
inline void CubeSim::Location::celectial_body(const CelestialBody& celestial_body)
{
   // Set Celestial Body
   _celestial_body = &celestial_body;
}


// Get Latitude [rad]
inline double CubeSim::Location::latitude(void) const
{
   // Return Latitude
   return _latitude;
}


// Set Latitude [rad]
inline void CubeSim::Location::latitude(double latitude)
{
   // Check Latitude
   if ((latitude < (-Constant::PI / 2.0)) || ((Constant::PI / 2.0) < latitude))
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Latitude
   _latitude = latitude;
}


// Get Longitude [rad]
inline double CubeSim::Location::longitude(void) const
{
   // Return Longitude
   return _longitude;
}


// Set Longitude [rad]
inline void CubeSim::Location::longitude(double longitude)
{
   // Set Longitude
   _longitude = fmod(longitude, 2.0 * Constant::PI);

   // Check Longitude
   if (_longitude < -Constant::PI)
   {
      // Update Longitude
      _longitude += 2.0 * Constant::PI;
   }
}


// Compute Radius [m]
inline double CubeSim::Location::radius(void) const
{
   // Compute and return Radius
   return static_cast<const Vector3D>(*this).norm();
}


// Get Time
inline const CubeSim::Time& CubeSim::Location::time(void) const
{
   // Return Time
   return _time;
}


// Set Time
inline void CubeSim::Location::time(const Time& time)
{
   // Set Time
   _time = time;
}
