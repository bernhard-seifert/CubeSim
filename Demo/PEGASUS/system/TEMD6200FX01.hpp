

// TEMD6200FX01 VISIBLE LIGHT PHOTO DIODE


// Includes
#include "../CubeSim/system/photodetector.hpp"


// Preprocessor Directives
#pragma once


// Class TEMD6200FX01
class TEMD6200FX01 : public CubeSim::System::Photodetector
{
public:

   // Constructor
   TEMD6200FX01(void);

   // Copy Constructor
   TEMD6200FX01(const TEMD6200FX01& TEMD6200FX01);

   // Clone
   virtual System* clone(void) const;

private:

   // Accuracy [W/m^2]
   static const double _ACCURACY;

   // Opening Angle [rad]
   static const double _ANGLE;

   // Area [m^2]
   static const double _AREA;

   // Range [W/m^2]
   static const double _RANGE;
};


// Copy Constructor
inline TEMD6200FX01::TEMD6200FX01(const TEMD6200FX01& TEMD6200FX01) : Photodetector(TEMD6200FX01)
{
   // Set Part
   _part(*this->assembly("Assembly")->part("Photo Diode"));
}


// Clone
inline CubeSim::System* TEMD6200FX01::clone(void) const
{
   // Return Copy
   return new TEMD6200FX01(*this);
}
