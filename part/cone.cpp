

// CUBESIM - PART - CONE


// Includes
#include "cone.hpp"
#include "../constant.hpp"


// Compute Moment of Inertia (Body Frame) [kg*m^2]
const CubeSim::Inertia CubeSim::Part::Cone::_inertia(void) const
{
   // Moment of Inertia
   Matrix3D I;

   // Compute Mass
   double mass = this->mass();

   // Compute Moment of Inertia
   I(1, 1) = I(2, 2) = 3.0 * mass * (_height * _height / 80.0 + 3.0 * _radius * _radius / 20.0);
   I(3, 3) = mass * 3.0 * _radius * _radius / 10.0;

   // Return Moment of Inertia
   return Inertia(I, mass, _center());
}
