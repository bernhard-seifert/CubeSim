

// CUBESIM - SPACECRAFT - HUBBLE


// Includes
#include "../spacecraft.hpp"


// Preprocessor Directives
#pragma once


// Class Hubble
class CubeSim::Spacecraft::Hubble : public Spacecraft
{
public:

   // Constructor
   Hubble(void);

   // Clone
   virtual Spacecraft* clone(void) const;

private:

   // Class _System
   class _System;
};


// Clone
inline CubeSim::Spacecraft* CubeSim::Spacecraft::Hubble::clone(void) const
{
   // Return Copy
   return new Hubble(*this);
}
