

// CUBESIM - INERTIA


// Includes
#include "rotation.hpp"


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class Inertia
   class Inertia;
}


// Class Inertia
class CubeSim::Inertia
{
public:

   // Constructor
   Inertia(void);
   Inertia(const Matrix3D& inertia, double mass, const Vector3D& center = Vector3D());

   // Compute Inertia around arbitrary Axis and Pivot [kg*m^2]
   double operator ()(const Vector3D& axis, const Vector3D& pivot = Vector3D()) const;

   // Compute Momentum of Inertia Matrix
   operator const Matrix3D(void) const;

   // Add
   const Inertia operator +(const Inertia& inertia) const;
   Inertia& operator +=(const Inertia& inertia);

   // Translate [m]
   const Inertia operator +(const Vector3D& distance) const;
   const Inertia operator -(const Vector3D& distance) const;
   Inertia& operator +=(const Vector3D& distance);
   Inertia& operator -=(const Vector3D& distance);

   // Rotate
   const Inertia operator +(const Rotation& rotation) const;
   const Inertia operator -(const Rotation& rotation) const;
   Inertia& operator +=(const Rotation& rotation);
   Inertia& operator -=(const Rotation& rotation);

   // Center [m]
   const Vector3D& center(void) const;
   void center(const Vector3D& center);

   // Mass [kg]
   double mass(void) const;
   void mass(double mass);

private:

   // Variables
   double _mass;
   Vector3D _center;
   Matrix3D _matrix;
};


// Constructor
inline CubeSim::Inertia::Inertia(void) : _mass()
{
}


// Constructor
inline CubeSim::Inertia::Inertia(const Matrix3D& inertia, double mass, const Vector3D& center) : _matrix(inertia)
{
   // Initialize
   this->center(center);
   this->mass(mass);
}


// Add
inline const CubeSim::Inertia CubeSim::Inertia::operator +(const Inertia& inertia) const
{
   // Add, assign and return Result
   return (Inertia(*this) += inertia);
}


// Translate [m]
inline const CubeSim::Inertia CubeSim::Inertia::operator +(const Vector3D& displacement) const
{
   // Translate, assign and return Result
   return (Inertia(*this) += displacement);
}


// Translate [m]
inline const CubeSim::Inertia CubeSim::Inertia::operator -(const Vector3D& displacement) const
{
   // Translate, assign and return Result
   return (Inertia(*this) -= displacement);
}


// Translate and assign [m]
inline CubeSim::Inertia& CubeSim::Inertia::operator +=(const Vector3D& displacement)
{
   // Update Center
   _center += displacement;

   // Return Reference
   return *this;
}


// Translate and assign [m]
inline CubeSim::Inertia& CubeSim::Inertia::operator -=(const Vector3D& displacement)
{
   // Update Center
   _center -= displacement;

   // Return Reference
   return *this;
}


// Rotate
inline const CubeSim::Inertia CubeSim::Inertia::operator +(const Rotation& rotation) const
{
   // Rotate, assign and return Result
   return (Inertia(*this) += rotation);
}


// Rotate
inline const CubeSim::Inertia CubeSim::Inertia::operator -(const Rotation& rotation) const
{
   // Rotate, assign and return Result
   return (Inertia(*this) -= rotation);
}


// Rotate and assign
inline CubeSim::Inertia& CubeSim::Inertia::operator +=(const Rotation& rotation)
{
   // Rotate and assign
   _matrix += rotation;
   _center += rotation;

   // Return Reference
   return *this;
}


// Rotate and assign
inline CubeSim::Inertia& CubeSim::Inertia::operator -=(const Rotation& rotation)
{
   // Rotate and assign
   _matrix -= rotation;
   _center -= rotation;

   // Return Reference
   return *this;
}


// Get Center [m]
inline const CubeSim::Vector3D& CubeSim::Inertia::center(void) const
{
   // Return Center
   return _center;
}


// Set Center [m]
inline void CubeSim::Inertia::center(const Vector3D& center)
{
   // Set Center
   _center = center;
}


// Get Mass [kg]
inline double CubeSim::Inertia::mass(void) const
{
   // Return Mass
   return _mass;
}


// Set Mass [kg]
inline void CubeSim::Inertia::mass(double mass)
{
   // Check Mass
   if (mass < 0.0)
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Set Mass
   _mass = mass;
}
