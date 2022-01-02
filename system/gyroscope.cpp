

// CUBESIM - SYSTEM - GYROSCOPE


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
#include <algorithm>
#include "gyroscope.hpp"
#include "../spacecraft.hpp"


// Measure Spin Rate [rad/s]
const CubeSim::Vector3D CubeSim::System::Gyroscope::spin_rate(void) const
{
   // Check if enabled
   if (!is_enabled())
   {
      // Return invalid angular Rate
      return Vector3D(NAN, NAN, NAN);
   }

   // Check Initialization Flag
   if (!_init)
   {
      // Check Spacecraft and Part
      if (!spacecraft() || !_part_)
      {
         // Exception
         throw Exception::Failed();
      }

      // Get Part Position and Rotation in global Frame
      auto location = _part_->locate();

      // Compute Part Rotation relative to Spacecraft
      _rotation = location.second - spacecraft()->rotation();

      // Set Initialization Flag
      _init = true;
   }

   // Compute angular Rate (Body Frame)
   Vector3D angular_rate = spacecraft()->angular_rate() - spacecraft()->rotation() - _rotation;

   // Compute and return angular Rate (consider Accuracy and Range)
   return Vector3D(std::min(_range_, std::max(-_range_, angular_rate.x() + _distribution(_generator) * _accuracy_)),
      std::min(_range_, std::max(-_range_, angular_rate.y() + _distribution(_generator) * _accuracy_)),
      std::min(_range_, std::max(-_range_, angular_rate.z() + _distribution(_generator) * _accuracy_)));
}


// Default Accuracy [rad/s]
const double CubeSim::System::Gyroscope::_ACCURACY = 0.0;

// Default Range [rad/s]
const double CubeSim::System::Gyroscope::_RANGE = std::numeric_limits<double>::infinity();
