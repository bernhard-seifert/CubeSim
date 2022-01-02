

// CUBESIM - PART - PRISM


// Includes
#include "../part.hpp"
#include "../polygon.hpp"


// Preprocessor Directives
#pragma once


// Class Prism
class CubeSim::Part::Prism : public Part
{
public:

   // Constructor
   Prism(const Polygon2D& base = Polygon2D(), double height = 0.0);

   // Base [m]
   const Polygon2D& base(void) const;
   void base(const Polygon2D& base);

   // Clone
   virtual Part* clone(void) const;

   // Height [m]
   double height(void) const;
   void height(double height);

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
   Polygon2D _base;
};


// Constructor
inline CubeSim::Part::Prism::Prism(const Polygon2D& base, double height)
{
   // Initialize
   this->base(base);
   this->height(height);
}


// Get Base [m]
inline const CubeSim::Polygon2D& CubeSim::Part::Prism::base(void) const
{
   // Return Base
   return _base;
}


// Set Base [m]
inline void CubeSim::Part::Prism::base(const Polygon2D& base)
{
   // Check Vertices
   if (base.vertex().size() < 3)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Base
   _base = base;

   // Update Property
   _update(_UPDATE_DIMENSION);
}


// Clone
inline CubeSim::Part* CubeSim::Part::Prism::clone(void) const
{
   // Return Copy
   return new Prism(*this);
}


// Get Height [m]
inline double CubeSim::Part::Prism::height(void) const
{
   // Return Height
   return _height;
}


// Set Height [m]
inline void CubeSim::Part::Prism::height(double height)
{
   // Check Height
   if (height <= 0.0)
   {
      // Exception
      throw new Exception::Parameter();
   }

   // Set Height
   _height = height;

   // Update Property
   _update(_UPDATE_DIMENSION);
}


// Compute Surface Area [m^2]
inline double CubeSim::Part::Prism::_area(void) const
{
   // Compute and return Surface Area
   return (2.0 * _base.area() + _base.perimeter() * _height);
}


// Compute Center of Mass (Body Frame) [m]
inline const CubeSim::Vector3D CubeSim::Part::Prism::_center(void) const
{
   // Get Center of Mass of Base
   Vector2D center = _base.center();

   // Return Result
   return Vector3D(center.x(), center.y(), _height / 2.0);
}


// Check if contains Point (Body Frame)
inline bool CubeSim::Part::Prism::_contains(const Vector3D& point) const
{
   // Return Result
   return ((0.0 <= point.z()) && (point.z() <= _height) && _base.inside(Vector2D(point.x(), point.y())));
}


// Compute Volume [m^3]
inline double CubeSim::Part::Prism::_volume(void) const
{
   // Compute and return Volume
   return (_base.area() * _height);
}
