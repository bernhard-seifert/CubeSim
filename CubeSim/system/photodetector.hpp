

// CUBESIM - SYSTEM - PHOTODETECTOR


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
#include <random>
#include "../system.hpp"
#include "../module/albedo.hpp"
#include "../module/light.hpp"


// Preprocessor Directives
#pragma once


// Class Photodetector
class CubeSim::System::Photodetector : public System
{
public:

   // Clone
   virtual System* clone(void) const;

   // Measure Radiant Flux [W]
   double radiant_flux(void) const;

protected:

   // Constructor
   Photodetector(double area, double angle = _ANGLE, double accuracy = _ACCURACY, double range = _RANGE);

   // Copy Constructor (reset Part)
   Photodetector(const Photodetector& photodetector);

   // Accuracy [W/m^2]
   double _accuracy(void) const;
   void _accuracy(double accuracy);

   // Opening Angle [rad]
   double _angle(void) const;
   void _angle(double angle);

   // Effective Sensor Area [m^2]
   double _area(void) const;
   void _area(double area);

   // Part
   Part* _part(void) const;
   void _part(Part& part);

   // Range [W/m^2]
   double _range(void) const;
   void _range(double range);

private:

   // Default Accuracy [W/m^2]
   static const double _ACCURACY;

   // Default opening Angle [rad]
   static const double _ANGLE;

   // Default Range [W/m^2]
   static const double _RANGE;

   // Variables
   double _accuracy_;
   double _angle_;
   double _area_;
   double _range_;
   Part* _part_;
   mutable bool _init;
   mutable Rotation _rotation;
   mutable std::normal_distribution<double> _distribution;
   mutable std::default_random_engine _generator;
   mutable std::vector<Module::Albedo*> _albedo;
   mutable std::vector<Module::Light*> _light;
};


// Clone
inline CubeSim::System* CubeSim::System::Photodetector::clone(void) const
{
   // Return Copy
   return new Photodetector(*this);
}


// Constructor
inline CubeSim::System::Photodetector::Photodetector(double area, double angle, double accuracy, double range) :
   _init(), _part_(), _distribution(0.0, 1.0)
{
   // Initialize
   _area(area);
   _angle(angle);
   _accuracy(accuracy);
   _range(range);
}


// Copy Constructor (reset Part)
inline CubeSim::System::Photodetector::Photodetector(const Photodetector& photodetector) : System(photodetector),
   _accuracy_(photodetector._accuracy_), _angle_(photodetector._angle_), _area_(photodetector._area_),
   _range_(photodetector._range_), _part_(), _init(), _distribution(photodetector._distribution)
{
}


// Get Accuracy [W/m^2]
inline double CubeSim::System::Photodetector::_accuracy(void) const
{
   // Return Accuracy
   return _accuracy_;
}


// Set Accuracy [W/m^2]
inline void CubeSim::System::Photodetector::_accuracy(double accuracy)
{
   // Check Accuracy
   if (accuracy < 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Accuracy
   _accuracy_ = accuracy;
}


// Get Opening Angle [rad]
inline double CubeSim::System::Photodetector::_angle(void) const
{
   // Return Opening Angle
   return _angle_;
}


// Set Opening Angle [rad]
inline void CubeSim::System::Photodetector::_angle(double angle)
{
   // Check Opening Angle
   if ((angle < 0.0) || (Constant::PI < angle))
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Opening Angle
   _angle_ = angle;
}


// Get effective Sensor Area [m^2]
inline double CubeSim::System::Photodetector::_area(void) const
{
   // Return effective Sensor Area
   return _area_;
}


// Set effective Sensor Area [m^2]
inline void CubeSim::System::Photodetector::_area(double area)
{
   // Check effective Sensor Area
   if (area <= 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set effective Sensor Area
   _area_ = area;
}


// Get Part
inline CubeSim::Part* CubeSim::System::Photodetector::_part(void) const
{
   // Return Part
   return _part_;
}


// Set Part
inline void CubeSim::System::Photodetector::_part(Part& part)
{
   // Set Part
   _part_ = &part;
}


// Get Range [W/m^2]
inline double CubeSim::System::Photodetector::_range(void) const
{
   // Return Range
   return _range_;
}


// Set Range [W/m^2]
inline void CubeSim::System::Photodetector::_range(double range)
{
   // Check Range
   if (range <= 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Range
   _range_ = range;
}
