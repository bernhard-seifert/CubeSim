

// CUBESIM - FORCE


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
   // Class Force
   class Force;

   // Class RigidBody
   class RigidBody;

   // Scale
   const Force operator *(double factor, const Force& force);
}


// Class Force
class CubeSim::Force : public Vector3D, public List<Force>::Item
{
public:

   // Constructor
   Force(double x, double y, double z);
   Force(double x, double y, double z, double point_x, double point_y, double point_z);
   Force(const Vector3D& force = Vector3D(), const Vector3D& point = Vector3D());

   // Copy Constructor (Rigid Body Reference is reset)
   Force(const Force& force);

   // Assign
   Force& operator =(const Force& force);
   Force& operator =(const Vector3D& force);

   // Sign
   const Force& operator +(void) const;
   const Force operator -(void) const;

   // Scale
   const Force operator *(double factor) const;
   const Force operator /(double factor) const;
   Force& operator *=(double factor);
   Force& operator /=(double factor);

   // Add (Point of Application of passed Force is discarded)
   const Force operator +(const Force& force) const;
   Force& operator +=(const Force& force);

   // Subtract (Point of Application of passed Force is discarded)
   const Force operator -(const Force& force) const;
   Force& operator -=(const Force& force);

   // Translate [m]
   const Force operator +(const Vector3D& distance) const;
   const Force operator -(const Vector3D& distance) const;
   Force& operator +=(const Vector3D& distance);
   Force& operator -=(const Vector3D& distance);

   // Rotate
   const Force operator +(const Rotation& rotation) const;
   const Force operator -(const Rotation& rotation) const;
   Force& operator +=(const Rotation& rotation);
   Force& operator -=(const Rotation& rotation);

   // Point of Application [m]
   const Vector3D& point(void) const;
   void point(const Vector3D& point);

   // X Coordinate [m]
   void x(double x);
   using Vector3D::x;

   // Y Coordinate [m]
   void y(double y);
   using Vector3D::y;

   // Z Coordinate [m]
   void z(double z);
   using Vector3D::z;

private:

   // Update Properties
   static const uint8_t _UPDATE_MAGNITUDE = 1;
   static const uint8_t _UPDATE_POINT = 2;

   // Update Property
   void _update(uint8_t update);

   // Variables
   Vector3D _point;
   RigidBody* _rigid_body;

   // Friends
   friend class RigidBody;
};


// Constructor
inline CubeSim::Force::Force(double x, double y, double z) : Force(Vector3D(x, y, z))
{
}


// Constructor
inline CubeSim::Force::Force(double x, double y, double z, double point_x, double point_y, double point_z) :
   Force(Vector3D(x, y, z), Vector3D(point_x, point_y, point_z))
{
}


// Constructor
inline CubeSim::Force::Force(const Vector3D& force, const Vector3D& point) : Vector3D(force), _point(point),
   _rigid_body()
{
}


// Copy Constructor (Rigid Body Reference is reset)
inline CubeSim::Force::Force(const Force& force) : Vector3D(force), _point(force._point), _rigid_body()
{
}


// Assign
inline CubeSim::Force& CubeSim::Force::operator =(const Vector3D& force)
{
   // Assign
   static_cast<Vector3D&>(*this) = force;

   // Update Property
   _update(_UPDATE_MAGNITUDE);

   // Return Reference
   return *this;
}


// Plus Sign
inline const CubeSim::Force& CubeSim::Force::operator +(void) const
{
   // Return Reference
   return *this;
}


// Minus Sign
inline const CubeSim::Force CubeSim::Force::operator -(void) const
{
   // Return Result
   return Force(-static_cast<const Vector3D&>(*this), _point);
}


// Scale
inline const CubeSim::Force CubeSim::Force::operator *(double factor) const
{
   // Scale, assign and return Result
   return (Force(*this) *= factor);
}


// Scale
inline const CubeSim::Force CubeSim::Force::operator /(double factor) const
{
   // Scale, assign and return Result
   return (Force(*this) /= factor);
}


// Scale and assign
inline CubeSim::Force& CubeSim::Force::operator *=(double factor)
{
   // Scale and assign
   static_cast<Vector3D&>(*this) *= factor;

   // Return Reference
   return *this;
}


