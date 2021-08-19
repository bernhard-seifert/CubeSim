

// CUBESIM - CELESTIAL BODY


// Includes
#include "simulation.hpp"


// Assign (Simulation Reference is maintained)
inline CubeSim::CelestialBody& CubeSim::CelestialBody::operator =(const CelestialBody& celestial_body)
{
   // Check Celestial Body
   if (this != &celestial_body)
   {
      // Check Type to avoid Object Slicing
      if (typeid(*this) != typeid(celestial_body))
      {
         // Exception
         throw Exception::Parameter();
      }

      // Assign
      static_cast<RigidBody&>(*this) = celestial_body;
      static_cast<List<CelestialBody>::Item&>(*this) = celestial_body;
      _density = celestial_body._density;
      _flattening = celestial_body._flattening;
      _radius = celestial_body._radius;
      _temperature = celestial_body._temperature;
   }

   // Return Reference
   return *this;
}


// Compute gravitational Field (Body Frame) [m/s^2]
const CubeSim::Vector3D CubeSim::CelestialBody::gravitational_field(const Vector3D& point) const
{
   // Compute Distance
   double r = point.norm();

   // Return ideal gravitational Field
   return ((radius() <= r) ? (-Constant::G * mass() / pow(r, 3.0) * point) : Vector3D());
}


// Compute Moment of Inertia Tensor (Body Frame) [kg*m^2]
const CubeSim::Inertia CubeSim::CelestialBody::_inertia(void) const
{
   // Compute Mass
   double mass = this->mass();

   // Compute Coefficient for X and Y Axes
   double a = 1.0 + pow(1.0 - _flattening, 2.0);

   // Compute and return Tensor
   return Inertia(mass * radius() * radius() / 5.0 *
      Matrix3D(Vector3D(a, 0.0, 0.0), Vector3D(0.0, a, 0.0), Vector3D(0.0, 0.0, 2.0)), mass);
}
