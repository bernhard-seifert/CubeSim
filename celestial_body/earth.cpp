

// CUBESIM - CELESTIAL BODY - EARTH


// Includes
#include "earth.hpp"
#include "../simulation.hpp"


// Compute magnetic Field (Body Frame) [T]
const CubeSim::Vector3D CubeSim::CelestialBody::Earth::magnetic_field(const Vector3D& point) const
{
   // Check Simulation
   if (!simulation())
   {
      // Exception
      throw Exception::Failed();
   }

   // Check IGRF Model Time
   if (_IGRF_REFRESH < (abs(_igrf.time() - simulation()->time()) / 1000.0))
   {
      // Set IGRF Time
      _igrf.time(simulation()->time());
   }

   // Compute magnetic Field
   IGRF::Field B = _igrf(point.x(), point.y(), point.z());

   // Return magnetic Field
   return Vector3D(B.x(), B.y(), B.z());
}


// IGRF Model Refresh Time [s]
const double CubeSim::CelestialBody::Earth::_IGRF_REFRESH = 24.0 * 3600;
