

// CUBESIM - CELESTIAL BODY - MARS


// Includes
#include "../celestial_body.hpp"


// Preprocessor Directives
#pragma once


// Class Mars
class CubeSim::CelestialBody::Mars : public CelestialBody
{
public:

   // Constructor
   Mars(void);

   // Clone
   virtual CelestialBody* clone(void) const;
};


// Constructor
inline CubeSim::CelestialBody::Mars::Mars(void) : CelestialBody(3.38992E6, 5.89001E-3, 3955.919195, 210.0,
   Vector3D(2.069270543E11, -3.560689745E9, -5.147936537E9), Vector3D(1.304308833E3, 2.628158890E4, 5.188465741E2))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Mars::clone(void) const
{
   // Return Copy
   return new Mars(*this);
}
