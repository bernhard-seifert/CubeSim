

// CUBESIM - CELESTIAL BODY - PLUTO


// Includes
#include "../celestial_body.hpp"


// Preprocessor Directives
#pragma once


// Class Pluto
class CubeSim::CelestialBody::Pluto : public CelestialBody
{
public:

   // Constructor
   Pluto(void);

   // Clone
   virtual CelestialBody* clone(void) const;
};


// Constructor
inline CubeSim::CelestialBody::Pluto::Pluto(void) : CelestialBody(1.1883E6, 0.0, 1859.553540, 44.0,
   Vector3D(-1.478626341E12, -4.182878119E12, 8.753002593E11), Vector3D(5.271230990E3, -2.661751412E3, -1.242036207E3))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Pluto::clone(void) const
{
   // Return Copy
   return new Pluto(*this);
}
