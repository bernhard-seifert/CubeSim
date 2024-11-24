

// CUBESIM - PART - SPHERE


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
#include "../part.hpp"


// Preprocessor Directives
#pragma once


// Class Sphere
class CubeSim::Part::Sphere : public Part
{
public:

   // Constructor
   Sphere(double radius = 0.0);

   // Clone
   virtual Part* clone(void) const;

   // Radius [m]
   double radius(void) const;
   void radius(double radius);

private:

   // Compute Surface Area [m^2]
   virtual double _area(void) const;

   // Compute Center of Mass (Body Frame) [m]
   virtual const Vector3D _center(void) const;

   // Check if Point is inside (Body Frame)
   virtual bool _contains(const Vector3D& point) const;

   // Compute Moment of Inertia Tensor (Body Frame) [kg*m^2]
   virtual const Inertia _inertia(void) const;

   // Compute Volume [m^3]
   virtual double _volume(void) const;

   // Variables
   double _radius;
};


// Constructor
inline CubeSim::Part::Sphere::Sphere(double radius)
{
   // Initialize
   this->radius(radius);
}


// Clone
inline CubeSim::Part* CubeSim::Part::Sphere::clone(void) const
{
   // Return Copy
   return new Sphere(*this);
}


// Get Radius [m]
inline double CubeSim::Part::Sphere::radius(void) const
{
   // Return Radius
   return _radius;
}


// Set Radius [m]
inline void CubeSim::Part::Sphere::radius(double radius)
{
   // Check Radius
   if (radius < 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Radius
   _radius = radius;

   // Update Property
   _update(_UPDATE_DIMENSION);
}


// Compute Surface Area [m^2]
inline double CubeSim::Part::Sphere::_area(void) const
{
   // Compute and return Surface Area
   return (4.0 * Constant::PI * _radius * _radius);
}


// Compute Center of Mass (Body Frame) [m]
inline const CubeSim::Vector3D CubeSim::Part::Sphere::_center(void) const
{
   // Return Result
   return Vector3D();
}


// Check if contains Point (Body Frame)
inline bool CubeSim::Part::Sphere::_contains(const Vector3D& point) const
{
   // Return Result
   return ((point.x() * point.x() + point.y() * point.y() + point.z() * point.z()) <= (_radius * _radius));
}


// Compute Moment of Inertia (Body Frame) [kg*m^2]
inline const CubeSim::Inertia CubeSim::Part::Sphere::_inertia(void) const
{
   // Compute Mass
   double mass = this->mass();

   // Compute and return Tensor
   return Inertia(2.0 * mass * radius() * radius() / 5.0 * Matrix3D::IDENTITY, mass);
}


// Compute Volume [m^3]
inline double CubeSim::Part::Sphere::_volume(void) const
{
   // Compute and return Volume
   return (4.0 / 3.0 * Constant::PI * pow(radius(), 3));
}
