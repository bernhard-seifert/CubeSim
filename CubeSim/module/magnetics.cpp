

// CUBESIM - MODULE - MAGNETICS


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
#include "magnetics.hpp"
#include "../simulation.hpp"


// Compute magnetic Field [T]
const CubeSim::Vector3D CubeSim::Module::Magnetics::field(const Vector3D& point) const
{
   // Check for specific Celestial Body
   if (_celestial_body)
   {
      // Compute and return magnetic Field
      return _field(*_celestial_body, point);
   }

   // Check Simulation
   if (!simulation())
   {
      // Exception
      throw Exception::Failed();
   }

   // Magnetic Field
   Vector3D field;

   // Parse Celestial Body List
   for (auto celestial_body = simulation()->celestial_body().begin();
      celestial_body != simulation()->celestial_body().end(); ++celestial_body)
   {
      // Update magnetic Field
      field += _field(*celestial_body->second, point);
   }

   // Return magnetic Field
   return field;
}


// Compute magnetic Field [T]
const CubeSim::Vector3D CubeSim::Module::Magnetics::_field(const CelestialBody& celestial_body,
   const Vector3D& point) const
{
   // Transform Point relative to Celestial Body
   Vector3D point_ = point - celestial_body.position() - celestial_body.rotation();

   // Compute, transform and return magnetic Field
   return (celestial_body.magnetic_field(point_) + celestial_body.rotation());
}
