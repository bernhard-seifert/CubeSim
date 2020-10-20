

// CUBESIM - SYSTEM - MAGNETORQUER


// Includes
#include "magnetorquer.hpp"
#include "../simulation.hpp"
#include "../module/magnetics.hpp"


// Default Accuracy [A]
const double CubeSim::System::Magnetorquer::_ACCURACY = 0.0;

// Default Range [A]
const double CubeSim::System::Magnetorquer::_RANGE = std::numeric_limits<double>::infinity();

// Default Time Step [s]
const double CubeSim::System::Magnetorquer::_TIME_STEP = 1.0;


// Behavior
void CubeSim::System::Magnetorquer::_behavior(void)
{
   // Check Simulation and Part
   if (!simulation() || !_part_)
   {
      // Exception
      throw Exception::Failed();
   }

   // Magnetics Modules
   std::vector<Module::Magnetics*> magnetics;

   // Parse Module List
   for (auto module = simulation()->module().begin(); module != simulation()->module().end(); ++module)
   {
      // Check Module
      if (dynamic_cast<Module::Magnetics*>(module->second))
      {
         // Insert Magnetics Module into List
         magnetics.push_back(dynamic_cast<Module::Magnetics*>(module->second));
      }
   }

   // Get Part Position and Rotation in global Frame
   auto location = _part_->locate();

   // Compute Part Rotation relative to Spacecraft
   Rotation rotation = location.second - spacecraft()->rotation();

   // Insert Torque
   _part_->insert("Magnetorquer", Torque());

   // Loop
   for (;;)
   {
      // Check if enabled
      if (is_enabled())
      {
         // Magnetic Field
         Vector3D field;

         // Parse Magnetics Modules
         for (auto magnetics_ = magnetics.begin(); magnetics_ != magnetics.end(); ++magnetics_)
         {
            // Compute and update magnetic Field
            field += (*magnetics_)->field(spacecraft()->position()) - spacecraft()->rotation() - rotation;
         }

         // Compute and update Torque (Body Frame)
         *_part_->torque("Magnetorquer") = _area_ * (_current + _distribution(_generator) * _accuracy_) *
            (Vector3D::Z ^ field);
      }
      else
      {
         // Reset Torque
         *_part_->torque("Magnetorquer") = Vector3D();
      }

      // Delay
      simulation()->delay(_time_step_);
   }
}
