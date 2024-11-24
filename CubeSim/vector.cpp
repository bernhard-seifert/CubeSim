

// CUBESIM - VECTOR


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
#include <algorithm>
#include "vector.hpp"


// 2D Unit Vectors
const CubeSim::Vector2D CubeSim::Vector2D::X(1.0, 0.0);
const CubeSim::Vector2D CubeSim::Vector2D::Y(0.0, 1.0);


// Compute Angle
double CubeSim::Vector2D::operator |(const Vector2D& v) const
{
   // Compute Norms
   double norm1 = norm();
   double norm2 = v.norm();

   // Check Norms
   if (norm1 == 0.0)
   {
      // Exception
      throw CubeSim::Exception::Failed();
   }
   else if (norm2 == 0.0)
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Compute and return Angle
   return acos(*this * v / norm1 / norm2);
}


// Compute Unit Vector
const CubeSim::Vector2D CubeSim::Vector2D::unit(void) const
{
   // Compute Norm
   double norm_ = norm();

   // Check Norm
   if (norm_ == 0.0)
   {
      // Exception
      throw CubeSim::Exception::Failed();
   }

   // Return Result
   return Vector2D(x() / norm_, y() / norm_);
}


// 3D Unit Vectors
const CubeSim::Vector3D CubeSim::Vector3D::X(1.0, 0.0, 0.0);
const CubeSim::Vector3D CubeSim::Vector3D::Y(0.0, 1.0, 0.0);
const CubeSim::Vector3D CubeSim::Vector3D::Z(0.0, 0.0, 1.0);


// Compute Angle
double CubeSim::Vector3D::operator |(const Vector3D& v) const
{
   // Compute Norms
   double norm1 = norm();
   double norm2 = v.norm();

   // Check Norms
   if (norm1 == 0.0)
   {
      // Exception
      throw CubeSim::Exception::Failed();
   }
   else if (norm2 == 0.0)
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Compute and return Angle (catch numeric Errors)
   return acos(std::clamp(*this * v / norm1 / norm2, -1.0, 1.0));
}


// Compute Unit Vector
const CubeSim::Vector3D CubeSim::Vector3D::unit(void) const
{
   // Compute Norm
   double norm_ = norm();

   // Check Norm
   if (norm_ == 0.0)
   {
      // Exception
      throw CubeSim::Exception::Failed();
   }

   // Return Result
   return Vector3D(x() / norm_, y() / norm_, z() / norm_);
}
