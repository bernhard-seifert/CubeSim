

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
inline CubeSim::CelestialBody::Venus::Venus(void) : CelestialBody(6.05184E6, 0.0, 5243.777460, 226.6,
   Vector3D(-1.085735509E11, -3.784200933E9, 6.190064473E9), Vector3D(8.984651055E2, -3.517203951E4, -5.320225583E2))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Venus::clone(void) const
{
   // Return Copy
   return new Venus(*this);
}
