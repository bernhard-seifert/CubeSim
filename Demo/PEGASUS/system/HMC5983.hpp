

// HMC5983 DIGITAL COMPASS


// Includes
#include "../CubeSim/system/magnetometer.hpp"


// Preprocessor Directives
#pragma once


// Class HMC5983
class HMC5983 : public CubeSim::System::Magnetometer
{
public:

   // Constructor
   HMC5983(void);

   // Copy Constructor
   HMC5983(const HMC5983& hmc5983);

   // Clone
   virtual System* clone(void) const;

private:

   // Accuracy [T]
   static const double _ACCURACY;

   // Range [T]
   static const double _RANGE;
};


// Copy Constructor
inline HMC5983::HMC5983(const HMC5983& hmc5983) : Magnetometer(hmc5983)
{
   // Set Part
   _part(*this->assembly("Assembly")->part("Digital Compass"));
}


// Clone
inline CubeSim::System* HMC5983::clone(void) const
{
   // Return Copy
   return new HMC5983(*this);
}
