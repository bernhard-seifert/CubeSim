

// CUBESIM - CELESTIAL BODY - VENUS


// Includes
#include "../celestial_body.hpp"


// Preprocessor Directives
#pragma once


// Class Venus
class CubeSim::CelestialBody::Venus : public CelestialBody
{
public:

   // Constructor
   Venus(void);

   // Clone
   virtual CelestialBody* clone(void) const;
};


// Constructor
inline CubeSim::CelestialBody::Venus::Venus(void) : CelestialBody(6.051800E+6, 0.000E+00, 5243.0, 737.2,
   Vector3D(8.265257646E+10, -7.134718253E+10, -5.741900324E+9), Vector3D(2.271112507E+4, 2.634865255E+4,
   -9.494098281E+2))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Venus::clone(void) const
{
   // Return Copy
   return new Venus(*this);
}
