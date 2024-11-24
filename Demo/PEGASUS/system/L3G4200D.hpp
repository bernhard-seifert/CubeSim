

// L3G4200D DIGITAL GYROSCOPE


// Includes
#include "../CubeSim/system/gyroscope.hpp"


// Preprocessor Directives
#pragma once


// Class L3G4200D
class L3G4200D : public CubeSim::System::Gyroscope
{
public:

   // Constructor
   L3G4200D(void);

   // Copy Constructor
   L3G4200D(const L3G4200D& l3g4200d);

   // Clone
   virtual System* clone(void) const;

private:

   // Accuracy [rad/s]
   static const double _ACCURACY;

   // Range [rad/s]
   static const double _RANGE;
};


// Copy Constructor
inline L3G4200D::L3G4200D(const L3G4200D& l3g4200d) : Gyroscope(l3g4200d)
{
   // Set Part
   _part(*this->assembly("Assembly")->part("Digital Gyroscope"));
}


// Clone
inline CubeSim::System* L3G4200D::clone(void) const
{
   // Return Copy
   return new L3G4200D(*this);
}
