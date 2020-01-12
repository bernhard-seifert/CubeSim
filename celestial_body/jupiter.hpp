

// CUBESIM - CELESTIAL BODY - JUPITER


// Includes
#include "../celestial_body.hpp"


// Preprocessor Directives
#pragma once


// Class Earth
class CubeSim::CelestialBody::Jupiter : public CelestialBody
{
 public:

  // Constructor
   Jupiter(void);

   // Clone
   virtual CelestialBody* clone(void) const;
};


// Constructor
inline CubeSim::CelestialBody::Jupiter::Jupiter(void) : CelestialBody(6.991100E+7, 6.487E-02, 1326.2, 163.2,
   Vector3D(-5.575103879E+11, 5.674636167E+11, 1.010688851E+10), Vector3D(-9.475619834E+3, -8.540278736E+3,
   2.475675327E+2))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Jupiter::clone(void) const
{
   // Return Copy
   return new Jupiter(*this);
}
