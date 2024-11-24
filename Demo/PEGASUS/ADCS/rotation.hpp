

// ADCS - ROTATION


// Includes
#include "matrix.hpp"


// Preprocessor Directives
#pragma once


// Namespace ADCS
namespace ADCS
{
   // Class Rotation
   class Rotation;

   // Rotate
   const Vector operator +(const Vector& vector, const Rotation& rotation);
   const Vector operator -(const Vector& vector, const Rotation& rotation);
   const Matrix operator +(const Matrix& matrix, const Rotation& rotation);
   const Matrix operator -(const Matrix& matrix, const Rotation& rotation);
   Vector& operator +=(Vector& vector, const Rotation& rotation);
   Vector& operator -=(Vector& vector, const Rotation& rotation);
   Matrix& operator +=(Matrix& matrix, const Rotation& rotation);
   Matrix& operator -=(Matrix& matrix, const Rotation& rotation);
}


// Class Rotation
class ADCS::Rotation
{
public:

   // Constructor
   Rotation(const numeric_t& yaw, const numeric_t& pitch, const numeric_t& roll);
   Rotation(const Vector& axis, const numeric_t& angle);
   Rotation(const Vector& b1, const Vector& b2, const Vector& b3);
   Rotation(const Matrix& matrix = Matrix::IDENTITY);

   // Get Matrix
   operator const Matrix&(void) const;

   // Sign
   const Rotation& operator +(void) const;
   const Rotation operator -(void) const;

   // Compare
   bool operator ==(const Rotation& rotation) const;
   bool operator !=(const Rotation& rotation) const;

   // Rotate
   const Rotation operator +(const Rotation& rotation) const;
   const Rotation operator -(const Rotation& rotation) const;
   Rotation& operator +=(const Rotation& rotation);
   Rotation& operator -=(const Rotation& rotation);

   // Get Euler Angle
   const numeric_t& angle(void) const;

   // Get Euler Axis
   const Vector& axis(void) const;

   // Get Matrix
   const Matrix& matrix(void) const;

   // Get Pitch Angle
   const numeric_t& pitch(void) const;

   // Get Roll Angle
   const numeric_t& roll(void) const;

   // Get Yaw Angle
   const numeric_t& yaw(void) const;

private:

   // Compute Pitch, Roll, Yaw Angles
   void _angles(void) const;

   // Compute Euler Angle and Axis
   void _euler(void) const;

   // Invalidate
   void _invalidate(void);

   // Variables
   Matrix _matrix;
   mutable numeric_t _angle;
   mutable numeric_t _pitch;
   mutable numeric_t _roll;
   mutable numeric_t _yaw;
   mutable Vector _axis;
};


// Get Matrix
inline ADCS::Rotation::operator const ADCS::Matrix&(void) const
{
   // Return Matrix
   return _matrix;
}


// Plus Sign
inline const ADCS::Rotation& ADCS::Rotation::operator +(void) const
{
   // Return Reference
   return *this;
}


// Compare
inline bool ADCS::Rotation::operator ==(const Rotation& rotation) const
{
   // Return Result
   return (_matrix == rotation._matrix);
}


// Compare
inline bool ADCS::Rotation::operator !=(const Rotation& rotation) const
{
   // Return Result
   return !(*this == rotation);
}


// Rotate and assign
inline ADCS::Rotation& ADCS::Rotation::operator +=(const Rotation& rotation)
{
   // Rotate, assign and return Reference
   return (*this = *this + rotation);
}


// Rotate and assign
inline ADCS::Rotation& ADCS::Rotation::operator -=(const Rotation& rotation)
{
   // Rotate, assign and return Reference
   return (*this = *this - rotation);
}


// Get Euler Angle
inline const ADCS::numeric_t& ADCS::Rotation::angle(void) const
{
   // Compute Euler Angle and Axis
   _euler();

   // Return Euler Angle
   return _angle;
}


// Get Euler Axis
inline const ADCS::Vector& ADCS::Rotation::axis(void) const
{
   // Compute Euler Angle and Axis
   _euler();

   // Return Euler Axis
   return _axis;
}


// Get Matrix
inline const ADCS::Matrix& ADCS::Rotation::matrix(void) const
{
   // Return Matrix
   return _matrix;
}


// Get Pitch Angle
inline const ADCS::numeric_t& ADCS::Rotation::pitch(void) const
{
   // Compute Pitch, Roll, Yaw Angles
   _angles();

   // Return Pitch Angle
   return _pitch;
}


// Get Roll Angle
inline const ADCS::numeric_t& ADCS::Rotation::roll(void) const
{
   // Compute Pitch, Roll, Yaw Angles
   _angles();

   // Return Roll Angle
   return _roll;
}


// Get Yaw Angle
inline const ADCS::numeric_t& ADCS::Rotation::yaw(void) const
{
   // Compute Pitch, Roll, Yaw Angles
   _angles();

   // Return Yaw Angle
   return _yaw;
}


// Rotate Vector
inline const ADCS::Vector ADCS::operator +(const Vector& vector, const Rotation& rotation)
{
   // Rotate and return Result
   return (rotation.matrix() * vector);
}


// Rotate Vector
inline const ADCS::Vector ADCS::operator -(const Vector& vector, const Rotation& rotation)
{
   // Rotate and return Result
   return (rotation.matrix().transpose() * vector);
}


// Rotate Matrix
inline const ADCS::Matrix ADCS::operator +(const Matrix& matrix, const Rotation& rotation)
{
   // Rotate and return Result
   return (rotation.matrix() * matrix * rotation.matrix().transpose());
}


// Rotate Matrix
inline const ADCS::Matrix ADCS::operator -(const Matrix& matrix, const Rotation& rotation)
{
   // Rotate and return Result
   return (rotation.matrix().transpose() * matrix * rotation.matrix());
}


// Rotate and assign Vector
inline ADCS::Vector& ADCS::operator +=(Vector& vector, const Rotation& rotation)
{
   // Rotate Vector, assign and return Reference
   return (vector = vector + rotation);
}


// Rotate and assign Vector
inline ADCS::Vector& ADCS::operator -=(Vector& vector, const Rotation& rotation)
{
   // Rotate Vector, assign and return Reference
   return (vector = vector - rotation);
}


// Rotate and assign Matrix
inline ADCS::Matrix& ADCS::operator +=(Matrix& matrix, const Rotation& rotation)
{
   // Rotate Matrix, assign and return Reference
   return (matrix = matrix + rotation);
}


// Rotate and assign Matrix
inline ADCS::Matrix& ADCS::operator -=(Matrix& matrix, const Rotation& rotation)
{
   // Rotate Matrix, assign and return Reference
   return (matrix = matrix - rotation);
}
