

// CUBESIM - PART - CYLINDER


// Includes
#include "cylinder.hpp"
#include "../constant.hpp"


// Compute Moment of Inertia (Body Frame) [kg*m^2]
const CubeSim::Inertia CubeSim::Part::Cylinder::_inertia(void) const
{
   // Moment of Inertia
   Matrix3D I;

   // Compute Mass
   double mass = this->mass();

   // Compute Moment of Inertia
   I(1, 1) = I(2, 2) = mass * (3.0 * _radius * _radius + _height * _height) / 12.0;
   I(3, 3) = mass * _radius * _radius / 2.0;

   // Return Moment of Inertia
   return Inertia(I, mass, _center());
}