// Scale and assign
inline CubeSim::Force& CubeSim::Force::operator /=(double factor)
{
   // Check Factor
   if (factor == 0.0)
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Scale and assign
   static_cast<Vector3D&>(*this) /= factor;

   // Return Reference
   return *this;
}


// Add (Point of Application of passed Force is discarded)
inline const CubeSim::Force CubeSim::Force::operator +(const Force& force) const
{
   // Add, assign and return Result
   return (Force(*this) += force);
}


// Add and assign (Point of Application of passed Force is discarded)
inline CubeSim::Force& CubeSim::Force::operator +=(const Force& force)
{
   // Add and assign
   static_cast<Vector3D&>(*this) += force;

   // Return Reference
   return *this;
}


// Subtract (Point of Application of passed Force is discarded)
inline const CubeSim::Force CubeSim::Force::operator -(const Force& force) const
{
	// Subtract, assign and return Result
	return (Force(*this) -= force);
}


// Subtract and assign (Point of Application of passed Force is discarded)
inline CubeSim::Force& CubeSim::Force::operator -=(const Force& force)
{
	// Subtract and assign
	static_cast<Vector3D&>(*this) -= force;

	// Return Reference
	return *this;
}


// Translate [m]
inline const CubeSim::Force CubeSim::Force::operator +(const Vector3D& distance) const
{
   // Translate, assign and return Result
   return (Force(*this) += distance);
}


// Translate [m]
inline const CubeSim::Force CubeSim::Force::operator -(const Vector3D& distance) const
{
   // Translate and return Result
   return (Force(*this) -= distance);
}


// Translate and assign [m]
inline CubeSim::Force& CubeSim::Force::operator +=(const Vector3D& distance)
{
   // Translate and assign
   _point += distance;

   // Return Reference
   return *this;
}


// Translate and assign [m]
inline CubeSim::Force& CubeSim::Force::operator -=(const Vector3D& distance)
{
   // Translate and assign
   _point -= distance;

   // Return Reference
   return *this;
}


// Rotate
inline const CubeSim::Force CubeSim::Force::operator +(const Rotation& rotation) const
{
   // Rotate, assign and return Result
   return (Force(*this) += rotation);
}


// Rotate
inline const CubeSim::Force CubeSim::Force::operator -(const Rotation& rotation) const
{
   // Rotate, assign and return Result
   return (Force(*this) -= rotation);
}


// Rotate and assign
inline CubeSim::Force& CubeSim::Force::operator +=(const Rotation& rotation)
{
   // Rotate and assign
   static_cast<Vector3D&>(*this) += rotation;
   _point += rotation;

   // Return Reference
   return *this;
}


// Rotate and assign
inline CubeSim::Force& CubeSim::Force::operator -=(const Rotation& rotation)
{
   // Rotate and assign
   static_cast<Vector3D&>(*this) -= rotation;
   _point -= rotation;

   // Return Reference
   return *this;
}


// Get Point of Application [m]
inline const CubeSim::Vector3D& CubeSim::Force::point(void) const
{
   // Return Point of Application
   return _point;
}


// Set Point of Application [m]
inline void CubeSim::Force::point(const Vector3D& point)
{
   // Set Point of Application
   _point = point;

   // Update Property
   _update(_UPDATE_POINT);
}


// Set X Coordinate [m]
inline void CubeSim::Force::x(double x)
{
   // Set X Coordinate
   Vector3D::x(x);

   // Update Property
   _update(_UPDATE_MAGNITUDE);
}


// Set Y Coordinate [m]
inline void CubeSim::Force::y(double y)
{
   // Set Y Coordinate
   Vector3D::y(y);

   // Update Property
   _update(_UPDATE_MAGNITUDE);
}


// Set Z Coordinate [m]
inline void CubeSim::Force::z(double z)
{
   // Set Z Coordinate
   Vector3D::z(z);

   // Update Property
   _update(_UPDATE_MAGNITUDE);
}


// Scale
inline const CubeSim::Force CubeSim::operator *(double factor, const Force& force)
{
   // Scale and return Result
   return (force * factor);
}
