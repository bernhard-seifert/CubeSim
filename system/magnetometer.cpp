

// CUBESIM - SYSTEM - MAGNETOMETER


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
#include "magnetometer.hpp"
#include "../simulation.hpp"


// Measure magnetic Field [T]
const CubeSim::Vector3D CubeSim::System::Magnetometer::magnetic_field(void) const
{
   // Check if enabled
   if (!is_enabled())
   {
      // Return invalid magnetic Field
      return Vector3D(NAN, NAN, NAN);
   }

   // Check Initialization Flag
   if (!_init)
   {
      // Check Simulation and Part
      if (!simulation() || !_part_)
      {
         // Exception
         throw Exception::Failed();
      }

      // Parse Module List
      for (auto module = simulation()->module().begin(); module != simulation()->module().end(); ++module)
      {
         // Check Module
         if (dynamic_cast<Module::Magnetics*>(module->second))
         {
            // Insert Magnetics Module into List
            _magnetics.push_back(dynamic_cast<Module::Magnetics*>(module->second));
         }
      }

      // Get Part Position and Rotation in global Frame
      auto location = _part_->locate();

      // Compute Part Rotation relative to Spacecraft
      _rotation = location.second - spacecraft()->rotation();

      // Set Initialization Flag
      _init = true;
   }

   // Magnetic Field
   Vector3D magnetic_field;

   // Parse Magnetics Modules
   for (auto magnetics = _magnetics.begin(); magnetics != _magnetics.end(); ++magnetics)
   {
      // Update magnetic Field
      magnetic_field += (*magnetics)->field(spacecraft()->position()) - spacecraft()->rotation() - _rotation;
   }

   // Compute and return magnetic Field (consider Accuracy and Range)
   return Vector3D(std::min(_range_, std::max(-_range_, magnetic_field.x() + _distribution(_generator) * _accuracy_)),
      std::min(_range_, std::max(-_range_, magnetic_field.y() + _distribution(_generator) * _accuracy_)),
      std::min(_range_, std::max(-_range_, magnetic_field.z() + _distribution(_generator) * _accuracy_)));
}


// Default Accuracy [T]
const double CubeSim::System::Magnetometer::_ACCURACY = 0.0;

// Default Range [T]
const double CubeSim::System::Magnetometer::_RANGE = std::numeric_limits<double>::infinity();
