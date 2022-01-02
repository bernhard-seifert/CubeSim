

// CUBESIM - SYSTEM - THRUSTER


// Includes
#include "thruster.hpp"
#include "../simulation.hpp"


// Default Accuracy [N]
const double CubeSim::System::Thruster::_ACCURACY = 0.0;

// Default Range [N]
const double CubeSim::System::Thruster::_RANGE = std::numeric_limits<double>::infinity();

// Default Time Step [s]
const double CubeSim::System::Thruster::_TIME_STEP = 1.0;


// Behavior
void CubeSim::System::Thruster::_behavior(void)
{
   // Check Simulation and Part
   if (!simulation() || !_part_)
   {
      // Exception
      throw Exception::Failed();
   }

   // Insert Force
   _part_->insert("Thruster", Force());

   // Loop
   for (;;)
   {
      // Check if enabled
      if (is_enabled())
      {
         // Compute and update Force (Body Frame)
         *_part_->force("Thruster") = (_thrust + _distribution(_generator) * _accuracy_) * Vector3D::Z;
      }
      else
      {
         // Reset Force
         *_part_->force("Force") = Vector3D();
      }

      // Delay
      simulation()->delay(_time_step);
   }
}
