

// CUBESIM - VECTOR


// Includes
#include <vector.hpp>
#include "constant.hpp"
#include "exception.hpp"


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class Vector2D
   class Vector2D;

   // Class Vector3D
   class Vector3D;

   // Class Matrix3D
   class Matrix3D;

   // Multiply
   const Vector2D operator *(double a, const Vector2D& v);
   const Vector3D operator *(double a, const Vector3D& v);
}


// Class Vector2D
class CubeSim::Vector2D : private Vector<double>
{
public:

   // Unit Vectors
   static const Vector2D X;
   static const Vector2D Y;

   // Constructor
   Vector2D(void);
   Vector2D(double x, double y);
   Vector2D(const Vector<double>& v);

   // Get Element
   double& operator ()(size_t i);
   double operator ()(size_t i) const;
   double& at(size_t i);
   const double& at(size_t i) const;

   // Sign
   const Vector2D& operator +(void) const;
   const Vector2D operator -(void) const;

   // Compare
   bool operator ==(const Vector2D& v) const;
   bool operator !=(const Vector2D& v) const;

   // Multiply
   const Vector2D operator *(double a) const;
   double operator *(const Vector2D& v) const;
   Vector2D& operator *=(double a);

   // Divide
   const Vector2D operator /(double a) const;
   Vector2D& operator /=(double a);

   // Add
   const Vector2D operator +(const Vector2D& v) const;
   Vector2D& operator +=(const Vector2D& v);

   // Subtract
   const Vector2D operator -(const Vector2D& v) const;
   Vector2D& operator -=(const Vector2D& v);

   // Compute Z Coordinate of Cross Product
   double operator ^(const Vector2D& v) const;

   // Compute Angle
   double operator |(const Vector2D& v) const;

   // Compute Norm
   using Vector<double>::norm;

   // Compute Unit Vector
   const Vector2D unit(void) const;

   // X Coordinate
   double x(void) const;
   void x(double x);

   // Y Coordinate
   double y(void) const;
   void y(double y);
};


// Class Vector3D
class CubeSim::Vector3D : private Vector<double>
{
public:

   // Unit Vectors
   static const Vector3D X;
   static const Vector3D Y;
   static const Vector3D Z;

   // Constructor
   Vector3D(void);
   Vector3D(double x, double y, double z);
   Vector3D(const Vector2D& v);
   Vector3D(const Vector<double>& v);

   // Get Element
   double& operator ()(size_t i);
   double operator ()(size_t i) const;
   double& at(size_t i);
   const double& at(size_t i) const;

   // Sign
   const Vector3D& operator +(void) const;
   const Vector3D operator -(void) const;

   // Compare
   bool operator ==(const Vector3D& v) const;
   bool operator !=(const Vector3D& v) const;

   // Multiply
   const Vector3D operator *(double a) const;
   double operator *(const Vector3D& v) const;
   Vector3D& operator *=(double a);

   // Divide
   const Vector3D operator /(double a) const;
   Vector3D& operator /=(double a);

   // Add
   const Vector3D operator +(const Vector3D& v) const;
   Vector3D& operator +=(const Vector3D& v);

   // Subtract
   const Vector3D operator -(const Vector3D& v) const;
   Vector3D& operator -=(const Vector3D& v);

   // Compute Cross Product
   const Vector3D operator ^(const Vector3D& v) const;
   Vector3D& operator ^=(const Vector3D& v);

   // Compute Angle
   double operator |(const Vector3D& v) const;

   // Compute Norm
   using Vector<double>::norm;

   // Compute Unit Vector
   const Vector3D unit(void) const;

   // X Coordinate
   double x(void) const;
   void x(double x);

   // Y Coordinate
   double y(void) const;
   void y(double y);

   // Z Coordinate
   double z(void) const;
   void z(double z);

   // Friends
   friend Matrix3D;
};


// Constructor
inline CubeSim::Vector2D::Vector2D(void) : Vector<double>(2)
{
   // Initialize
   epsilon(Constant::EPSILON);
}


// Constructor
inline CubeSim::Vector2D::Vector2D(double x, double y) : Vector<double>(2)
{
   // Initialize
   this->x(x);
   this->y(y);

   // Initialize
   epsilon(Constant::EPSILON);
}


// Constructor
inline CubeSim::Vector2D::Vector2D(const Vector<double>& v) : Vector<double>(v)
{
   // Check Dimension
   if (v.dim() != 2)
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Initialize
   epsilon(Constant::EPSILON);
}


// Get Element
inline double& CubeSim::Vector2D::operator ()(size_t i)
{
   // Return Element
   return at(i);
}


// Get Element
inline double CubeSim::Vector2D::operator ()(size_t i) const
{
   // Return Element
   return at(i);
}


