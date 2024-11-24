

// OEM615 GNSS RECEIVER


// Includes
#include "../CubeSim/system/gnss.hpp"


// Preprocessor Directives
#pragma once


// Class OEM615
class OEM615 : public CubeSim::System::GNSS
{
public:

   // Constructor
   OEM615(void);

   // Copy Constructor
   OEM615(const OEM615& oem615);

   // Clone
   virtual System* clone(void) const;

private:

   // Spatial Accuracy [m]
   static const double _SPATIAL_ACCURACY;

   // Temporal Accuracy [s]
   static const double _TEMPORAL_ACCURACY;
};


// Copy Constructor
inline OEM615::OEM615(const OEM615& oem615) : GNSS(oem615)
{
}


// Clone
inline CubeSim::System* OEM615::clone(void) const
{
   // Return Copy
   return new OEM615(*this);
}
