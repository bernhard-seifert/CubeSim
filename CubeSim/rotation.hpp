

// CUBESIM - ROTATION


// Includes
#include "matrix.hpp"


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class Rotation
   class Rotation;

   // Rotate
   const Vector3D operator +(const Vector3D& vector, const Rotation& rotation);
   const Vector3D operator -(const Vector3D& vector, const Rotation& rotation);
   const Matrix3D operator +(const Matrix3D& matrix, const Rotation& rotation);
   const Matrix3D operator -(const Matrix3D& matrix, const Rotation& rotation);
   Vector3D& operator +=(Vector3D& vector, const Rotation& rotation);
   Vector3D& operator -=(Vector3D& vector, const Rotation& rotation);
   Matrix3D& operator +=(Matrix3D& matrix, const Rotation& rotation);
   Matrix3D& operator -=(Matrix3D& matrix, const Rotation& rotation);
}


// Class Rotation
class CubeSim::Rotation
{
public:

   // Constructor
   Rotation(double yaw, double pitch, double roll);
   Rotation(const Vector3D& axis, double angle);
   Rotation(const Vector3D& b1, const Vector3D& b2, const Vector3D& b3);
   Rotation(const Matrix3D& matrix = Matrix3D::IDENTITY);

   // Get Matrix
   operator const Matrix3D&(void) const;

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

   // Get Euler Angle [rad]
   double angle(void) const;

   // Get Euler Axis
   const Vector3D& axis(void) const;

   // Get Matrix
   const Matrix3D& matrix(void) const;

   // Get Pitch Angle [rad]
   double pitch(void) const;

   // Get Roll Angle [rad]
   double roll(void) const;

   // Get Yaw Angle [rad]
   double yaw(void) const;

private:

   // Compute Pitch, Roll, Yaw Angles [rad]
   void _angles(void) const;

   // Compute Euler Angle [rad] and Axis
   void _euler(void) const;

   // Variables
   Matrix3D _matrix;
   mutable double _angle;
   mutable double _pitch;
   mutable double _roll;
   mutable double _yaw;
   mutable Vector3D _axis;
};


// Constructor
inline CubeSim::Rotation::Rotation(const Matrix3D& matrix) : _angle(NAN), _pitch(NAN)
{
   // Check Matrix
   if ((matrix.transpose() * matrix) != Matrix3D::IDENTITY)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Initialize
   _matrix = matrix;
}


// Get Matrix
inline CubeSim::Rotation::operator const CubeSim::Matrix3D&(void) const
{
   // Return Matrix
   return _matrix;
}


// Plus Sign
inline const CubeSim::Rotation& CubeSim::Rotation::operator +(void) const
{
   // Return Reference
   return *this;
}


// Minus Sign
inline const CubeSim::Rotation CubeSim::Rotation::operator -(void) const
{
   // Rotation
   Rotation rotation;

   // Compute Rotation
   rotation._angle = -_angle;
   rotation._axis = _axis;
   rotation._matrix = _matrix.transpose();

   // Invalidate Pitch Angle
   rotation._pitch = NAN;

   // Return Rotation
   return rotation;
}


// Compare
inline bool CubeSim::Rotation::operator ==(const Rotation& rotation) const
{
   // Return Result
   return (_matrix == rotation._matrix);
}


// Compare
inline bool CubeSim::Rotation::operator !=(const Rotation& rotation) const
{
   // Return Result
   return !(*this == rotation);
}


// Rotate
inline const CubeSim::Rotation CubeSim::Rotation::operator +(const Rotation& rotation) const
{
   // Rotation
   Rotation rotation_;

   // Compute Matrix
   rotation_._matrix = rotation.matrix() * matrix();

   // Invalidate Euler and Pitch Angles
   rotation_._angle = NAN;
   rotation_._pitch = NAN;

   // Return Result
   return rotation_;
}


// Rotate and assign
inline CubeSim::Rotation& CubeSim::Rotation::operator +=(const Rotation& rotation)
{
   // Rotate, assign and return Reference
   return (*this = *this + rotation);
}


