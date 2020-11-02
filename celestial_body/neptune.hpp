

// CUBESIM - CELESTIAL BODY - NEPTUNE


// Includes
#include "../celestial_body.hpp"


// Preprocessor Directives
#pragma once


// Class Neptune
class CubeSim::CelestialBody::Neptune : public CelestialBody
{
public:

   // Constructor
   Neptune(void);

   // Clone
   virtual CelestialBody* clone(void) const;
};


// Constructor
inline CubeSim::CelestialBody::Neptune::Neptune(void) : CelestialBody(2.4766E+7, 1.71E-2, 1637.483061, 72.0,
   Vector3D(2.513785452E12, -3.739265136E12, 1.907027541E10), Vector3D(4.475107950E3, 3.062850548E3, -1.667293984E2))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Neptune::clone(void) const
{
   // Return Copy
   return new Neptune(*this);
}
