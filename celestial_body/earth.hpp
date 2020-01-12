

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
inline CubeSim::CelestialBody::Earth::Earth(void) : CelestialBody(6.378137E6, 3.352811E-3, 5513.432, 288.2,
   Vector3D(-2.518093252E+10, 1.447275912E+11, -2.498037967E+7), Vector3D(-2.980233994E+4, -5.296316724E+3,
   9.984795913E-1), Vector3D(0.000000000E+00, 2.900635468E-05, 6.690385270E-05), Rotation(Vector3D(-2.384463898E-01,
   -1.972639971E-01, -9.509102137E-01), 1.431978381))
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
