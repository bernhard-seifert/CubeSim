

// CUBESIM - MODULE - EPHEMERIS


// Includes
#include "../module.hpp"


// Preprocessor Directives
#pragma once


// Class Ephemeris
class CubeSim::Module::Ephemeris : public Module
{
public:

   // Clone
   virtual Module* clone(void) const;

private:

   // Behavior
   virtual void _behavior(void);
};


// Clone
inline CubeSim::Module* CubeSim::Module::Ephemeris::clone(void) const
{
   // Return Copy
   return new Ephemeris(*this);
}
