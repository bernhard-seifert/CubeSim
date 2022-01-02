

// CUBESIM - PART - CONE


// Includes
#include "../part.hpp"


// Preprocessor Directives
#pragma once


// Class Cone
class CubeSim::Part::Cone : public Part
{
public:

   // Constructor
   Cone(void);
   Cone(double radius, double height);

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
inline CubeSim::Part::Cone::Cone(void)
{
}


// Constructor
inline CubeSim::Part::Cone::Cone(double radius, double height)
{
   // Initialize
   this->radius(radius);
   this->height(height);
}


// Clone
inline CubeSim::Part* CubeSim::Part::Cone::clone(void) const
{
   // Return Copy
   return new Cone(*this);
}


// Get Height [m]
inline double CubeSim::Part::Cone::height(void) const
{
   // Return Height
   return _height;
}


// Set Height [m]
inline void CubeSim::Part::Cone::height(double height)
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
inline double CubeSim::Part::Cone::radius(void) const
{
   // Return Radius
   return _radius;
}


// Set Radius [m]
inline void CubeSim::Part::Cone::radius(double radius)
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
inline double CubeSim::Part::Cone::_area(void) const
{
   // Compute and return Surface Area
   return (Constant::PI * _radius * (_radius + sqrt(_radius * _radius + _height * _height)));
}


// Compute Center of Mass (Body Frame) [m]
inline const CubeSim::Vector3D CubeSim::Part::Cone::_center(void) const
{
   // Return Result
   return Vector3D(0.0, 0.0, height() / 4.0);
}


// Check if contains Point (Body Frame)
inline bool CubeSim::Part::Cone::_contains(const Vector3D& point) const
{
   // Return Result
   return ((0.0 <= point.z()) && (point.z() <= _height) && ((point.x() * point.x() + point.y() * point.y()) <=
      pow((_height == 0.0) ? _radius : (_radius / _height * (_height - point.z())), 2.0)));
}


// Compute Volume [m^3]
inline double CubeSim::Part::Cone::_volume(void) const
{
   // Compute and return Volume
   return (Constant::PI * _radius * _radius * _height / 3.0);
}
