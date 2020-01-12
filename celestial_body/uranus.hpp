

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
inline CubeSim::CelestialBody::Uranus::Uranus(void) : CelestialBody(2.536200E+7, 2.293E-02, 1270.0, 78.2,
   Vector3D(2.888221840E+12, 7.854648158E+11, -3.450056598E+10), Vector3D(-1.836849219E+3, 6.253875933E+3,
   4.683973821E+1))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Uranus::clone(void) const
{
   // Return Copy
   return new Uranus(*this);
}
