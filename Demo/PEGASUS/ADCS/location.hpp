

// ADCS - LOCATION


// Preprocessor Directives
#pragma once


// Includes
#include "constant.hpp"
#include "vector.hpp"


// Namespace ADCS
namespace ADCS
{
   // Class Location
   class Location;
}


// Class Location
class ADCS::Location
{
public:

   // Constructor
   Location(const Vector& point = Vector());
   Location(const numeric_t& latitude, const numeric_t& longitude, const numeric_t& altitude, const double& time = 0.0);

   // Convert to Vector
   operator const Vector(void) const;

   // Altitude [m]
   const numeric_t& altitude(void) const;
   void altitude(const numeric_t& altitude);

   // Latitude [rad]
   const numeric_t& latitude(void) const;
   void latitude(const numeric_t& latitude);

   // Longitude [rad]
   const numeric_t& longitude(void) const;
   void longitude(const numeric_t& longitude);

   // Point
   const Vector point(void) const;
   void point(const Vector& point);

   // Radius [m]
   const numeric_t radius(void) const;
   void radius(const numeric_t& radius);

   // Time [s] (since 2000-01-01 00:00:00)
   const double& time(void) const;
   void time(const double& time);

private:

   // Compute Normal (Distance from the Surface to the Z-Axis along the Ellipsoid Normal)
   numeric_t _normal(void) const;

   // Variables
   numeric_t _altitude;
   numeric_t _latitude;
   numeric_t _longitude;
   double _time;

   // Friends
   friend class Transform;
};


// Constructor
inline ADCS::Location::Location(const Vector& point)
{
   // Initialize
   this->point(point);
}


// Convert to Vector
inline ADCS::Location::operator const ADCS::Vector(void) const
{
   // Return Point
   return point();
}


// Get Altitude
inline const ADCS::numeric_t& ADCS::Location::altitude(void) const
{
   // Return Altitude
   return _altitude;
}


// Set Altitude
inline void ADCS::Location::altitude(const numeric_t& altitude)
{
   // Set Altitude
   _altitude = altitude;
}


// Get Latitude
inline const ADCS::numeric_t& ADCS::Location::latitude(void) const
{
   // Return Latitude
   return _latitude;
}


// Set Latitude
inline void ADCS::Location::latitude(const numeric_t& latitude)
{
   // Check Latitude
   if (((-Constant::PI / NUM(2.0)) <= latitude) && (latitude <= (Constant::PI / NUM(2.0))))
   {
      // Set Latitude
      _latitude = latitude;
   }
}


// Get Longitude
inline const ADCS::numeric_t& ADCS::Location::longitude(void) const
{
   // Return Longitude
   return _longitude;
}


// Compute Radius
inline const ADCS::numeric_t ADCS::Location::radius(void) const
{
   // Compute and return Radius
   return static_cast<const Vector>(*this).norm();
}


// Get Time [s] (since 2000-01-01 00:00:00)
inline const double& ADCS::Location::time(void) const
{
   // Return Time
   return _time;
}


// Set Time [s] (since 2000-01-01 00:00:00)
inline void ADCS::Location::time(const double& time)
{
   // Set Time
   _time = time;
}
