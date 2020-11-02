

// CUBESIM - CELESTIAL BODY - SUN


// Includes
#include "../celestial_body.hpp"


// Preprocessor Directives
#pragma once


// Class Sun
class CubeSim::CelestialBody::Sun : public CelestialBody
{
public:

   // Constructor
   Sun(void);

   // Clone
   virtual CelestialBody* clone(void) const;
};


// Constructor
inline CubeSim::CelestialBody::Sun::Sun(void) : CelestialBody(6.957E8, 5.0E-5, 1409.914222, 5772.0,
   Vector3D(-1.068000648E9, -4.176802126E8, 3.084467021E7), Vector3D(9.305300848E0, -1.283176670E1, -1.631528028E-1))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Sun::clone(void) const
{
   // Return Copy
   return new Sun(*this);
}
