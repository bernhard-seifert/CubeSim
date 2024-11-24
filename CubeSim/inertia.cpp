

// CUBESIM - INERTIA


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
#include "inertia.hpp"


// Compute Inertia around arbitrary Axis and Pivot [kg*m^2]
double CubeSim::Inertia::operator ()(const Vector3D& axis, const Vector3D& pivot) const
{
   // Check Axis
   if (axis == Vector3D())
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Normalize Axis
   Vector3D axis_ = axis.unit();

   // Check Pivot
   if (pivot == _center)
   {
      // Compute and return Moment of Inertia
      return (_matrix * axis_ * axis_);
   }

   // Compute Vector from Pivot to Center
   Vector3D center = _center - pivot;

   // Compute Distance from Center to Axis
   Vector3D distance = center - (center * axis_) * axis_;

   // Check distance
   if (distance == Vector3D())
   {
      // Compute and return Moment of Inertia
      return (_matrix * axis_ * axis_);
   }

   // Compute Translation Matrix
   Matrix3D T;
   T(1, 1) = _mass * (distance.y() * distance.y() + distance.z() * distance.z());
   T(1, 2) = T(2, 1) = -_mass * distance.x() * distance.y();
   T(1, 3) = T(3, 1) = -_mass * distance.x() * distance.z();
   T(2, 2) = _mass * (distance.x() * distance.x() + distance.z() * distance.z());
   T(2, 3) = T(3, 2) = -_mass * distance.y() * distance.z();
   T(3, 3) = _mass * (distance.x() * distance.x() + distance.y() * distance.y());

   // Compute and return Moment of Inertia
   return ((_matrix + T) * axis_ * axis_);
}


// Compute Moment of Inertia Matrix
CubeSim::Inertia::operator const CubeSim::Matrix3D(void) const
{
   // Compute Translation Matrix
   Matrix3D T;
   T(1, 1) = _mass * (_center.y() * _center.y() + _center.z() * _center.z());
   T(1, 2) = T(2, 1) = -_mass * _center.x() * _center.y();
   T(1, 3) = T(3, 1) = -_mass * _center.x() * _center.z();
   T(2, 2) = _mass * (_center.x() * _center.x() + _center.z() * _center.z());
   T(2, 3) = T(3, 2) = -_mass * _center.y() * _center.z();
   T(3, 3) = _mass * (_center.x() * _center.x() + _center.y() * _center.y());

   // Compute and return Moment of Inertia Matrix
   return (_matrix + T);
}


// Add and assign
CubeSim::Inertia& CubeSim::Inertia::operator +=(const Inertia& inertia)
{
   // Center
   Vector3D center;

   // Compute Mass
   double mass = _mass + inertia._mass;

   // Check Mass
   if (0.0 < mass)
   {
      // Compute Center
      center = (_center * _mass + inertia._center * inertia._mass) / mass;
   }

   // Moment of Inertia Matrix
   Matrix3D matrix;

   // Inertia List
   std::vector<const Inertia*> inertia_ = {this, &inertia};

   // Parse Inertia List
   for (auto inertia__ = inertia_.begin(); inertia__ != inertia_.end(); ++inertia__)
   {
      // Update Moment of Inertia Matrix
      matrix += (*inertia__)->_matrix;

      // Compute Distance
      Vector3D distance = (*inertia__)->_center - center;

      // Check Distance
      if (distance != Vector3D())
      {
         // Compute Translation Matrix
         Matrix3D T;
         T(1, 1) = (*inertia__)->_mass * (distance.y() * distance.y() + distance.z() * distance.z());
         T(1, 2) = T(2, 1) = -(*inertia__)->_mass * distance.x() * distance.y();
         T(1, 3) = T(3, 1) = -(*inertia__)->_mass * distance.x() * distance.z();
         T(2, 2) = (*inertia__)->_mass * (distance.x() * distance.x() + distance.z() * distance.z());
         T(2, 3) = T(3, 2) = -(*inertia__)->_mass * distance.y() * distance.z();
         T(3, 3) = (*inertia__)->_mass * (distance.x() * distance.x() + distance.y() * distance.y());

         // Update Moment of Inertia
         matrix += T;
      }
   }

   // Update Moment of Inertia Matrix, Center, Mass
   _matrix = matrix;
   _center = center;
   _mass = mass;

   // Return Reference
   return *this;
}
