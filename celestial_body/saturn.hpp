

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
inline CubeSim::CelestialBody::Saturn::Saturn(void) : CelestialBody(5.823200E+7, 9.796E-02, 687.1, 133.2,
   Vector3D(-8.086233424E+11, -1.249156227E+12, 5.390151707E+10), Vector3D(7.580739881E+3, -5.277321267E+3,
   -2.093410854E+2))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Saturn::clone(void) const
{
   // Return Copy
   return new Saturn(*this);
}
