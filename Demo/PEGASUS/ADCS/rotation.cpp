

// ROTATION


// Includes
#include <cmath>
#include "constant.hpp"
#include "rotation.hpp"


// Constructor
ADCS::Rotation::Rotation(const numeric_t& yaw, const numeric_t& pitch, const numeric_t& roll) : _angle(NAN),
   _pitch(pitch), _roll(roll), _yaw(yaw)
{
   // Compute Matrix
   _matrix(1, 1) = std::cos(yaw) * std::cos(pitch);
   _matrix(1, 2) = std::cos(yaw) * std::sin(pitch) * std::sin(roll) - std::sin(yaw) * std::cos(roll);
   _matrix(1, 3) = std::cos(yaw) * std::sin(pitch) * std::cos(roll) + std::sin(yaw) * std::sin(roll);
   _matrix(2, 1) = std::sin(yaw) * std::cos(pitch);
   _matrix(2, 2) = std::sin(yaw) * std::sin(pitch) * std::sin(roll) + std::cos(yaw) * std::cos(roll);
   _matrix(2, 3) = std::sin(yaw) * std::sin(pitch) * std::cos(roll) - std::cos(yaw) * std::sin(roll);
   _matrix(3, 1) = -std::sin(pitch);
   _matrix(3, 2) = std::cos(pitch) * std::sin(roll);
   _matrix(3, 3) = std::cos(pitch) * std::cos(roll);
}


// Constructor
ADCS::Rotation::Rotation(const Vector& axis, const numeric_t& angle) : _angle(angle), _pitch(NAN)
{
   // Check Axis
   if (axis == Vector())
   {
      // Invalidate
      _invalidate();

      // Return
      return;
   }

   // Initialize
   _axis = axis.unit();

   // Compute Sine and Cosine
   numeric_t sin_ = std::sin(angle);
   numeric_t cos_ = std::cos(angle);

   // Compute Matrix
   _matrix(1, 1) = _axis.x() * _axis.x() * (1 - cos_) + cos_;
   _matrix(1, 2) = _axis.x() * _axis.y() * (1 - cos_) - _axis.z() * sin_;
   _matrix(1, 3) = _axis.x() * _axis.z() * (1 - cos_) + _axis.y() * sin_;
   _matrix(2, 1) = _axis.x() * _axis.y() * (1 - cos_) + _axis.z() * sin_;
   _matrix(2, 2) = _axis.y() * _axis.y() * (1 - cos_) + cos_;
   _matrix(2, 3) = _axis.y() * _axis.z() * (1 - cos_) - _axis.x() * sin_;
   _matrix(3, 1) = _axis.x() * _axis.z() * (1 - cos_) - _axis.y() * sin_;
   _matrix(3, 2) = _axis.y() * _axis.z() * (1 - cos_) + _axis.x() * sin_;
   _matrix(3, 3) = _axis.z() * _axis.z() * (1 - cos_) + cos_;
}


// Constructor
ADCS::Rotation::Rotation(const Vector& b1, const Vector& b2, const Vector& b3)
{
   // Check Base Vectors
   if ((b1 == Vector()) || (b2 == Vector()) || (b3 == Vector()))
   {
      // Invalidate
      _invalidate();

      // Return
      return;
   }

   // Compute Unit Vectors
   Vector b1_ = b1.unit();
   Vector b2_ = b2.unit();
   Vector b3_ = b3.unit();

   // Compute Matrix
   _matrix(1, 1) = b1_.x();
   _matrix(1, 2) = b2_.x();
   _matrix(1, 3) = b3_.x();
   _matrix(2, 1) = b1_.y();
   _matrix(2, 2) = b2_.y();
   _matrix(2, 3) = b3_.y();
   _matrix(3, 1) = b1_.z();
   _matrix(3, 2) = b2_.z();
   _matrix(3, 3) = b3_.z();

   // Check Matrix
   if ((_matrix.transpose() * _matrix) != Matrix::IDENTITY)
   {
      // Invalidate
      _invalidate();
   }
}


// Constructor
ADCS::Rotation::Rotation(const Matrix& matrix) : _matrix(matrix), _angle(NAN), _pitch(NAN)
{
   // Check Matrix
   if ((matrix.transpose() * matrix) != Matrix::IDENTITY)
   {
      // Invalidate
      _invalidate();
   }
}


// Minus Sign
const ADCS::Rotation ADCS::Rotation::operator -(void) const
{
   // Rotation
   Rotation rotation;

   // Compute Rotation
   rotation._angle = -_angle;
   rotation._axis = _axis;
   rotation._pitch = NAN;
   rotation._matrix = _matrix.transpose();

   // Return Rotation
   return rotation;
}


// Rotate
const ADCS::Rotation ADCS::Rotation::operator +(const Rotation& rotation) const
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


// Rotate
const ADCS::Rotation ADCS::Rotation::operator -(const Rotation& rotation) const
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


// Compute Pitch, Roll, Yaw Angles
void ADCS::Rotation::_angles(void) const
{
   // Check Pitch Angle
   if (std::isnan(_pitch))
   {
      // Compute Pitch, Roll, Yaw Angles
      _pitch = atan2(-_matrix(3, 1), sqrt(_matrix(3, 2) * _matrix(3, 2) + _matrix(3, 3) * _matrix(3, 3)));
      _roll = atan2(_matrix(3, 2), _matrix(3, 3));
      _yaw = atan2(_matrix(2, 1), _matrix(1, 1));
   }
}


// Compute Euler Angle and Axis
void ADCS::Rotation::_euler(void) const
{
   // Check Euler Angle
   if (std::isnan(_angle))
   {
      // Compute Cosine of Euler Angle
      numeric_t cos_ = (_matrix(1, 1) + _matrix(2, 2) + _matrix(3, 3) - 1) / 2;

      // Check Cosine of Euler Angle
      if (cos_ == 1)
      {
         // Set Euler Angle and Axis
         _angle = 0.0;
         _axis = Vector::Z;
      }
      else if (cos_ == -1)
      {
         // Set Euler Angle
         _angle = Constant::PI;

         // Reset Euler Axis
         _axis = Vector();

         // Parse Columns
         for (uint8_t i = 1; i <= 3; ++i)
         {
            // Compute Axis
            Vector axis = Vector(_matrix(1, i) + ((i == 1) ? 1 : 0), _matrix(2, i) + ((i == 2) ? 1 : 0),
               _matrix(3, i) + ((i == 3) ? 1 : 0));

            // Compare Euler Axes
            if (_axis.norm() < axis.norm())
            {
               // Set Euler Axis
               _axis = axis;
            }
         }

         // Compute Unit Vector
         _axis = _axis.unit();
      }
      else
      {
         // Compute Sine
         numeric_t sin_ = sqrt(1 - cos_ * cos_);

         // Compute Euler Angle and Axis
         _angle = acos(cos_);
         _axis = Vector((_matrix(3, 2) - _matrix(2, 3)) / 2 / sin_, (_matrix(1, 3) - _matrix(3, 1)) / 2 / sin_,
            (_matrix(2, 1) - _matrix(1, 2)) / 2 / sin_);
      }
   }
}


// Invalidate
void ADCS::Rotation::_invalidate(void)
{
   // Invalidate Members
   _angle = NAN;
   _pitch = NAN;
   _roll = NAN;
   _yaw = NAN;
   _axis = Vector(NAN);
   _matrix = Matrix(NAN);
}
