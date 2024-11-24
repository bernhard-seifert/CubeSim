

// ADAPTER BOARD MAGNETORQUER


// Includes
#include "../CubeSim/system/magnetorquer.hpp"


// Preprocessor Directives
#pragma once


// Class AdapterTorquer
class AdapterTorquer : public CubeSim::System::Magnetorquer
{
public:

   // Constructor
   AdapterTorquer(void);

   // Copy Constructor
   AdapterTorquer(const AdapterTorquer& adapter_torquer);

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
inline AdapterTorquer::AdapterTorquer(const AdapterTorquer& adapter_torquer) : Magnetorquer(adapter_torquer)
{
   // Set Part
   _part(*this->assembly("Assembly")->part("Coil"));
}


// Clone
inline CubeSim::System* AdapterTorquer::clone(void) const
{
   // Return Copy
   return new AdapterTorquer(*this);
}
