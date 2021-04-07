

// CUBESIM - SYSTEM - ACCELEROMETER


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
   Vector3D acceleration = (_position[0] * 2.0 - _position[1] * 5.0 + _position[2] * 4.0 - _position[3]) / _time_step_ /
      _time_step_ - rotation;

   // Check gravitational Force
   if (!gravitation)
   {
      // Get gravitational Force
      gravitation = spacecraft()->force("Gravitation");
   }
   else
   {
      // Add gravitational Acceleration
      acceleration -= (*gravitation - _rotation) / spacecraft()->mass();
   }

   // Compute and return Acceleration (consider Accuracy and Range)
   return Vector3D(std::min(_range_, std::max(-_range_, acceleration.x() + _distribution(_generator) * _accuracy_)),
      std::min(_range_, std::max(-_range_, acceleration.y() + _distribution(_generator) * _accuracy_)),
      std::min(_range_, std::max(-_range_, acceleration.z() + _distribution(_generator) * _accuracy_)));
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
   // Check Simulation and Part
   if (!simulation() || !_part_)
   {
      // Exception
      throw Exception::Failed();
   }

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
      simulation()->delay(_time_step_);
   }
}
