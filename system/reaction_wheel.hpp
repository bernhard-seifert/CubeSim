

// CUBESIM - SYSTEM - REACTION WHEEL


// Includes
#include <algorithm>
#include <random>
#include "../system.hpp"


// *** TODO ***


// Preprocessor Directives
#pragma once


// Class ReactionWheel
class CubeSim::System::ReactionWheel : public System
{
public:

   // *** angular velocity: public
   // *** angular acceleration: limit private, value public?

   // Clone
   virtual System* clone(void) const;

   // Set Current [A] *** this will become rate
   void current(double current);

protected:

   // Constructor
   ReactionWheel(double area, double range = _RANGE, double accuracy = _ACCURACY, double time_step = _TIME_STEP);

   // Copy Constructor
   ReactionWheel(const ReactionWheel& magnetorquer);

   // Accuracy [A]
   double _accuracy(void) const;
   void _accuracy(double accuracy);

   // Effective Coil Area [m^2]
   double _area(void) const;
   void _area(double area);

   // Part
   Part* _part(void) const;
   void _part(Part& part);

   // Range [A]
   double _range(void) const;
   void _range(double range);

   // Time Step [s]
   double _time_step(void) const;
   void _time_step(double time_step);

private:

   // Default Accuracy [A]
   static const double _ACCURACY;

   // Default Range [A]
   static const double _RANGE;

   // Default Time Step [s]
   static const double _TIME_STEP;

   // Behavior
   virtual void _behavior(void);

   // Variables
   double _accuracy_;
   double _area_;
   double _current;
   double _range_;
   double _time_step_;
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


// Set Current [A]
inline void CubeSim::System::ReactionWheel::current(double current)
{
   // Set Current
   _current = std::min(_range_, std::max(-_range_, current));
}


// Constructor
inline CubeSim::System::ReactionWheel::ReactionWheel(double area, double range, double accuracy, double time_step) :
   _current(), _part_(), _distribution(0.0, 1.0)
{
   // Initialize
   _accuracy(accuracy);
   _area(area);
   _range(range);
   _time_step(time_step);
}


// Copy Constructor
inline CubeSim::System::ReactionWheel::ReactionWheel(const ReactionWheel& magnetorquer) : System(magnetorquer),
_accuracy_(magnetorquer._accuracy_), _area_(magnetorquer._area_), _current(magnetorquer._current),
_range_(magnetorquer._range_), _time_step_(magnetorquer._time_step_), _part_(),
_distribution(magnetorquer._distribution)
{
}


// Get Accuracy [A]
inline double CubeSim::System::ReactionWheel::_accuracy(void) const
{
   // Return Accuracy
   return _accuracy_;
}


// Set Accuracy [A]
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


// Get effective Coil Area [m^2]
inline double CubeSim::System::ReactionWheel::_area(void) const
{
   // Return effective Sensor Area
   return _area_;
}


// Set effective Coil Area [m^2]
inline void CubeSim::System::ReactionWheel::_area(double area)
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


// Get Range [A]
inline double CubeSim::System::ReactionWheel::_range(void) const
{
   // Return Range
   return _range_;
}


// Set Range [A]
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

   // Limit Current
   current(_current);
}


// Get Time Step [s]
inline double CubeSim::System::ReactionWheel::_time_step(void) const
{
   // Return Time Step
   return _time_step_;
}


// Set Time Step [s]
inline void CubeSim::System::ReactionWheel::_time_step(double time_step)
{
   // Check Time Step
   if (time_step <= 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Time Step
   _time_step_ = time_step;
}
