

// CUBESIM - SYSTEM - ACCELEROMETER


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
#include "accelerometer.hpp"
#include "../simulation.hpp"


// Measure Acceleration [m/s^2]
const CubeSim::Vector3D CubeSim::System::Accelerometer::acceleration(void) const
{
   // Gravitational Force on Spacecraft
   static Force* gravitation;

   // Check if enabled and Position List Size
   if (!is_enabled() || (_position.size() < 4))
   {
      // Return invalid Acceleration
      return Vector3D(NAN, NAN, NAN);
   }

   // Compute Part Rotation
   Rotation rotation = _rotation + spacecraft()->rotation();

   // Obtain Acceleration from Position Spline (Body Frame)
   Vector3D acceleration = (_position[0] * 2.0 - _position[1] * 5.0 + _position[2] * 4.0 - _position[3]) / _time_step /
      _time_step - rotation;

   // Check gravitational Force
   if (!gravitation)
   {
      // Get gravitational Force
      gravitation = spacecraft()->force("Gravitation");
   }

   // Check gravitational Force
   if (gravitation)
   {
      // Add gravitational Acceleration
      acceleration -= (*gravitation - _rotation) / spacecraft()->mass();
   }

   // Compute and return Acceleration (consider Accuracy and Range)
   return Vector3D(std::clamp(acceleration.x() + _distribution(_generator) * _accuracy_, -_range_, _range_),
      std::clamp(acceleration.y() + _distribution(_generator) * _accuracy_, -_range_, _range_),
      std::clamp(acceleration.z() + _distribution(_generator) * _accuracy_, -_range_, _range_));
}


// Default Accuracy [m/s^2]
const double CubeSim::System::Accelerometer::_ACCURACY = 0.0;

// Default Range [m/s^2]
const double CubeSim::System::Accelerometer::_RANGE = std::numeric_limits<double>::infinity();

// Default Time Step [s]
const double CubeSim::System::Accelerometer::_TIME_STEP = 1.0;


// Behavior
void CubeSim::System::Accelerometer::_behavior(void)
{
   // Get Part Position and Rotation in global Frame
   auto location = _part_->locate();

   // Compute Part Position and Rotation relative to Spacecraft
   Vector3D position = location.first - spacecraft()->position() - spacecraft()->rotation();
   _rotation = location.second - spacecraft()->rotation();

   // Loop
   for (;;)
   {
      // Check Position List Size
      if (_position.size() == 4)
      {
         // Remove last Position
         _position.pop_back();
      }

      // Compute Part Position and insert into List
      _position.insert(_position.begin(), position + spacecraft()->rotation() + spacecraft()->position());

      // Delay
      simulation()->delay(_time_step);
   }
}


// Initialize
void CubeSim::System::Accelerometer::_init(void)
{
   // Check Simulation and Part
   if (!simulation() || !_part_)
   {
      // Exception
      throw Exception::Failed();
   }
}