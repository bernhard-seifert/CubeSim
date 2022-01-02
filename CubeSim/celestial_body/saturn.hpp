

// CUBESIM - CELESTIAL BODY - SATURN


// Includes
#include "../celestial_body.hpp"


// Preprocessor Directives
#pragma once


// Class Saturn
class CubeSim::CelestialBody::Saturn : public CelestialBody
{
public:

   // Constructor
   Saturn(void);

   // Clone
   virtual CelestialBody* clone(void) const;
};


// Constructor
inline CubeSim::CelestialBody::Saturn::Saturn(void) : CelestialBody(5.8232E+7, 9.796E-2, 761.743397, 81.0,
   Vector3D(9.576383365E+11, 9.821475308E11, -5.518981181E10), Vector3D(-7.419580383E3, 6.725982471E3, 1.775012040E2))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Saturn::clone(void) const
{
   // Return Copy
   return new Saturn(*this);
}
