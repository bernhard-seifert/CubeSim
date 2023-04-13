

// CUBESIM - LOCATION


// Copyright (c) 2022 Bernhard Seifert
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sub-license, and / or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
// Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
// OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


// Includes
#include "celestial_body.hpp"


// Get Position
const CubeSim::Vector3D CubeSim::Location::position(void) const
{
   // Compute Normal
   double normal = _normal();

   // Compute Distance from Axis
   double d = (normal + _altitude) * cos(_latitude);

   // Compute and return Position
   return (Vector3D(d * cos(_longitude), d * sin(_longitude), (normal * pow(1.0 - _celestial_body->flattening(), 2.0) +
      _altitude) * sin(_latitude)) + _celestial_body->rotation() + _celestial_body->position());
}


// Set Position
void CubeSim::Location::position(const Vector3D& position)
{
   // Compute relative position
   Vector3D position_ = position - _celestial_body->position() - _celestial_body->rotation();

   // Check Position
   if (position_ == Vector3D())
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
         _latitude = atan2(position_.z(), sqrt(position_.x() * position_.x() + position_.y() * position_.y()));
         _altitude = position_.norm() - _celestial_body->radius();
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
            double c = pow(position_.x() * position_.x() + position_.y() * position_.y() +
               (1.0 - e * e) * position_.z() * position_.z() * k * k, 1.5) / _celestial_body->radius() / e / e;

            // Iterate
            k = (c + (1.0 - e * e) * position_.z() * position_.z() * k * k * k) /
               (c - position_.x() * position_.x() - position_.y() * position_.y());

            // Check Convergence
            if (fabs(k - k_) < std::numeric_limits<double>::epsilon())
            {
               // Stop Iteration
               break;
            }
         }

         // Compute Latitude and Altitude
         _latitude = atan2(k * position_.z(), sqrt(position_.x() * position_.x() + position_.y() * position_.y()));
         _altitude = sqrt(position_.x() * position_.x() + position_.y() * position_.y() +
            position_.z() * position_.z() * k * k) * (e * e + 1.0 / k - 1.0) / e / e;
      }

      // Compute Longitude
      _longitude = ((position_.x() == 0.0) && (position_.y() == 0.0)) ? 0.0 : atan2(position_.y(), position_.x());
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
