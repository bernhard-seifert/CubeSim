

// CUBESIM - SYSTEM - MAGNETOMETER


// Includes
#include <random>
#include "../system.hpp"
#include "../module/magnetics.hpp"


// Preprocessor Directives
#pragma once


// Class Magnetometer
class CubeSim::System::Magnetometer : public System
{
public:

   // Clone
   virtual System* clone(void) const;

   // Measure magnetic Field [T]
   const Vector3D magnetic_field(void) const;

protected:

   // Constructor
   Magnetometer(double accuracy = _ACCURACY, double range = _RANGE);

   // Copy Constructor
   Magnetometer(const Magnetometer& magnetometer);

   // Accuracy [T]
   double _accuracy(void) const;
   void _accuracy(double accuracy);

   // Part
   Part* _part(void) const;
   void _part(Part& part);

   // Range [T]
   double _range(void) const;
   void _range(double range);

private:

   // Default Accuracy [T]
   static const double _ACCURACY;

   // Default Range [T]
   static const double _RANGE;

   // Variables
   double _accuracy_;
   double _range_;
   Part* _part_;
   mutable bool _init;
   mutable Rotation _rotation;
   mutable std::default_random_engine _generator;
   mutable std::normal_distribution<double> _distribution;
   mutable std::vector<Module::Magnetics*> _magnetics;
};


// Clone
inline CubeSim::System* CubeSim::System::Magnetometer::clone(void) const
{
   // Return Copy
   return new Magnetometer(*this);
}


// Constructor
inline CubeSim::System::Magnetometer::Magnetometer(double accuracy, double range) : _part_(), _init(),
   _distribution(0.0, 1.0)
{
   // Initialize
   _accuracy(accuracy);
   _range(range);
}


// Copy Constructor
inline CubeSim::System::Magnetometer::Magnetometer(const Magnetometer& magnetometer) : System(magnetometer),
   _accuracy_(magnetometer._accuracy_), _range_(magnetometer._range_), _part_(), _init(),
   _distribution(magnetometer._distribution)
{
}


// Get Accuracy [T]
inline double CubeSim::System::Magnetometer::_accuracy(void) const
{
   // Return Accuracy
   return _accuracy_;
}


// Set Accuracy [T]
inline void CubeSim::System::Magnetometer::_accuracy(double accuracy)
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
inline CubeSim::Part* CubeSim::System::Magnetometer::_part(void) const
{
   // Return Part
   return _part_;
}


// Set Part
inline void CubeSim::System::Magnetometer::_part(Part& part)
{
   // Set Part
   _part_ = &part;
}


// Get Range [T]
inline double CubeSim::System::Magnetometer::_range(void) const
{
   // Return Range
   return _range_;
}


// Set Range [T]
inline void CubeSim::System::Magnetometer::_range(double range)
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
