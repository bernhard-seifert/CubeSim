

// ADXL330 DIGITAL ACCELEROMETER


// Includes
#include "../CubeSim/system/accelerometer.hpp"


// Preprocessor Directives
#pragma once


// Class ADXL330
class ADXL330 : public CubeSim::System::Accelerometer
{
public:

   // Constructor
   ADXL330(void);

   // Copy Constructor
   ADXL330(const ADXL330& ADXL330);

   // Clone
   virtual System* clone(void) const;

private:

   // Accuracy for 1g Range [m/s^2]
   static const double _ACCURACY;

   // Range [m/s^2]
   static const double _RANGE;
};


// Copy Constructor
inline ADXL330::ADXL330(const ADXL330& ADXL330) : Accelerometer(ADXL330)
{
   // Set Part
   _part(*this->assembly("Assembly")->part("Digital Accelerometer"));
}


// Clone
inline CubeSim::System* ADXL330::clone(void) const
{
   // Return Copy
   return new ADXL330(*this);
}
