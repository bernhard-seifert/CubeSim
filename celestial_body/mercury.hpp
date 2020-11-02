

// CUBESIM - CELESTIAL BODY - MERCURY


// Includes
#include "../celestial_body.hpp"


// Preprocessor Directives
#pragma once


// Class Mercury
class CubeSim::CelestialBody::Mercury : public CelestialBody
{
public:

   // Constructor
   Mercury(void);

   // Clone
   virtual CelestialBody* clone(void) const;
};


// Constructor
inline CubeSim::CelestialBody::Mercury::Mercury(void) : CelestialBody(2.44E+6, 0.0, 5426.489670, 440.0,
   Vector3D(-2.212062176E10, -6.682431830E10, -3.461601353E9), Vector3D(3.666229236E4, -1.230266987E4, -4.368336052E3))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Mercury::clone(void) const
{
   // Return Copy
   return new Mercury(*this);
}
