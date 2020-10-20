

// CUBESIM - PART - SPHERE


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
