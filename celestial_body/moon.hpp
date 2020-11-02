

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
inline CubeSim::CelestialBody::Moon::Moon(void) : CelestialBody(1.73753E6, 0.0, 3344.588581, 250.2,
   Vector3D(-2.659657953E10, 1.442683562E11, 6.678400538E7), Vector3D(-2.926974097E4, -6.020397948E3, -1.740793458E0))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Moon::clone(void) const
{
   // Return Copy
   return new Moon(*this);
}
