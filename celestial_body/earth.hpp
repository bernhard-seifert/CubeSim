

// CUBESIM - CELESTIAL BODY - EARTH


// Includes
#include <algorithm>
#include <igrf.hpp>
#include "../celestial_body.hpp"


// Preprocessor Directives
#pragma once


// Class Earth
class CubeSim::CelestialBody::Earth : public CelestialBody
{
public:

   // Constructor
   Earth(void);

   // Clone
   virtual CelestialBody* clone(void) const;

   // Compute magnetic Field (Body Frame) [T]
   virtual const Vector3D magnetic_field(const Vector3D& point) const;
   using CelestialBody::magnetic_field;

   // Compute relative Reflectivity
   virtual double reflectivity(double longitude, double latitude) const;

private:

   // IGRF Model Refresh Time [s]
   static const double _IGRF_REFRESH;

   // Variables
   mutable IGRF _igrf;
};


// Constructor
inline CubeSim::CelestialBody::Earth::Earth(void) : CelestialBody(6.37101E6, 3.352811E-3, 5531.955784, 254.0,
   Vector3D(-2.627892929E10, 1.445102394E11, 3.022818136E7), Vector3D(-2.983052803E4, -5.220465685E3, -1.014621798E-1),
   Vector3D(0.000000000E0, 2.900635596E-5, 6.690385214E-5),
   Rotation(Vector3D(-1.641460522E-1, 2.003678031E-1, 9.658720500E-1), 1.802808357))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Earth::clone(void) const
{
   // Return Copy
   return new Earth(*this);
}


// Compute relative Reflectivity
inline double CubeSim::CelestialBody::Earth::reflectivity(double longitude, double latitude) const
{
   // Compute and return Reflectivity (Data from SSC03-XI-7)
   return std::min((((0.0346 * latitude - 0.0125) * latitude + 0.2369) * latitude + 0.0055) * latitude + 0.2049, 1.0);
}
