

// CUBESIM - CELESTIAL BODY


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
#include "simulation.hpp"


// Assign (Simulation Reference is maintained)
inline CubeSim::CelestialBody& CubeSim::CelestialBody::operator =(const CelestialBody& celestial_body)
{
   // Check Celestial Body
   if (this != &celestial_body)
   {
      // Check Type to avoid Object Slicing
      if (typeid(*this) != typeid(celestial_body))
      {
         // Exception
         throw Exception::Parameter();
      }

      // Assign
      static_cast<RigidBody&>(*this) = celestial_body;
      static_cast<List<CelestialBody>::Item&>(*this) = celestial_body;
      _density = celestial_body._density;
      _flattening = celestial_body._flattening;
      _radius = celestial_body._radius;
      _temperature = celestial_body._temperature;
   }

   // Return Reference
   return *this;
}


// Compute gravitational Field (Body Frame) [m/s^2]
const CubeSim::Vector3D CubeSim::CelestialBody::gravitational_field(const Vector3D& point) const
{
   // Compute Distance
   double r = point.norm();

   // Return ideal gravitational Field
   return ((radius() <= r) ? (-Constant::G * mass() / pow(r, 3.0) * point) : Vector3D());
}


// Check if Point is inside (Body Frame)
bool CubeSim::CelestialBody::_contains(const Vector3D& point) const
{
   // Return Result
   return ((point.z() * point.z()) <= ((1.0 - _flattening) * (1.0 - _flattening) * (_radius * _radius -
      point.x() * point.x() - point.y() * point.y())));
}


// Compute Moment of Inertia Tensor (Body Frame) [kg*m^2]
const CubeSim::Inertia CubeSim::CelestialBody::_inertia(void) const
{
   // Compute Mass
   double mass = this->mass();

   // Compute Coefficient for X and Y Axes
   double a = 1.0 + pow(1.0 - _flattening, 2.0);

   // Compute and return Tensor
   return Inertia(mass * radius() * radius() / 5.0 *
      Matrix3D(Vector3D(a, 0.0, 0.0), Vector3D(0.0, a, 0.0), Vector3D(0.0, 0.0, 2.0)), mass);
}
