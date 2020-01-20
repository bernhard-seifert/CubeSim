

// CUBESIM - PART - BOX


// Includes
#include "box.hpp"


// Compute Momentum of Inertia (Body Frame) [kg*m^2]
const CubeSim::Inertia CubeSim::Part::Box::_inertia(void) const
{
   // Momentum of Inertia
   Matrix3D I;

   // Compute Mass
   double mass = this->mass();

   // Compute Momentum of Inertia
   I(1, 1) = mass * (_width * _width + _height * _height) / 12.0;
   I(2, 2) = mass * (_length * _length + _height * _height) / 12.0;
   I(3, 3) = mass * (_length * _length + _width * _width) / 12.0;

   // Return Momentum of Inertia
   return Inertia(I, mass, _center());
}