// Rotate
inline const CubeSim::Rotation CubeSim::Rotation::operator -(const Rotation& rotation) const
{
   // Rotation
   Rotation rotation_;

   // Compute Matrix
   rotation_._matrix = rotation.matrix().transpose() * matrix();

   // Invalidate Euler and Pitch Angles
   rotation_._angle = NAN;
   rotation_._pitch = NAN;

   // Return Result
   return rotation_;
}


// Rotate and assign
inline CubeSim::Rotation& CubeSim::Rotation::operator -=(const Rotation& rotation)
{
   // Rotate, assign and return Reference
   return (*this = *this - rotation);
}


// Get Euler Angle [rad]
inline double CubeSim::Rotation::angle(void) const
{
   // Compute Euler Angle and Axis
   _euler();

   // Return Euler Angle
   return _angle;
}


// Get Euler Axis
inline const CubeSim::Vector3D& CubeSim::Rotation::axis(void) const
{
   // Compute Euler Angle and Axis
   _euler();

   // Return Euler Axis
   return _axis;
}


// Get Matrix
inline const CubeSim::Matrix3D& CubeSim::Rotation::matrix(void) const
{
   // Return Matrix
   return _matrix;
}


// Get Pitch Angle [rad]
inline double CubeSim::Rotation::pitch(void) const
{
   // Compute Pitch, Roll, Yaw Angles
   _angles();

   // Return Pitch Angle
   return _pitch;
}


// Get Roll Angle [rad]
inline double CubeSim::Rotation::roll(void) const
{
   // Compute Pitch, Roll, Yaw Angles
   _angles();

   // Return Roll Angle
   return _roll;
}


// Get Yaw Angle [rad]
inline double CubeSim::Rotation::yaw(void) const
{
   // Compute Pitch, Roll, Yaw Angles
   _angles();

   // Return Yaw Angle
   return _yaw;
}


// Rotate Vector
inline const CubeSim::Vector3D CubeSim::operator +(const CubeSim::Vector3D& vector, const CubeSim::Rotation& rotation)
{
   // Rotate and return Result
   return (rotation.matrix() * vector);
}


// Rotate Vector
inline const CubeSim::Vector3D CubeSim::operator -(const CubeSim::Vector3D& vector, const CubeSim::Rotation& rotation)
{
   // Rotate and return Result
   return (rotation.matrix().transpose() * vector);
}


// Rotate Matrix
inline const CubeSim::Matrix3D CubeSim::operator +(const Matrix3D& matrix, const Rotation& rotation)
{
   // Rotate and return Result
   return (rotation.matrix() * matrix * rotation.matrix().transpose());
}


// Rotate Matrix
inline const CubeSim::Matrix3D CubeSim::operator -(const CubeSim::Matrix3D& matrix, const CubeSim::Rotation& rotation)
{
   // Rotate and return Result
   return (rotation.matrix().transpose() * matrix * rotation.matrix());
}


// Rotate and assign Vector
inline CubeSim::Vector3D& CubeSim::operator +=(Vector3D& vector, const Rotation& rotation)
{
   // Rotate Vector, assign and return Reference
   return (vector = vector + rotation);
}


// Rotate and assign Vector
inline CubeSim::Vector3D& CubeSim::operator -=(Vector3D& vector, const Rotation& rotation)
{
   // Rotate Vector, assign and return Reference
   return (vector = vector - rotation);
}


// Rotate and assign Matrix
inline CubeSim::Matrix3D& CubeSim::operator +=(Matrix3D& matrix, const Rotation& rotation)
{
   // Rotate Matrix, assign and return Reference
   return (matrix = matrix + rotation);
}


// Rotate and assign Matrix
inline CubeSim::Matrix3D& CubeSim::operator -=(Matrix3D& matrix, const Rotation& rotation)
{
   // Rotate Matrix, assign and return Reference
   return (matrix = matrix - rotation);
}
