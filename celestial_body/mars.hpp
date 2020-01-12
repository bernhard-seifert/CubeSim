

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
inline CubeSim::CelestialBody::Mars::Mars(void) : CelestialBody(3.389900E+6, 6.480E-03, 3934.0, 208.2,
   Vector3D(2.032572503E+11, -4.126166240E+10, -5.860794896E+9), Vector3D(5.753284369E+3, 2.582712644E+4,
   3.997562922E+2))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Mars::clone(void) const
{
   // Return Copy
   return new Mars(*this);
}
