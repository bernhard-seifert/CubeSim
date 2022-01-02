

// CUBESIM - PART - CYLINDER


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


// Class Cylinder
class CubeSim::Part::Cylinder : public Part
{
public:

   // Constructor
   Cylinder(void);
   Cylinder(double radius, double height);

   // Clone
   virtual Part* clone(void) const;

   // Height [m]
   double height(void) const;
   void height(double height);

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
   double _height;
   double _radius;
};


// Constructor
inline CubeSim::Part::Cylinder::Cylinder(void)
{
}


// Constructor
inline CubeSim::Part::Cylinder::Cylinder(double radius, double height)
{
   // Initialize
   this->radius(radius);
   this->height(height);
}


// Clone
inline CubeSim::Part* CubeSim::Part::Cylinder::clone(void) const
{
   // Return Copy
   return new Cylinder(*this);
}


// Get Height [m]
inline double CubeSim::Part::Cylinder::height(void) const
{
   // Return Height
   return _height;
}


// Set Height [m]
inline void CubeSim::Part::Cylinder::height(double height)
{
   // Check Height
   if (height < 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Height
   _height = height;

   // Update Property
   _update(_UPDATE_DIMENSION);
}


// Get Radius [m]
inline double CubeSim::Part::Cylinder::radius(void) const
{
   // Return Radius
   return _radius;
}


// Set Radius [m]
inline void CubeSim::Part::Cylinder::radius(double radius)
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
inline double CubeSim::Part::Cylinder::_area(void) const
{
   // Compute and return Surface Area
   return (2.0 * Constant::PI * _radius * (_radius + _height));
}


// Compute Center of Mass (Body Frame) [m]
inline const CubeSim::Vector3D CubeSim::Part::Cylinder::_center(void) const
{
   // Return Result
   return Vector3D(0.0, 0.0, _height / 2.0);
}


// Check if contains Point (Body Frame)
inline bool CubeSim::Part::Cylinder::_contains(const Vector3D& point) const
{
   // Return Result
   return ((0.0 <= point.z()) && (point.z() <= _height) &&
      ((point.x() * point.x() + point.y() * point.y()) <= (_radius * _radius)));
}


// Compute Volume [m^3]
inline double CubeSim::Part::Cylinder::_volume(void) const
{
   // Compute and return Volume
   return (Constant::PI * _radius * _radius * _height);
}
