

// MONITOR


// Includes
#include <console.hpp>
#include "../CubeSim/celestial_body.hpp"
#include "../CubeSim/system.hpp"


// Preprocessor Directives
#pragma once


// Undefine
#undef _LO


// Class Monitor
class Monitor : public CubeSim::System
{
public:

   // Clone
   virtual System* clone(void) const;

private:

   // Behavior
   virtual void _behavior(void);

   // Compute ECI Frame
   const CubeSim::Rotation& _ECI(void) const;

   // Compute LO Frame
   const CubeSim::Rotation _LO(void) const;

   // Get Earth
   const CubeSim::CelestialBody& _earth(void) const;

   // Print Number
   void _print(uint8_t x, uint8_t y, const char* format, double number = 0.0, uint8_t color = Console::COLOR_LIGHT_GRAY,
      uint8_t background = Console::COLOR_BLACK);

   // Get Spacecraft
   const CubeSim::Spacecraft& _spacecraft(void) const;
};


// Clone
inline CubeSim::System* Monitor::clone(void) const
{
   // Return Copy
   return new Monitor(*this);
}