// Get Element
inline double& CubeSim::Vector2D::at(size_t i)
{
   // Check Index
   if ((i < 1) || (2 < i))
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Return Element
   return Vector<double>::at(i);
}


// Get Element
inline const double& CubeSim::Vector2D::at(size_t i) const
{
   // Check Index
   if ((i < 1) || (2 < i))
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Return Element
   return Vector<double>::at(i);
}


// Plus Sign
inline const CubeSim::Vector2D& CubeSim::Vector2D::operator +(void) const
{
   // Return Reference
   return *this;
}


// Minus Sign
inline const CubeSim::Vector2D CubeSim::Vector2D::operator -(void) const
{
   // Return Result
   return Vector<double>::operator -();
}


// Compare
inline bool CubeSim::Vector2D::operator ==(const Vector2D& v) const
{
   // Return Result
   return Vector<double>::operator ==(v);
}


// Compare
inline bool CubeSim::Vector2D::operator !=(const Vector2D& v) const
{
   // Return Result
   return Vector<double>::operator !=(v);
}


// Multiply
inline const CubeSim::Vector2D CubeSim::Vector2D::operator *(double a) const
{
   // Return Result
   return Vector<double>::operator *(a);
}


// Multiply
inline double CubeSim::Vector2D::operator *(const Vector2D& v) const
{
   // Return Result
   return Vector<double>::operator *(v);
}


// Multiply and assign
inline CubeSim::Vector2D& CubeSim::Vector2D::operator *=(double a)
{
   // Multiply and assign
   Vector<double>::operator *=(a);

   // Return Reference
   return *this;
}


// Divide
inline const CubeSim::Vector2D CubeSim::Vector2D::operator /(double a) const
{
   // Check Parameter
   if (a == 0.0)
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Return Result
   return Vector<double>::operator /(a);
}


// Divide and assign
inline CubeSim::Vector2D& CubeSim::Vector2D::operator /=(double a)
{
   // Check Parameter
   if (a == 0.0)
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Divide and assign
   Vector<double>::operator /=(a);

   // Return Reference
   return *this;
}


// Add
inline const CubeSim::Vector2D CubeSim::Vector2D::operator +(const Vector2D& v) const
{
   // Return Result
   return Vector<double>::operator +(v);
}


// Add and assign
inline CubeSim::Vector2D& CubeSim::Vector2D::operator +=(const Vector2D& v)
{
   // Add and assign
   Vector<double>::operator +=(v);

   // Return Reference
   return *this;
}


// Subtract
inline const CubeSim::Vector2D CubeSim::Vector2D::operator -(const Vector2D& v) const
{
   // Return Result
   return Vector<double>::operator -(v);
}


// Subtract and assign
inline CubeSim::Vector2D& CubeSim::Vector2D::operator -=(const Vector2D& v)
{
   // Subtract and assign
   Vector<double>::operator -=(v);

   // Return Reference
   return *this;
}


// Compute Z Coordinate of Cross Product
inline double CubeSim::Vector2D::operator ^(const Vector2D& v) const
{
   // Return Result
   return (x() * v.y() - y() * v.x());
}


// Get X Coordinate
inline double CubeSim::Vector2D::x(void) const
{
   // Return X Coordinate
   return (*this)(1);
}


// Set X Coordinate
inline void CubeSim::Vector2D::x(double x)
{
   // Set X Coordinate
   (*this)(1) = x;
}


// Get Y Coordinate
inline double CubeSim::Vector2D::y(void) const
{
   // Return Y Coordinate
   return (*this)(2);
}


// Set Y Coordinate
inline void CubeSim::Vector2D::y(double y)
{
   // Set Y Coordinate
   (*this)(2) = y;
}


// Constructor
inline CubeSim::Vector3D::Vector3D(void) : Vector<double>(3)
{
   // Initialize
   epsilon(Constant::EPSILON);
}


// Constructor
inline CubeSim::Vector3D::Vector3D(double x, double y, double z) : Vector<double>(3)
{
   // Initialize
   this->x(x);
   this->y(y);
   this->z(z);

   // Initialize
   epsilon(Constant::EPSILON);
}


// Constructor
inline CubeSim::Vector3D::Vector3D(const Vector2D& v) : Vector3D(v.x(), v.y(), 0.0)
{
}


// Constructor
inline CubeSim::Vector3D::Vector3D(const Vector<double>& v) : Vector<double>(v)
{
   // Check Dimension
   if (v.dim() != 3)
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Initialize
   epsilon(Constant::EPSILON);
}


// Get Element
inline double& CubeSim::Vector3D::operator ()(size_t i)
{
   // Return Element
   return at(i);
}


