

// ADCS - LOCATION


// Includes
#include <cmath>
#include <limits>
#include "location.hpp"


// Constructor
ADCS::Location::Location(const numeric_t& latitude, const numeric_t& longitude, const numeric_t& altitude,
   const double& time)
{
   // Initialize
   this->latitude(latitude);
   this->longitude(longitude);
   this->altitude(altitude);
   this->time(time);
}


// Get Point
const ADCS::Vector ADCS::Location::point(void) const
{
   // Compute Normal
   numeric_t normal = _normal();

   // Compute Distance from Axis
   numeric_t d = (normal + _altitude) * std::cos(_latitude);

   // Compute and return Vector
   return Vector(d * std::cos(_longitude), d * std::sin(_longitude),
      (normal * std::pow(NUM(1.0) - Constant::EARTH_FLATTENING, NUM(2.0)) + _altitude) * std::sin(_latitude));
}


// Set Point
void ADCS::Location::point(const Vector& point)
{
   // Check Position
   if (point == Vector())
   {
      // Initialize
      _latitude = NUM(0.0);
      _longitude = NUM(0.0);
      _altitude = NUM(0.0);
   }
   else
   {
      // Check Flattening
      if (Constant::EARTH_FLATTENING == NUM(0.0))
      {
         // Compute Latitude and Altitude
         _latitude = std::atan2(point.z(), sqrt(point.x() * point.x() + point.y() * point.y()));
         _altitude = point.norm() - Constant::EARTH_RADIUS;
      }
      else
      {
         // Compute Eccentricity of Ellipsoid
         numeric_t e = std::sqrt(NUM(2.0) * Constant::EARTH_FLATTENING * (NUM(1.0) - Constant::EARTH_FLATTENING));

         // Initialize
         numeric_t k = NUM(1.0) / (NUM(1.0) - e * e);

         // Solve Equation (Newton-Raphson Method)
         for (uint8_t i = 0; i < 10; ++i)
         {
            // Save previous Value
            numeric_t k_ = k;

            // Compute auxiliary Variable
            numeric_t c = std::pow(point.x() * point.x() + point.y() * point.y() + (NUM(1.0) - e * e) * point.z() *
               point.z() * k * k, NUM(1.5)) / Constant::EARTH_RADIUS / e / e;

            // Iterate
            k = (c + (NUM(1.0) - e * e) * point.z() * point.z() * k * k * k) /
               (c - point.x() * point.x() - point.y() * point.y());

            // Check Convergence
            if (std::fabs(k - k_) < std::numeric_limits<numeric_t>::epsilon())
            {
               // Stop Iteration
               break;
            }
         }

         // Compute Latitude and Altitude
         _latitude = std::atan2(k * point.z(), std::sqrt(point.x() * point.x() + point.y() * point.y()));
         _altitude = std::sqrt(point.x() * point.x() + point.y() * point.y() + point.z() * point.z() * k * k) *
            (e * e + NUM(1.0) / k - NUM(1.0)) / e / e;
      }

      // Compute Longitude
      _longitude = ((point.x() == NUM(0.0)) && (point.y() == NUM(0.0))) ? NUM(0.0) : std::atan2(point.y(), point.x());
   }
}


// Set Longitude
void ADCS::Location::longitude(const numeric_t& longitude)
{
   // Set Longitude
   _longitude = std::fmod(longitude, NUM(2.0) * Constant::PI);

   // Check Longitude
   if (_longitude < -Constant::PI)
   {
      // Update Longitude
      _longitude += NUM(2.0) * Constant::PI;
   }
}


// Set Radius
void ADCS::Location::radius(const numeric_t& radius)
{
   // Check Radius
   if (NUM(0.0) <= radius)
   {
      // Compute Normal
      numeric_t normal = _normal();

      // Compute Coefficients
      numeric_t p = (NUM(1.0) + Constant::EARTH_FLATTENING * (Constant::EARTH_FLATTENING - NUM(2.0)) *
         std::pow(std::sin(_latitude), NUM(2.0))) * normal;
      numeric_t q = normal * normal - radius * radius + (std::pow(NUM(1.0) - Constant::EARTH_FLATTENING, NUM(4.0)) -
         NUM(1.0)) * std::pow(normal * std::sin(_latitude), NUM(2.0));

      // Compute Altitude
      _altitude = std::sqrt(p * p - q) - p;
   }
}


// Compute Normal (Distance from the Surface to the Z-Axis along the Ellipsoid Normal)
ADCS::numeric_t ADCS::Location::_normal(void) const
{
   // Compute and return Normal
   return (Constant::EARTH_RADIUS / std::sqrt(NUM(1.0) + Constant::EARTH_FLATTENING *
      (Constant::EARTH_FLATTENING - NUM(2.0)) * std::pow(std::sin(_latitude), NUM(2.0))));
}
