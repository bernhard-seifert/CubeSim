

// CUBESIM - SYSTEM - MAGNETORQUER


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
#include <random>
#include "../system.hpp"


// Preprocessor Directives
#pragma once


// Class Magnetorquer
class CubeSim::System::Magnetorquer : public System
{
public:

   // Clone
   virtual System* clone(void) const;

   // Current [A]
   double current(void) const;
   void current(double current);

   // Time Step [s]
   double time_step(void) const;
   void time_step(double time_step);

protected:

   // Constructor
   Magnetorquer(double area, double range = _RANGE, double accuracy = _ACCURACY, double time_step = _TIME_STEP);

   // Copy Constructor (reset Part)
   Magnetorquer(const Magnetorquer& magnetorquer);

   // Accuracy [A]
   double _accuracy(void) const;
   void _accuracy(double accuracy);

   // Effective Coil Area [m^2]
   double _area(void) const;
   void _area(double area);

   // Part
   Part* _part(void) const;
   void _part(Part& part);

   // Relative magnetic Permeability
   double _permeability(void) const;
   void _permeability(double permeability);

   // Range [A]
   double _range(void) const;
   void _range(double range);

private:

   // Default Accuracy [A]
   static const double _ACCURACY;

   // Default Range [A]
   static const double _RANGE;

   // Default Time Step [s]
   static const double _TIME_STEP;

   // Behavior
   virtual void _behavior(void);

   // Initialize
   virtual void _init(void);

   // Variables
   double _accuracy_;
   double _area_;
   double _current;
   double _permeability_;
   double _range_;
   double _time_step;
   Part* _part_;
   mutable std::normal_distribution<double> _distribution;
   mutable std::default_random_engine _generator;
};


// Clone
inline CubeSim::System* CubeSim::System::Magnetorquer::clone(void) const
{
   // Return Copy
   return new Magnetorquer(*this);
}


// Get Current [A]
inline double CubeSim::System::Magnetorquer::current(void) const
{
   // Return Current
   return _current;
}


// Set Current [A]
inline void CubeSim::System::Magnetorquer::current(double current)
{
   // Set Current
   _current = std::clamp(current, -_range_, _range_);
}


// Get Time Step [s]
inline double CubeSim::System::Magnetorquer::time_step(void) const
{
   // Return Time Step
   return _time_step;
}


// Set Time Step [s]
inline void CubeSim::System::Magnetorquer::time_step(double time_step)
{
   // Check Time Step
   if (time_step <= 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Time Step
   _time_step = time_step;
}


// Constructor
inline CubeSim::System::Magnetorquer::Magnetorquer(double area, double range, double accuracy, double time_step) :
   _current(), _part_(), _distribution(0.0, 1.0)
{
   // Initialize
   this->time_step(time_step);
   _accuracy(accuracy);
   _area(area);
   _range(range);
}


// Copy Constructor (reset Part)
inline CubeSim::System::Magnetorquer::Magnetorquer(const Magnetorquer& magnetorquer) : System(magnetorquer),
   _accuracy_(magnetorquer._accuracy_), _area_(magnetorquer._area_), _current(magnetorquer._current),
   _permeability_(1.0), _range_(magnetorquer._range_), _time_step(magnetorquer._time_step), _part_(),
   _distribution(magnetorquer._distribution)
{
}


// Get Accuracy [A]
inline double CubeSim::System::Magnetorquer::_accuracy(void) const
{
   // Return Accuracy
   return _accuracy_;
}


// Set Accuracy [A]
inline void CubeSim::System::Magnetorquer::_accuracy(double accuracy)
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


// Get effective Coil Area [m^2]
inline double CubeSim::System::Magnetorquer::_area(void) const
{
   // Return effective Sensor Area
   return _area_;
}


// Set effective Coil Area [m^2]
inline void CubeSim::System::Magnetorquer::_area(double area)
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
inline CubeSim::Part* CubeSim::System::Magnetorquer::_part(void) const
{
   // Return Part
   return _part_;
}


// Set Part
inline void CubeSim::System::Magnetorquer::_part(Part& part)
{
   // Set Part
   _part_ = &part;
}


// Get relative magnetic Permeability
inline double CubeSim::System::Magnetorquer::_permeability(void) const
{
   // Return relative magnetic Permeability
   return _permeability_;
}


// Set relative magnetic Permeability
inline void CubeSim::System::Magnetorquer::_permeability(double permeability)
{
   // Check relative magnetic Permeability
   if (permeability < 1.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set relative magnetic Permeability
   _permeability_ = permeability;
}


// Get Range [A]
inline double CubeSim::System::Magnetorquer::_range(void) const
{
   // Return Range
   return _range_;
}


// Set Range [A]
inline void CubeSim::System::Magnetorquer::_range(double range)
{
   // Check Range
   if (range <= 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Range
   _range_ = range;

   // Limit Current
   current(_current);
}
