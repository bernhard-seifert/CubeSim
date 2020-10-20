

// CUBESIM - PART - PRISM


// Includes
#include "prism.hpp"


// Compute Moment of Inertia (Body Frame) [kg*m^2]
const CubeSim::Inertia CubeSim::Part::Prism::_inertia(void) const
{
   // Mass, Integrals
   double mass = 0.0;
   double xx = 0.0, xy = 0.0, yy = 0.0, zz = 0.0;

   // Parse Vertices
   for (size_t i = 0; i < _base.vertex().size(); ++i)
   {
      // Get Vertices of Triangle
      const Vector2D& v1 = _base.vertex(i);
      const Vector2D& v2 = _base.vertex((i + 1) % _base.vertex().size());

      // Compute Mass of triangular Prism
      double mass_ = abs(v1 ^ v2) / 2.0 * _height * _material.density();

      // Update Mass
      mass += mass_;

      // Update Integrals
      xx += mass_ * (v1.x() * v1.x() + v1.x() * v2.x() + v2.x() * v2.x()) / 6.0;
      xy += mass_ * (v1.x() * (2.0 * v1.y() + v2.y()) + v2.x() * (v1.y() + 2.0 * v2.y())) / 12.0;
      yy += mass_ * (v1.y() * v1.y() + v1.y() * v2.y() + v2.y() * v2.y()) / 6.0;
      zz += mass_ * _height * _height / 12.0;
   }

   // Computer Center
   Vector2D center = _base.center();

   // Translate Integrals
   xx -= mass * center.x() * center.x();
   xy -= mass * center.x() * center.y();
   yy -= mass * center.y() * center.y();

   // Moment of Inertia
   Matrix3D I;

   // Compute Moment of Inertia
   I(1, 1) = yy + zz;
   I(1, 2) = I(2, 1) = -xy;
   I(2, 2) = xx + zz;
   I(3, 3) = xx + yy;

   // Return Moment of Inertia
   return Inertia(I, mass, Vector3D(center.x(), center.y(), _height / 2.0));
}