// Get Element
inline double CubeSim::Vector3D::operator ()(size_t i) const
{
   // Return Element
   return at(i);
}


// Get Element
inline double& CubeSim::Vector3D::at(size_t i)
{
   // Check Index
   if ((i < 1) || (3 < i))
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Return Element
   return Vector<double>::at(i);
}


// Get Element
inline const double& CubeSim::Vector3D::at(size_t i) const
{
   // Check Index
   if ((i < 1) || (3 < i))
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Return Element
   return Vector<double>::at(i);
}


// Plus Sign
inline const CubeSim::Vector3D& CubeSim::Vector3D::operator +(void) const
{
   // Return Reference
   return *this;
}


// Minus Sign
inline const CubeSim::Vector3D CubeSim::Vector3D::operator -(void) const
{
   // Return Result
   return Vector<double>::operator -();
}


// Compare
inline bool CubeSim::Vector3D::operator ==(const Vector3D& v) const
{
   // Return Result
   return Vector<double>::operator ==(v);
}


// Compare
inline bool CubeSim::Vector3D::operator !=(const Vector3D& v) const
{
   // Return Result
   return Vector<double>::operator !=(v);
}


// Multiply
inline const CubeSim::Vector3D CubeSim::Vector3D::operator *(double a) const
{
   // Return Result
   return Vector<double>::operator *(a);
}


// Multiply
inline double CubeSim::Vector3D::operator *(const Vector3D& v) const
{
   // Return Result
   return Vector<double>::operator *(v);
}


// Multiply and assign
inline CubeSim::Vector3D& CubeSim::Vector3D::operator *=(double a)
{
   // Multiply and assign
   Vector<double>::operator *=(a);

   // Return Reference
   return *this;
}


// Divide
inline const CubeSim::Vector3D CubeSim::Vector3D::operator /(double a) const
{
   // Check Parameter
   if (a == 0.0)
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Return Result
   return Vector<double>::operator /(a);
}


// Divide and assign
inline CubeSim::Vector3D& CubeSim::Vector3D::operator /=(double a)
{
   // Check Parameter
   if (a == 0.0)
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Divide and assign
   Vector<double>::operator /=(a);

   // Return Reference
   return *this;
}


// Add
inline const CubeSim::Vector3D CubeSim::Vector3D::operator +(const Vector3D& v) const
{
   // Return Result
   return Vector<double>::operator +(v);
}


// Add and assign
inline CubeSim::Vector3D& CubeSim::Vector3D::operator +=(const Vector3D& v)
{
   // Add and assign
   Vector<double>::operator +=(v);

   // Return Reference
   return *this;
}


// Subtract
inline const CubeSim::Vector3D CubeSim::Vector3D::operator -(const Vector3D& v) const
{
   // Return Result
   return Vector<double>::operator -(v);
}


// Subtract and assign
inline CubeSim::Vector3D& CubeSim::Vector3D::operator -=(const Vector3D& v)
{
   // Subtract and assign
   Vector<double>::operator -=(v);

   // Return Reference
   return *this;
}


// Compute Cross Product
inline const CubeSim::Vector3D CubeSim::Vector3D::operator ^(const Vector3D& v) const
{
   // Return Result
   return Vector<double>::operator ^(v);
}


// Compute Cross Product and assign
inline CubeSim::Vector3D& CubeSim::Vector3D::operator ^=(const Vector3D& v)
{
   // Compute Cross Product and assign
   Vector<double>::operator ^=(v);

   // Return Reference
   return *this;
}


// Get X Coordinate
inline double CubeSim::Vector3D::x(void) const
{
   // Return X Coordinate
   return (*this)(1);
}


// Set X Coordinate
inline void CubeSim::Vector3D::x(double x)
{
   // Set X Coordinate
   (*this)(1) = x;
}


// Get Y Coordinate
inline double CubeSim::Vector3D::y(void) const
{
   // Return Y Coordinate
   return (*this)(2);
}


// Set Y Coordinate
inline void CubeSim::Vector3D::y(double y)
{
   // Set Y Coordinate
   (*this)(2) = y;
}


// Get Z Coordinate
inline double CubeSim::Vector3D::z(void) const
{
   // Return Z Coordinate
   return (*this)(3);
}


// Set Z Coordinate
inline void CubeSim::Vector3D::z(double z)
{
   // Set Z Coordinate
   (*this)(3) = z;
}


// Multiply
inline const CubeSim::Vector2D CubeSim::operator *(double a, const Vector2D& v)
{
   // Multiply and return Result
   return (v * a);
}


// Multiply
inline const CubeSim::Vector3D CubeSim::operator *(double a, const Vector3D& v)
{
   // Multiply and return Result
   return (v * a);
}
