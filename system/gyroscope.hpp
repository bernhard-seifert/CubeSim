

// CUBESIM - SYSTEM - GYROSCOPE


// Includes
#include <random>
#include "../system.hpp"


// Preprocessor Directives
#pragma once


// Class Gyroscope
class CubeSim::System::Gyroscope : public System
{
public:

   // Measure angular Rate [rad/s]
   const Vector3D angular_rate(void) const;

   // Clone
   virtual System* clone(void) const;

protected:

   // Constructor
   Gyroscope(double accuracy = _ACCURACY, double range = _RANGE);

   // Copy Constructor
   Gyroscope(const Gyroscope& gyroscope);

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

   // Default Accuracy [rad/s]
   static const double _ACCURACY;

   // Default Range [rad/s]
   static const double _RANGE;

   // Variables
   double _accuracy_;
   double _range_;
   Part* _part_;
   mutable bool _init;
   mutable Rotation _rotation;
   mutable std::default_random_engine _generator;
   mutable std::normal_distribution<double> _distribution;
};


// Clone
inline CubeSim::System* CubeSim::System::Gyroscope::clone(void) const
{
   // Return Copy
   return new Gyroscope(*this);
}


// Constructor
inline CubeSim::System::Gyroscope::Gyroscope(double accuracy, double range) : _part_(), _init(), _distribution(0.0, 1.0)
{
   // Initialize
   _accuracy(accuracy);
   _range(range);
}


// Copy Constructor
inline CubeSim::System::Gyroscope::Gyroscope(const Gyroscope& gyroscope) : System(gyroscope),
   _accuracy_(gyroscope._accuracy_), _range_(gyroscope._range_), _part_(), _init(),
   _distribution(gyroscope._distribution)
{
}


// Get Accuracy [rad/s]
inline double CubeSim::System::Gyroscope::_accuracy(void) const
{
   // Return Accuracy
   return _accuracy_;
}


// Set Accuracy [rad/s]
inline void CubeSim::System::Gyroscope::_accuracy(double accuracy)
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
inline CubeSim::Part* CubeSim::System::Gyroscope::_part(void) const
{
   // Return Part
   return _part_;
}


// Set Part
inline void CubeSim::System::Gyroscope::_part(Part& part)
{
   // Set Part
   _part_ = &part;
}


// Get Range [rad/s]
inline double CubeSim::System::Gyroscope::_range(void) const
{
   // Return Range
   return _range_;
}


// Set Range [rad/s]
inline void CubeSim::System::Gyroscope::_range(double range)
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
