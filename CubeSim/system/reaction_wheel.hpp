

// CUBESIM - SYSTEM - REACTION WHEEL


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


// Class ReactionWheel
class CubeSim::System::ReactionWheel : public System
{
public:

   // Clone
   virtual System* clone(void) const;

   // Spin Rate [rad/s]
   double spin_rate(void) const;
   void spin_rate(double spin_rate);

   // Time Step [s]
   double time_step(void) const;
   void time_step(double time_step);

protected:

   // Constructor
   ReactionWheel(double range = _RANGE, double accuracy = _ACCURACY, double acceleration = _ACCELERATION,
      double time_step = _TIME_STEP);

   // Copy Constructor (reset Part)
   ReactionWheel(const ReactionWheel& reaction_wheel);

   // Spin Rate Acceleration [rad/s^2]
   double _acceleration(void) const;
   void _acceleration(double acceleration);

   // Accuracy [rad/s]
   double _accuracy(void) const;
   void _accuracy(double accuracy);

   // Part
   Part* _part(void) const;
   void _part(Part& part);

   // Range [rad/s]
   double _range(void) const;
   void _range(double range);

private:

   // Default Spin Rate Acceleration [rad/s^2]
   static const double _ACCELERATION;

   // Default Accuracy [rad/s]
   static const double _ACCURACY;

   // Default Range [rad/s]
   static const double _RANGE;

   // Default Time Step [s]
   static const double _TIME_STEP;

   // Behavior
   virtual void _behavior(void);

   // Initialize
   virtual void _init(void);

   // Variables
   double _acceleration_;
   double _accuracy_;
   double _range_;
   double _spin_rate;
   double _time_step;
   Part* _part_;
   mutable std::normal_distribution<double> _distribution;
   mutable std::default_random_engine _generator;
};


// Clone
inline CubeSim::System* CubeSim::System::ReactionWheel::clone(void) const
{
   // Return Copy
   return new ReactionWheel(*this);
}


// Get Spin Rate [rad/s]
inline double CubeSim::System::ReactionWheel::spin_rate(void) const
{
   // Return Spin Rate
   return _spin_rate;
}


// Set Spin Rate [rad/s]
inline void CubeSim::System::ReactionWheel::spin_rate(double spin_rate)
{
   // Set Spin Rate
   _spin_rate = std::min(_range_, std::max(-_range_, spin_rate));
}


// Get Time Step [s]
inline double CubeSim::System::ReactionWheel::time_step(void) const
{
   // Return Time Step
   return _time_step;
}


// Set Time Step [s]
inline void CubeSim::System::ReactionWheel::time_step(double time_step)
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
inline CubeSim::System::ReactionWheel::ReactionWheel(double range, double accuracy, double acceleration,
   double time_step) : _spin_rate(), _part_(), _distribution(0.0, 1.0)
{
   // Initialize
   this->time_step(time_step);
   _acceleration(acceleration);
   _accuracy(accuracy);
   _range(range);
}


// Copy Constructor (reset Part)
inline CubeSim::System::ReactionWheel::ReactionWheel(const ReactionWheel& reaction_wheel) : System(reaction_wheel),
   _acceleration_(reaction_wheel._acceleration_), _accuracy_(reaction_wheel._accuracy_), _range_(reaction_wheel._range_),
   _spin_rate(), _time_step(reaction_wheel._time_step), _part_(), _distribution(reaction_wheel._distribution)
{
}


// Get Spin Rate Acceleration [rad/s^2]
inline double CubeSim::System::ReactionWheel::_acceleration(void) const
{
   // Return Spin Rate Acceleration
   return _acceleration_;
}


// Set Spin Rate Acceleration [rad/s^2]
inline void CubeSim::System::ReactionWheel::_acceleration(double acceleration)
{
   // Check Spin Rate Acceleration
   if (acceleration <= 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Spin Rate Acceleration
   _acceleration_ = acceleration;
}


// Get Accuracy [rad/s]
inline double CubeSim::System::ReactionWheel::_accuracy(void) const
{
   // Return Accuracy
   return _accuracy_;
}


// Set Accuracy [rad/s]
inline void CubeSim::System::ReactionWheel::_accuracy(double accuracy)
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
inline CubeSim::Part* CubeSim::System::ReactionWheel::_part(void) const
{
   // Return Part
   return _part_;
}


// Set Part
inline void CubeSim::System::ReactionWheel::_part(Part& part)
{
   // Set Part
   _part_ = &part;
}


// Get Range [rad/s]
inline double CubeSim::System::ReactionWheel::_range(void) const
{
   // Return Range
   return _range_;
}


// Set Range [rad/s]
inline void CubeSim::System::ReactionWheel::_range(double range)
{
   // Check Range
   if (range <= 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Range
   _range_ = range;

   // Limit Spin Rate
   spin_rate(_spin_rate);
}
