

// CUBESIM - PART - BOX


// Includes
#include "../part.hpp"


// Preprocessor Directives
#pragma once


// Class Box
class CubeSim::Part::Box : public Part
{
public:

   // Constructor
   Box(void);
   Box(double length, double width, double height);

   // Clone
   virtual Part* clone(void) const;

   // Height [m]
   double height(void) const;
   void height(double height);

   // Length [m]
   double length(void) const;
   void length(double length);

   // Width [m]
   double width(void) const;
   void width(double width);

private:

   // Compute Surface Area [m^2]
   virtual double _area(void) const;

   // Compute Center of Mass (Body Frame) [m]
   virtual const Vector3D _center(void) const;

   // Check if Point is inside (Body Frame)
   virtual bool _contains(const Vector3D& point) const;

   // Compute Momentum of Inertia Tensor (Body Frame) [kg*m^2]
   virtual const Inertia _inertia(void) const;

   // Compute Volume [m^3]
   virtual double _volume(void) const;

   // Variables
   double _length;
   double _width;
   double _height;
};


// Constructor
inline CubeSim::Part::Box::Box(void)
{
}


// Constructor
inline CubeSim::Part::Box::Box(double length, double width, double height)
{
   // Initialize
   this->length(length);
   this->width(width);
   this->height(height);
}


// Clone
inline CubeSim::Part* CubeSim::Part::Box::clone(void) const
{
   // Return Copy
   return new Box(*this);
}


// Get Height [m]
inline double CubeSim::Part::Box::height(void) const
{
   // Return Height
   return _height;
}


// Set Height [m]
inline void CubeSim::Part::Box::height(double height)
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


// Get Length [m]
inline double CubeSim::Part::Box::length(void) const
{
   // Return Length
   return _length;
}


// Set Length [m]
inline void CubeSim::Part::Box::length(double length)
{
   // Check Length
   if (length < 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Length
   _length = length;

   // Update Property
   _update(_UPDATE_DIMENSION);
}


// Get Width [m]
inline double CubeSim::Part::Box::width(void) const
{
   // Return Width
   return _width;
}


// Set Width [m]
inline void CubeSim::Part::Box::width(double width)
{
   // Check Width
   if (width < 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Width
   _width = width;

   // Update Property
   _update(_UPDATE_DIMENSION);
}


// Compute Surface Area [m^2]
inline double CubeSim::Part::Box::_area(void) const
{
   // Compute and return Surface Area
   return (2.0 * (_length * _width + _width * _height + _height * _length));
}


// Compute Center of Mass (Body Frame) [m]
inline const CubeSim::Vector3D CubeSim::Part::Box::_center(void) const
{
   // Return Result
   return Vector3D(_length / 2.0, _width / 2.0, _height / 2.0);
}


// Check if contains Point (Body Frame)
inline bool CubeSim::Part::Box::_contains(const Vector3D& point) const
{
   // Return Result
   return ((0.0 <= point.x()) && (point.x() <= _length) && (0.0 <= point.y()) && (point.y() <= _width) &&
      (0.0 <= point.z()) && (point.z() <= _height));
}

// Compute Volume [m^3]
inline double CubeSim::Part::Box::_volume(void) const
{
   // Compute and return Volume
   return (_length * _width * _height);
}
