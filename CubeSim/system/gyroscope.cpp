

// CUBESIM - SYSTEM - GYROSCOPE


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
