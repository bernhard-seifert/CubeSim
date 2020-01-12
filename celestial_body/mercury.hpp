

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
inline CubeSim::CelestialBody::Mercury::Mercury(void) : CelestialBody(2.440000E+6, 0.000E+00, 5427.0, 440.2,
   Vector3D(5.088632720E+10, -3.058604451E+10, -7.138828499E+9), Vector3D(1.562065207E+4, 4.394732263E+4,
   2.157455516E+3))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Mercury::clone(void) const
{
   // Return Copy
   return new Mercury(*this);
}
