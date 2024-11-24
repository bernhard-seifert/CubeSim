

// ADCS - VECTOR


// Includes
#include <stdint.h>
#include "numeric.hpp"


// Preprocessor Directives
#pragma once


// Namespace ADCS
namespace ADCS
{
   // Class Vector
   class Vector;

   // Multiply
   const Vector operator *(const numeric_t& a, const Vector& v);
}


// Class Vector
class ADCS::Vector
{
public:

   // Unit Vectors
   static const Vector X;
   static const Vector Y;
   static const Vector Z;

   // Constructor
   Vector(const numeric_t& a = 0.0);
   Vector(const numeric_t& x, const numeric_t& y, const numeric_t& z);

   // Get Element
   numeric_t& operator ()(uint8_t i);
   const numeric_t& operator ()(uint8_t i) const;

   // Sign
   const Vector& operator +(void) const;
   const Vector operator -(void) const;

   // Compare
   bool operator ==(const Vector& v) const;
   bool operator !=(const Vector& v) const;

   // Multiply
   const Vector operator *(const numeric_t& a) const;
   numeric_t operator *(const Vector& v) const;
   Vector& operator *=(const numeric_t& a);

   // Divide
   const Vector operator /(const numeric_t& a) const;
   Vector& operator /=(const numeric_t& a);

   // Add
   const Vector operator +(const Vector& v) const;
   Vector& operator +=(const Vector& v);

   // Subtract
   const Vector operator -(const Vector& v) const;
   Vector& operator -=(const Vector& v);

   // Compute Cross Product
   const Vector operator ^(const Vector& v) const;
   Vector& operator ^=(const Vector& v);

   // Compute Angle
   numeric_t operator %(const Vector& v) const;

   // Compute Norm
   numeric_t norm(void) const;

   // Compute Unit Vector
   const Vector unit(void) const;

   // X Coordinate
   const numeric_t& x(void) const;
   void x(const numeric_t& x);

   // Y Coordinate
   const numeric_t& y(void) const;
   void y(const numeric_t& y);

   // Z Coordinate
   const numeric_t& z(void) const;
   void z(const numeric_t& z);

private:

   // Epsilon
   static const numeric_t _EPSILON;

   // Check if equal
   static bool _equal(const numeric_t& x, const numeric_t& y);

   // Variables
   numeric_t _a[3];
};


// Constructor
inline ADCS::Vector::Vector(const numeric_t& a) : Vector(a, a, a)
{
}


// Constructor
inline ADCS::Vector::Vector(const numeric_t& x, const numeric_t& y, const numeric_t& z)
{
   // Initialize
   this->x(x);
   this->y(y);
   this->z(z);
}


// Get Element
inline ADCS::numeric_t& ADCS::Vector::operator ()(uint8_t i)
{
   // Check Index
   if ((i < 1) || (3 < i))
   {
      // Use first Element
      i = 1;
   }

   // Return Element
   return _a[i - 1];
}


// Get Element
inline const ADCS::numeric_t& ADCS::Vector::operator ()(uint8_t i) const
{
   // Check Index
   if ((i < 1) || (3 < i))
   {
      // Use first Element
      i = 1;
   }

   // Return Element
   return _a[i - 1];
}


// Plus Sign
inline const ADCS::Vector& ADCS::Vector::operator +(void) const
{
   // Return Reference
   return *this;
}


// Compare
inline bool ADCS::Vector::operator !=(const Vector& v) const
{
   // Return Result
   return !(*this == v);
}


// Compute Cross Product and assign
inline ADCS::Vector& ADCS::Vector::operator ^=(const Vector& v)
{
   // Compute Cross Product and assign
   *this = *this ^ v;

   // Return Reference
   return *this;
}


// Get X Coordinate
inline const ADCS::numeric_t& ADCS::Vector::x(void) const
{
   // Return X Coordinate
   return _a[0];
}


// Set X Coordinate
inline void ADCS::Vector::x(const numeric_t& x)
{
   // Set X Coordinate
   _a[0] = x;
}


// Get Y Coordinate
inline const ADCS::numeric_t& ADCS::Vector::y(void) const
{
   // Return Y Coordinate
   return _a[1];
}


// Set Y Coordinate
inline void ADCS::Vector::y(const numeric_t& y)
{
   // Set Y Coordinate
   _a[1] = y;
}


// Get Z Coordinate
inline const ADCS::numeric_t& ADCS::Vector::z(void) const
{
   // Return Z Coordinate
   return _a[2];
}


// Set Z Coordinate
inline void ADCS::Vector::z(const numeric_t& z)
{
   // Set Z Coordinate
   _a[2] = z;
}


// Multiply
inline const ADCS::Vector ADCS::operator *(const numeric_t& a, const Vector& v)
{
   // Multiply and return Result
   return (v * a);
}
