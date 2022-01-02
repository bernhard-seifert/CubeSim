

// CUBESIM - ROTATION


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
#include "rotation.hpp"


// Constructor
CubeSim::Rotation::Rotation(double yaw, double pitch, double roll) : _angle(NAN), _pitch(pitch), _roll(roll), _yaw(yaw)
{
   // Compute Matrix
   _matrix(1, 1) = cos(yaw) * cos(pitch);
   _matrix(1, 2) = cos(yaw) * sin(pitch) * sin(roll) - sin(yaw) * cos(roll);
   _matrix(1, 3) = cos(yaw) * sin(pitch) * cos(roll) + sin(yaw) * sin(roll);
   _matrix(2, 1) = sin(yaw) * cos(pitch);
   _matrix(2, 2) = sin(yaw) * sin(pitch) * sin(roll) + cos(yaw) * cos(roll);
   _matrix(2, 3) = sin(yaw) * sin(pitch) * cos(roll) - cos(yaw) * sin(roll);
   _matrix(3, 1) = -sin(pitch);
   _matrix(3, 2) = cos(pitch) * sin(roll);
   _matrix(3, 3) = cos(pitch) * cos(roll);
}


// Constructor
CubeSim::Rotation::Rotation(const Vector3D& axis, double angle) : _angle(angle), _pitch(NAN)
{
   // Check Angle
   if (angle == 0.0)
   {
      // Initialize
      _axis = Vector3D::Z;
      _matrix = Matrix3D::IDENTITY;
   }
   else
   {
      // Check Axis
      if (axis == Vector3D())
      {
         // Exception
         throw Exception::Parameter();
      }

      // Initialize
      _axis = axis.unit();

      // Compute Sine and Cosine
      double sin_ = sin(angle);
      double cos_ = cos(angle);

      // Compute Matrix
      _matrix(1, 1) = _axis.x() * _axis.x() * (1.0 - cos_) + cos_;
      _matrix(1, 2) = _axis.x() * _axis.y() * (1.0 - cos_) - _axis.z() * sin_;
      _matrix(1, 3) = _axis.x() * _axis.z() * (1.0 - cos_) + _axis.y() * sin_;
      _matrix(2, 1) = _axis.x() * _axis.y() * (1.0 - cos_) + _axis.z() * sin_;
      _matrix(2, 2) = _axis.y() * _axis.y() * (1.0 - cos_) + cos_;
      _matrix(2, 3) = _axis.y() * _axis.z() * (1.0 - cos_) - _axis.x() * sin_;
      _matrix(3, 1) = _axis.x() * _axis.z() * (1.0 - cos_) - _axis.y() * sin_;
      _matrix(3, 2) = _axis.y() * _axis.z() * (1.0 - cos_) + _axis.x() * sin_;
      _matrix(3, 3) = _axis.z() * _axis.z() * (1.0 - cos_) + cos_;
   }
}


// Constructor
CubeSim::Rotation::Rotation(const Vector3D& b1, const Vector3D& b2, const Vector3D& b3)
{
   // Check Base Vectors
   if ((b1 == Vector3D()) || (b2 == Vector3D()) || (b3 == Vector3D()))
   {
      // Exception
      throw Exception::Parameter();
   }

   // Compute Unit Vectors
   Vector3D b1_ = b1.unit();
   Vector3D b2_ = b2.unit();
   Vector3D b3_ = b3.unit();

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
   if ((_matrix.transpose() * _matrix) != Matrix3D::IDENTITY)
   {
      // Exception
      throw Exception::Parameter();
   }
}


// Compute Pitch, Roll, Yaw Angles [rad]
void CubeSim::Rotation::_angles(void) const
{
   // Check Pitch Angle
   if (isnan(_pitch))
   {
      // Compute Pitch, Roll, Yaw Angles
      _pitch = atan2(-_matrix(3, 1), sqrt(_matrix(3, 2) * _matrix(3, 2) + _matrix(3, 3) * _matrix(3, 3)));
      _roll = atan2(_matrix(3, 2), _matrix(3, 3));
      _yaw = atan2(_matrix(2, 1), _matrix(1, 1));
   }
}


// Compute Euler Angle [rad] and Axis
void CubeSim::Rotation::_euler(void) const
{
   // Check Euler Angle
   if (isnan(_angle))
   {
      // Compute Cosine of Euler Angle
      double cos_ = 0.5 * (_matrix(1, 1) + _matrix(2, 2) + _matrix(3, 3) - 1.0);

      // Check Cosine of Euler Angle
      if (1.0 <= cos_)
      {
         // Set Euler Angle and Axis
         _angle = 0.0;
         _axis = Vector3D::Z;
      }
      else if (cos_ <= -1.0)
      {
         // Set Euler Angle
         _angle = Constant::PI;

         // Reset Euler Axis
         _axis = Vector3D();

         // Parse Columns
         for (size_t i = 1; i <= 3; ++i)
         {
            // Compute Axis
            Vector3D axis = Vector3D(_matrix(1, i) + ((i == 1) ? 1.0 : 0.0), _matrix(2, i) + ((i == 2) ? 1.0 : 0.0),
               _matrix(3, i) + ((i == 3) ? 1.0 : 0.0));

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
         double sin_ = sqrt(1.0 - cos_ * cos_);

         // Compute Euler Angle and Axis
         _angle = acos(cos_);
         _axis = Vector3D((_matrix(3, 2) - _matrix(2, 3)) / 2.0 / sin_, (_matrix(1, 3) - _matrix(3, 1)) / 2.0 / sin_,
            (_matrix(2, 1) - _matrix(1, 2)) / 2.0 / sin_);
      }
   }
}
