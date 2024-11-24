

// CUBESIM - SYSTEM - REACTION WHEEL


// Copyright (c) 2022 Bernhard Seifert
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sub-license, and / or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
// Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
// OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


// Includes
#include "reaction_wheel.hpp"
#include "../simulation.hpp"


// Default Spin Rate Acceleration [rad/s^2]
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


// Initialize
void CubeSim::System::ReactionWheel::_init(void)
{
   // Check Simulation and Part
   if (!simulation() || !_part_)
   {
      // Exception
      throw Exception::Failed();
   }
}