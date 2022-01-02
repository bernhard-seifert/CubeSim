

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
#include <algorithm>
#include <random>
#include "../system.hpp"


// Preprocessor Directives
#pragma once


// Class Thruster
class CubeSim::System::Thruster : public System
{
public:

   // Clone
   virtual System* clone(void) const;

   // Thrust [N]
   double thrust(void) const;
   void thrust(double thrust);

   // Time Step [s]
   double time_step(void) const;
   void time_step(double time_step);

protected:

   // Constructor
   Thruster(double range = _RANGE, double accuracy = _ACCURACY, double time_step = _TIME_STEP);

   // Copy Constructor (reset Part)
   Thruster(const Thruster& thruster);

   // Accuracy [N]
   double _accuracy(void) const;
   void _accuracy(double accuracy);

   // Part
   Part* _part(void) const;
   void _part(Part& part);

   // Range [N]
   double _range(void) const;
   void _range(double range);

private:

   // Default Accuracy [N]
   static const double _ACCURACY;

   // Default Range [N]
   static const double _RANGE;

   // Default Time Step [s]
   static const double _TIME_STEP;

   // Behavior
   virtual void _behavior(void);

   // Variables
   double _accuracy_;
   double _range_;
   double _thrust;
   double _time_step;
   Part* _part_;
   mutable std::normal_distribution<double> _distribution;
   mutable std::default_random_engine _generator;
};


// Clone
inline CubeSim::System* CubeSim::System::Thruster::clone(void) const
{
   // Return Copy
   return new Thruster(*this);
}


// Get Thrust [N]
inline double CubeSim::System::Thruster::thrust(void) const
{
   // Return Thrust
   return _thrust;
}


// Set Thrust [N]
inline void CubeSim::System::Thruster::thrust(double thrust)
{
   // Set Thrust
   _thrust = std::min(_range_, std::max(0.0, thrust));
}


// Get Time Step [s]
inline double CubeSim::System::Thruster::time_step(void) const
{
   // Return Time Step
   return _time_step;
}


// Set Time Step [s]
inline void CubeSim::System::Thruster::time_step(double time_step)
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
inline CubeSim::System::Thruster::Thruster(double range, double accuracy, double time_step) : _part_(), _thrust(),
   _distribution(0.0, 1.0)
{
   // Initialize
   this->time_step(time_step);
   _accuracy(accuracy);
   _range(range);
}


// Copy Constructor (reset Part)
inline CubeSim::System::Thruster::Thruster(const Thruster& thruster) : System(thruster),
   _accuracy_(thruster._accuracy_), _range_(thruster._range_), _thrust(), _time_step(thruster._time_step), _part_(),
   _distribution(thruster._distribution)
{
}


// Get Accuracy [N]
inline double CubeSim::System::Thruster::_accuracy(void) const
{
   // Return Accuracy
   return _accuracy_;
}


// Set Accuracy [N]
inline void CubeSim::System::Thruster::_accuracy(double accuracy)
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


// Get Part
inline CubeSim::Part* CubeSim::System::Thruster::_part(void) const
{
   // Return Part
   return _part_;
}


// Set Part
inline void CubeSim::System::Thruster::_part(Part& part)
{
   // Set Part
   _part_ = &part;
}


// Get Range [N]
inline double CubeSim::System::Thruster::_range(void) const
{
   // Return Range
   return _range_;
}


// Set Range [N]
inline void CubeSim::System::Thruster::_range(double range)
{
   // Check Range
   if (range <= 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Range
   _range_ = range;

   // Limit Thrust
   thrust(_thrust);
}
