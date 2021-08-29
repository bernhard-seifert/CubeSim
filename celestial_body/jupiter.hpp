

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
inline CubeSim::CelestialBody::Jupiter::Jupiter(void) : CelestialBody(6.991100E+7, 6.487E-2, 1418.214440, 109.9,
   Vector3D(5.978410556E11, 4.387048656E11, -1.520164176E10), Vector3D(-7.892632216E3, 1.115034526E4, 1.305100444E2))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Jupiter::clone(void) const
{
   // Return Copy
   return new Jupiter(*this);
}
