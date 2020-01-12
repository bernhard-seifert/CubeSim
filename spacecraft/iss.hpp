

// CUBESIM - SPACECRAFT - ISS


// Includes
#include "../spacecraft.hpp"


// Preprocessor Directives
#pragma once


// Class ISS
class CubeSim::Spacecraft::ISS : public Spacecraft
{
public:

   // Constructor
   ISS(void);

   // Clone
   virtual Spacecraft* clone(void) const;

private:

   // Class _System
   class _System;
};


// Clone
inline CubeSim::Spacecraft* CubeSim::Spacecraft::ISS::clone(void) const
{
   // Return Copy
   return new ISS(*this);
}
