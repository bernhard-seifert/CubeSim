

// CUBESIM - MODULE - MAGNETICS


// Includes
#include "magnetics.hpp"
#include "../simulation.hpp"


// Compute magnetic Field [T]
const CubeSim::Vector3D CubeSim::Module::Magnetics::field(const Vector3D& point) const
{
   // Check for specific Celestial Body
   if (_celestial_body)
   {
      // Compute and return magnetic Field
      return _field(*_celestial_body, point);
   }

   // Check Simulation
   if (!simulation())
   {
      // Exception
      throw Exception::Failed();
   }

   // Magnetic Field
   Vector3D field;

   // Parse Celestial Body List
   for (auto celestial_body = simulation()->celestial_body().begin();
      celestial_body != simulation()->celestial_body().end(); ++celestial_body)
   {
      // Update magnetic Field
      field += _field(*celestial_body->second, point);
   }

   // Return magnetic Field
   return field;
}


// Compute magnetic Field [T]
const CubeSim::Vector3D CubeSim::Module::Magnetics::_field(const CelestialBody& celestial_body,
   const Vector3D& point) const
{
   // Transform Point relative to Celestial Body
   Vector3D point_ = point - celestial_body.position() - celestial_body.rotation();

   // Compute, transform and return magnetic Field
   return (celestial_body.magnetic_field(point_) + celestial_body.rotation());
}
