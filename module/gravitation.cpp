

// CUBESIM - MODULE - GRAVITATION


// Includes
#include "gravitation.hpp"
#include "../simulation.hpp"


// Default Time Step [s]
const double CubeSim::Module::Gravitation::_TIME_STEP = 1.000;

// Force Name
const std::string CubeSim::Module::Gravitation::_FORCE = "Gravitation";


// Compute gravitational Field [m/s^2]
const CubeSim::Vector3D CubeSim::Module::Gravitation::field(const Vector3D& point) const
{
   // Check Simulation
   if (!simulation())
   {
      // Exception
      throw Exception::Failed();
   }

   // Gravitational Field
   Vector3D field;

   // Parse Celestial Body List
   for (auto celestial_body = simulation()->celestial_body().begin();
      celestial_body != simulation()->celestial_body().end(); ++celestial_body)
   {
      // Update gravitational Field
      field += _field(*celestial_body->second, point);
   }

   // Return gravitational Field
   return field;
}


// Behavior
void CubeSim::Module::Gravitation::_behavior(void)
{
   // Check Simulation
   if (!simulation())
   {
      // Exception
      throw Exception::Failed();
   }

   // Parse Celestial Body List
   for (auto celestial_body = simulation()->celestial_body().begin();
      celestial_body != simulation()->celestial_body().end(); ++celestial_body)
   {
      // Create Force for Celestial Body
      celestial_body->second->insert(_FORCE, Force());
   }

   // Parse Spacecraft List
   for (auto spacecraft = simulation()->spacecraft().begin(); spacecraft != simulation()->spacecraft().end();
      ++spacecraft)
   {
      // Create Force for Spacecraft
      spacecraft->second->insert(_FORCE, Force());
   }

   // Loop
   for (;;)
   {
      // Parse Celestial Body List
      for (auto celestial_body = simulation()->celestial_body().begin();
         celestial_body != simulation()->celestial_body().end(); ++celestial_body)
      {
         // Transform and assign Force
         *celestial_body->second->force(_FORCE) = Force(field(celestial_body->second->position()) *
            celestial_body->second->mass() - celestial_body->second->rotation());
      }

      // Parse Spacecraft List
      for (auto spacecraft = simulation()->spacecraft().begin(); spacecraft != simulation()->spacecraft().end();
         ++spacecraft)
      {
         // Check cached Value
         if (std::isnan(spacecraft->second->__center.x()))
         {
            // Compute Center of Mass
            spacecraft->second->center();
         }

         // Transform and assign Force acting on Center of Mass (bypass its Transformation)
         *spacecraft->second->force(_FORCE) = Force(field(spacecraft->second->position()) * spacecraft->second->mass() -
            spacecraft->second->rotation(), spacecraft->second->__center);
      }

      // Delay
      simulation()->delay(_time_step);
   }
}


// Compute gravitational Field [m/s^2]
const CubeSim::Vector3D CubeSim::Module::Gravitation::_field(const CelestialBody& celestial_body,
   const Vector3D& point) const
{
   // Transform Point relative to Celestial Body
   Vector3D point_ = point - celestial_body.position() - celestial_body.rotation();

   // Compute, transform and return gravitational Field
   return (celestial_body.gravitational_field(point_) + celestial_body.rotation());
}
