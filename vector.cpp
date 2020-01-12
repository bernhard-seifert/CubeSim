

// CUBESIM - VECTOR


// Includes
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

   // Compute and return Angle
   return acos(*this * v / norm1 / norm2);
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
