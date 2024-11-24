

// SIDEPANEL MAGNETORQUER


// Includes
#include "../CubeSim/system/magnetorquer.hpp"


// Preprocessor Directives
#pragma once


// Class SidepanelTorquer
class SidepanelTorquer : public CubeSim::System::Magnetorquer
{
public:

   // Constructor
   SidepanelTorquer(void);

   // Copy Constructor
   SidepanelTorquer(const SidepanelTorquer& sidepanel_torquer);

   // Clone
   virtual System* clone(void) const;

private:

   // Accuracy [A]
   static const double _ACCURACY;

   // Effective Coil Area [m^2]
   static const double _AREA;

   // Range [A]
   static const double _RANGE;

   // Time Step [s]
   static const double _TIME_STEP;
};


// Copy Constructor
inline SidepanelTorquer::SidepanelTorquer(const SidepanelTorquer& sidepanel_torquer) : Magnetorquer(sidepanel_torquer)
{
   // Set Part
   _part(*this->assembly("Assembly")->part("Coil"));
}


// Clone
inline CubeSim::System* SidepanelTorquer::clone(void) const
{
   // Return Copy
   return new SidepanelTorquer(*this);
}
