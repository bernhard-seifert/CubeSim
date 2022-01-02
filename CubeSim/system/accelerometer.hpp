

// CUBESIM - SYSTEM - ACCELEROMETER


// Includes
#include <random>
#include "../system.hpp"


// Preprocessor Directives
#pragma once


// Class Accelerometer
class CubeSim::System::Accelerometer : public System
{
public:

   // Measure Acceleration [m/s^2]
   const Vector3D acceleration(void) const;

   // Clone
   virtual System* clone(void) const;

   // Time Step [s]
   double time_step(void) const;
   void time_step(double time_step);

protected:

   // Constructor
   Accelerometer(double accuracy = _ACCURACY, double range = _RANGE, double time_step = _TIME_STEP);

   // Copy Constructor (reset Part)
   Accelerometer(const Accelerometer& accelerometer);

   // Accuracy [m/s^2]
   double _accuracy(void) const;
   void _accuracy(double accuracy);

   // Part
   Part* _part(void) const;
   void _part(Part& part);

   // Range [m/s^2]
   double _range(void) const;
   void _range(double range);

private:

   // Default Accuracy [m/s^2]
   static const double _ACCURACY;

   // Default Range [m/s^2]
   static const double _RANGE;

   // Default Time Step [s]
   static const double _TIME_STEP;

   // Behavior
   virtual void _behavior(void);

   // Variables
   double _accuracy_;
   double _range_;
   double _time_step;
   Part* _part_;
   Rotation _rotation;
   std::vector<Vector3D> _position;
   mutable std::default_random_engine _generator;
   mutable std::normal_distribution<double> _distribution;
};


// Clone
inline CubeSim::System* CubeSim::System::Accelerometer::clone(void) const
{
   // Return Copy
   return new Accelerometer(*this);
}


// Get Time Step [s]
inline double CubeSim::System::Accelerometer::time_step(void) const
{
   // Return Time Step
   return _time_step;
}


// Set Time Step [s]
inline void CubeSim::System::Accelerometer::time_step(double time_step)
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
inline CubeSim::System::Accelerometer::Accelerometer(double accuracy, double range, double time_step) : _part_(),
   _distribution(0.0, 1.0)
{
   // Initialize
   this->time_step(time_step);
   _accuracy(accuracy);
   _range(range);
}


// Copy Constructor (reset Part)
inline CubeSim::System::Accelerometer::Accelerometer(const Accelerometer& accelerometer) : System(accelerometer),
   _accuracy_(accelerometer._accuracy_), _range_(accelerometer._range_), _time_step(accelerometer._time_step),
   _part_(), _distribution(accelerometer._distribution)
{
}


// Get Accuracy [m/s^2]
inline double CubeSim::System::Accelerometer::_accuracy(void) const
{
   // Return Accuracy
   return _accuracy_;
}


// Set Accuracy [m/s^2]
inline void CubeSim::System::Accelerometer::_accuracy(double accuracy)
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
inline CubeSim::Part* CubeSim::System::Accelerometer::_part(void) const
{
   // Return Part
   return _part_;
}


// Set Part
inline void CubeSim::System::Accelerometer::_part(Part& part)
{
   // Set Part
   _part_ = &part;
}


// Get Range [m/s^2]
inline double CubeSim::System::Accelerometer::_range(void) const
{
   // Return Range
   return _range_;
}


// Set Range [m/s^2]
inline void CubeSim::System::Accelerometer::_range(double range)
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
