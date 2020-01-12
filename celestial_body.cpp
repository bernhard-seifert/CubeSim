

// CUBESIM - CELESTIAL BODY


// Includes
#include "simulation.hpp"


// Assign (Simulation Reference is maintained)
inline CubeSim::CelestialBody& CubeSim::CelestialBody::operator =(const CelestialBody& celestial_body)
{
   // Check Type
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
