

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
inline CubeSim::CelestialBody::Neptune::Neptune(void) : CelestialBody(2.462400E+7, 1.708E-02, 1638.0, 73.2,
   Vector3D(4.118382583E+12, -1.771801384E+12, -5.842544184E+10), Vector3D(2.111228163E+3, 5.025248015E+3,
   -1.515076208E+2))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Neptune::clone(void) const
{
   // Return Copy
   return new Neptune(*this);
}
