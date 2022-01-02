

// CUBESIM - CELESTIAL BODY - URANUS


// Includes
#include "../celestial_body.hpp"


// Preprocessor Directives
#pragma once


// Class Uranus
class CubeSim::CelestialBody::Uranus : public CelestialBody
{
public:

   // Constructor
   Uranus(void);

   // Clone
   virtual CelestialBody* clone(void) const;
};


// Constructor
inline CubeSim::CelestialBody::Uranus::Uranus(void) : CelestialBody(2.5362E7, 2.293E-2, 1300.229399, 58.1,
   Vector3D(2.157706703E12, -2.055242912E12, -3.559264257E10), Vector3D(4.646953713E3, 4.6143611105E3, -4.301340943E1))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Uranus::clone(void) const
{
   // Return Copy
   return new Uranus(*this);
}
