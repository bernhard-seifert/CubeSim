

// CUBESIM - INERTIA


// Includes
#include "inertia.hpp"


// Compute Inertia (around arbitrary Axis and Origin) [kg*m^2]
double CubeSim::Inertia::operator ()(const Vector3D& axis, const Vector3D& origin) const
{
   // Check Axis
   if (axis == Vector3D())
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Normalize Axis
   Vector3D axis_ = axis.unit();

   // Check Origin
   if (origin == _center)
   {
      // Compute and return Momentum of Inertia
      return (static_cast<const Matrix3D&>(*this) * axis_ * axis_);
   }

   // Compute Vector from Origin to Center
   Vector3D center = _center - origin;

   // Compute Distance from Center to Axis
   Vector3D distance = center - (center * axis_) * axis_;

   // Check distance
   if (distance == Vector3D())
   {
      // Compute and return Momentum of Inertia
      return (static_cast<const Matrix3D&>(*this) * axis_ * axis_);
   }

   // Compute Translation Matrix
   Matrix3D T;
   T(1, 1) = _mass * (distance.y() * distance.y() + distance.z() * distance.z());
   T(1, 2) = T(2, 1) = -_mass * distance.x() * distance.y();
   T(1, 3) = T(3, 1) = -_mass * distance.x() * distance.z();
   T(2, 2) = _mass * (distance.x() * distance.x() + distance.z() * distance.z());
   T(2, 3) = T(3, 2) = -_mass * distance.y() * distance.z();
   T(3, 3) = _mass * (distance.x() * distance.x() + distance.y() * distance.y());

   // Compute and return Momentum of Inertia
   return ((static_cast<const Matrix3D&>(*this) + T) * axis_ * axis_);
}


// Compute Inertia Matrix
CubeSim::Inertia::operator const Matrix3D(void) const
{
   // Compute Translation Matrix
   Matrix3D T;
   T(1, 1) = _mass * (_center.y() * _center.y() + _center.z() * _center.z());
   T(1, 2) = T(2, 1) = -_mass * _center.x() * _center.y();
   T(1, 3) = T(3, 1) = -_mass * _center.x() * _center.z();
   T(2, 2) = _mass * (_center.x() * _center.x() + _center.z() * _center.z());
   T(2, 3) = T(3, 2) = -_mass * _center.y() * _center.z();
   T(3, 3) = _mass * (_center.x() * _center.x() + _center.y() * _center.y());

   // Compute and return Momentum of Inertia
   return (static_cast<const Matrix3D&>(*this) + T);
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

   // Moment of Inertia
   Matrix3D I;

   // Inertia List
   std::vector<const Inertia*> inertia_ = {this, &inertia};

   // Parse Inertia List
   for (auto inertia__ = inertia_.begin(); inertia__ != inertia_.end(); ++inertia__)
   {
      // Update Moment of Inertia
      I += **inertia__;

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
         I += T;
      }
   }

   // Update Moment of Inertia, Center, Mass
   static_cast<Matrix3D&>(*this) = I;
   _center = center;
   _mass = mass;

   // Return Reference
   return *this;
}
