

// CUBESIM - LOCATION


// Includes
#include "celestial_body.hpp"


// Get Point
const CubeSim::Vector3D CubeSim::Location::point(void) const
{
   // Compute Normal
   double normal = _normal();

   // Compute Distance from Axis
   double d = (normal + _altitude) * cos(_latitude);

   // Compute and return Point
   return Vector3D(d * cos(_longitude), d * sin(_longitude),
      (normal * pow(1.0 - _celestial_body->flattening(), 2.0) + _altitude) * sin(_latitude));
}


// Set Point
void CubeSim::Location::point(const Vector3D& point)
{
   // Check Point
   if (point == Vector3D())
   {
      // Set Latitude, Longitude, Altitude
      _latitude = 0.0;
      _longitude = 0.0;
      _altitude = 0.0;
   }
   else
   {
      // Check Flattening
      if (_celestial_body->flattening() == 0.0)
      {
         // Compute Latitude and Altitude
         _latitude = atan2(point.z(), sqrt(point.x() * point.x() + point.y() * point.y()));
         _altitude = point.norm() - _celestial_body->radius();
      }
      else
      {
         // Compute Eccentricity of Ellipsoid
         double e = sqrt(2.0 * _celestial_body->flattening() * (1.0 - _celestial_body->flattening()));

         // Initialize
         double k = 1.0 / (1.0 - e * e);

         // Solve Equation (Newton-Raphson Method)
         for (uint8_t i = 0; i < 10; ++i)
         {
            // Save previous Value
            double k_ = k;

            // Compute auxiliary Variable
            double c = pow(point.x() * point.x() + point.y() * point.y() +
               (1.0 - e * e) * point.z() * point.z() * k * k, 1.5) / _celestial_body->radius() / e / e;

            // Iterate
            k = (c + (1.0 - e * e) * point.z() * point.z() * k * k * k) /
               (c - point.x() * point.x() - point.y() * point.y());

            // Check Convergence
            if (fabs(k - k_) < std::numeric_limits<double>::epsilon())
            {
               // Stop Iteration
               break;
            }
         }

         // Compute Latitude and Altitude
         _latitude = atan2(k * point.z(), sqrt(point.x() * point.x() + point.y() * point.y()));
         _altitude = sqrt(point.x() * point.x() + point.y() * point.y() + point.z() * point.z() * k * k) *
            (e * e + 1.0 / k - 1.0) / e / e;
      }

      // Compute Longitude
      _longitude = ((point.x() == 0.0) && (point.y() == 0.0)) ? 0.0 : atan2(point.y(), point.x());
   }
}


// Set Radius [m]
void CubeSim::Location::radius(double radius)
{
   // Check Radius
   if (radius < 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Compute Normal
   double normal = _normal();

   // Compute Coefficients
   double p = (1.0 + _celestial_body->flattening() * (_celestial_body->flattening() - 2.0) * pow(sin(_latitude), 2.0)) *
      normal;
   double q = normal * normal - radius * radius + (pow(1.0 - _celestial_body->flattening(), 4.0) - 1.0) *
      pow(normal * sin(_latitude), 2.0);

   // Compute Altitude
   _altitude = sqrt(p * p - q) - p;
}


// Compute Normal (Distance from the Surface to the Z-Axis along the Ellipsoid Normal)
inline double CubeSim::Location::_normal(void) const
{
   // Compute and return Normal
   return (_celestial_body->radius() / sqrt(1.0 + _celestial_body->flattening() *
      (_celestial_body->flattening() - 2.0) * pow(sin(_latitude), 2.0)));
}
