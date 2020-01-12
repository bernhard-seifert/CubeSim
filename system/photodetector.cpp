

// CUBESIM - SYSTEM - PHOTODETECTOR


// Includes
#include <algorithm>
#include "photodetector.hpp"
#include "../simulation.hpp"


// Measure Irradiance [W]
double CubeSim::System::Photodetector::irradiance(void) const
{
   // Check if enabled
   if (!enabled())
   {
      // Return invalid Irradiance
      return NAN;
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
         if (dynamic_cast<Module::Light*>(module->second))
         {
            // Insert Light Module into List
            _light.push_back(dynamic_cast<Module::Light*>(module->second));
         }
         else if (dynamic_cast<Module::Albedo*>(module->second))
         {
            // Insert Albedo Module into List
            _albedo.push_back(dynamic_cast<Module::Albedo*>(module->second));
         }
      }

      // Get Part Position and Rotation in global Frame
      auto location = _part_->locate();

      // Compute Part Rotation relative to Spacecraft
      _rotation = location.second - spacecraft()->rotation();

      // Set Initialization Flag
      _init = true;
   }

   // Irradiance
   double irradiance = 0.0;

   // Parse Light Modules
   for (auto light = _light.begin(); light != _light.end(); ++light)
   {
      // Update Irradiance
      irradiance += (*light)->irradiance(spacecraft()->position(), Vector3D::Z + _rotation +
         spacecraft()->rotation(), _angle_);
   }

   // Parse Albedo Modules
   for (auto albedo = _albedo.begin(); albedo != _albedo.end(); ++albedo)
   {
      // Update Irradiance
      irradiance += (*albedo)->irradiance(spacecraft()->position(), Vector3D::Z + _rotation +
         spacecraft()->rotation(), _angle_);
   }

   // Compute and return Irradiance (consider Accuracy, Range and Area)
   return (std::min(_range_, std::max(0.0, (irradiance + _distribution(_generator) * _accuracy_))) * _area_);
}


// Default Accuracy [W/m^2]
const double CubeSim::System::Photodetector::_ACCURACY = 0.0;

// Default opening Angle [rad]
const double CubeSim::System::Photodetector::_ANGLE = Constant::PI;

// Default Range [W/m^2]
const double CubeSim::System::Photodetector::_RANGE = std::numeric_limits<double>::infinity();
