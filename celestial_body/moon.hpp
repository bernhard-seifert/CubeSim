

// CUBESIM - CELESTIAL BODY - MOON


// Includes
#include "../celestial_body.hpp"


// Preprocessor Directives
#pragma once


// Class Moon
class CubeSim::CelestialBody::Moon : public CelestialBody
{
public:

   // Constructor
   Moon(void);

   // Clone
   virtual CelestialBody* clone(void) const;
};


// Constructor
inline CubeSim::CelestialBody::Moon::Moon(void) : CelestialBody(1.737530E6, 1.200E-03, 3343.7, 250.2,
   Vector3D(-2.493673284E+10, 1.450227363E+11, -4.439107656E+7), Vector3D(-3.056658317E+4, -4.617726841E+3,
   -7.424309523E+1))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Moon::clone(void) const
{
   // Return Copy
   return new Moon(*this);
}
