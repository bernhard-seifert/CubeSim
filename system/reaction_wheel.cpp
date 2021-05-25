

// CUBESIM - SYSTEM - REACTION WHEEL


// Includes
#include "reaction_wheel.hpp"
#include "../simulation.hpp"


// Default Spin Rate Acceleration [rad/s]
const double CubeSim::System::ReactionWheel::_ACCELERATION = std::numeric_limits<double>::infinity();

// Default Accuracy [rad/s]
const double CubeSim::System::ReactionWheel::_ACCURACY = 0.0;

// Default Range [rad/s]
const double CubeSim::System::ReactionWheel::_RANGE = std::numeric_limits<double>::infinity();

// Default Time Step [s]
const double CubeSim::System::ReactionWheel::_TIME_STEP = 1.0;


// Behavior
void CubeSim::System::ReactionWheel::_behavior(void)
{
   // Check Simulation and Part
   if (!simulation() || !_part_)
   {
      // Exception
      throw Exception::Failed();
   }

   // Get Simulation Time
   double time = simulation()->time() * 0.001;

   // Actual Spin Rate (limited by Acceleration)
   double spin_rate = 0.0;

   // Loop
   for (;;)
   {
      // Get Simulation Time
      double time_ = simulation()->time() * 0.001;

      // Check if enabled
      if (is_enabled())
      {
         // Check Spin Rate
         if (_spin_rate < spin_rate)
         {
            // Decelerate
            spin_rate = std::max(spin_rate - (time_ - time) * _acceleration_, _spin_rate);
         }
         else
         {
            // Accelerate
            spin_rate = std::min(spin_rate + (time_ - time) * _acceleration_, _spin_rate);
         }

         // Compute and update Spin Rate
         _part_->angular_rate((spin_rate + _distribution(_generator) * _accuracy_) * Vector3D::Z);
      }
      else
      {
         // Reset angular Rate
         _part_->angular_rate(Vector3D());
         spin_rate = 0.0;
      }

      // Set Simulation Time
      time = time_;

      // Delay
      simulation()->delay(_time_step);
   }
}
