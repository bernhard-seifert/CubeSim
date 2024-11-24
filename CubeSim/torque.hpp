

// CUBESIM - TORQUE


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
#include "list.hpp"
#include "rotation.hpp"


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class Torque
   class Torque;

   // Scale
   const Torque operator *(double factor, const Torque& torque);
}


// Class Torque
class CubeSim::Torque : public Vector3D, public List<Torque>::Item
{
public:

   // Constructor
   Torque(double x, double y, double z);
   Torque(const Vector3D& torque = Vector3D());

   // Copy Constructor (Rigid Body Reference is reset)
   Torque(const Torque& torque);

   // Assign
   Torque& operator =(const Torque& torque);
   Torque& operator =(const Vector3D& torque);

   // Sign
   const Torque& operator +(void) const;
   const Torque operator -(void) const;

   // Scale
   const Torque operator *(double factor) const;
   Torque operator /(double factor) const;
   Torque& operator *=(double factor);
   Torque& operator /=(double factor);

   // Add
   const Torque operator +(const Torque& torque) const;
   Torque& operator +=(const Torque& torque);
   using Vector3D::operator +;
   using Vector3D::operator +=;

   // Rotate
   const Torque operator +(const Rotation& rotation) const;
   const Torque operator -(const Rotation& rotation) const;
   Torque& operator +=(const Rotation& rotation);
   Torque& operator -=(const Rotation& rotation);
   using Vector3D::operator -;
   using Vector3D::operator -=;

   // X Coordinate [N*m]
   void x(double x);
   using Vector3D::x;

   // Y Coordinate [N*m]
   void y(double y);
   using Vector3D::y;

   // Z Coordinate [N*m]
   void z(double z);
   using Vector3D::z;

private:

   // Update Properties
   static const uint8_t _UPDATE_MAGNITUDE = 1;

   // Update Property
   void _update(uint8_t update);

   // Variables
   RigidBody* _rigid_body;

   // Friends
   friend class RigidBody;
};


// Constructor
inline CubeSim::Torque::Torque(double x, double y, double z) : Torque(Vector3D(x, y, z))
{
}


// Constructor
inline CubeSim::Torque::Torque(const Vector3D& torque) : Vector3D(torque), _rigid_body()
{
}


// Copy Constructor (Rigid Body Reference is reset)
inline CubeSim::Torque::Torque(const Torque& torque) : Vector3D(torque), _rigid_body()
{
}


// Assign (Rigid Body Reference is maintained)
inline CubeSim::Torque& CubeSim::Torque::operator =(const Torque& torque)
{
   // Check Torque
   if (this != &torque)
   {
      // Assign
      *this = static_cast<const Vector3D&>(torque);
   }

   // Return Reference
   return *this;
}


// Assign
inline CubeSim::Torque& CubeSim::Torque::operator =(const Vector3D& torque)
{
   // Assign
   static_cast<Vector3D&>(*this) = torque;

   // Update Property
   _update(_UPDATE_MAGNITUDE);

   // Return Reference
   return *this;
}


// Plus Sign
inline const CubeSim::Torque& CubeSim::Torque::operator +(void) const
{
   // Return Reference
   return *this;
}


// Minus Sign
inline const CubeSim::Torque CubeSim::Torque::operator -(void) const
{
   // Return Result
   return -static_cast<const Vector3D&>(*this);
}


// Scale
inline const CubeSim::Torque CubeSim::Torque::operator *(double factor) const
{
   // Scale, assign and return Result
   return (Torque(*this) *= factor);
}


// Scale
inline CubeSim::Torque CubeSim::Torque::operator /(double factor) const
{
   // Scale, assign and return Result
   return (Torque(*this) /= factor);
}


// Scale and assign
inline CubeSim::Torque& CubeSim::Torque::operator *=(double factor)
{
   // Scale and assign
   static_cast<Vector3D&>(*this) *= factor;

   // Return Reference
   return *this;
}


// Scale and assign
inline CubeSim::Torque& CubeSim::Torque::operator /=(double factor)
{
   // Scale and assign
   static_cast<Vector3D&>(*this) /= factor;

   // Return Reference
   return *this;
}


// Add
inline const CubeSim::Torque CubeSim::Torque::operator +(const Torque& torque) const
{
   // Add, assign and return Result
   return (Torque(*this) += torque);
}


// Add and assign
inline CubeSim::Torque& CubeSim::Torque::operator +=(const Torque& torque)
{
   // Add and assign
   static_cast<Vector3D&>(*this) += torque;

   // Return Reference
   return *this;
}


// Rotate
inline const CubeSim::Torque CubeSim::Torque::operator +(const Rotation& rotation) const
{
   // Rotate, assign and return Result
   return (Torque(*this) += rotation);
}


// Rotate
inline const CubeSim::Torque CubeSim::Torque::operator -(const Rotation& rotation) const
{
   // Rotate, assign and return Result
   return (Torque(*this) -= rotation);
}


// Rotate and assign
inline CubeSim::Torque& CubeSim::Torque::operator +=(const Rotation& rotation)
{
   // Rotate and assign
   static_cast<Vector3D&>(*this) += rotation;

   // Return Reference
   return *this;
}


// Rotate and assign
inline CubeSim::Torque& CubeSim::Torque::operator -=(const Rotation& rotation)
{
   // Rotate and assign
   static_cast<Vector3D&>(*this) -= rotation;

   // Return Reference
   return *this;
}


// Scale
inline const CubeSim::Torque CubeSim::operator *(double factor, const Torque& torque)
{
   // Scale and return Result
   return (torque * factor);
}


// Set X Coordinate [N*m]
inline void CubeSim::Torque::x(double x)
{
   // Set X Coordinate
   Vector3D::x(x);

   // Update Property
   _update(_UPDATE_MAGNITUDE);
}


// Set Y Coordinate [N*m]
inline void CubeSim::Torque::y(double y)
{
   // Set Y Coordinate
   Vector3D::y(y);

   // Update Property
   _update(_UPDATE_MAGNITUDE);
}


// Set Z Coordinate [N*m]
inline void CubeSim::Torque::z(double z)
{
   // Set Z Coordinate
   Vector3D::z(z);

   // Update Property
   _update(_UPDATE_MAGNITUDE);
}
