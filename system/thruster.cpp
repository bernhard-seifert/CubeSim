

// CUBESIM - SYSTEM - THRUSTER


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
