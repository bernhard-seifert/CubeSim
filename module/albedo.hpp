

// CUBESIM - MODULE - ALBEDO


// Includes
#include "../celestial_body.hpp"
#include "../grid.hpp"
#include "../module.hpp"


// Preprocessor Directives
#pragma once


// Class Albedo
class CubeSim::Module::Albedo : public Module
{
public:

   // Earth
   class Earth;

   // Constructor
   Albedo(uint32_t resolution = _RESOLUTION);
   Albedo(CelestialBody& celestial_body, uint32_t resolution = _RESOLUTION);

   // Specific Celestial Body
   const CelestialBody* celestial_body(void) const;
   void celestial_body(const CelestialBody* celestial_body);

   // Clone
   virtual Module* clone(void) const;

   // Compute Irradiance [W/m^2]
   double irradiance(const Vector3D& point, const Vector3D& direction, double angle = Constant::PI) const;

   // Resolution (Number of Grid Points)
   uint32_t resolution(void) const;
   void resolution(uint32_t resolution);

private:

   // Default Resolution (Number of Grid Points)
   static const uint32_t _RESOLUTION = 1000;

   // Compute Irradiance [W/m^2]
   double _irradiance(const CelestialBody& celestial_body, const Vector3D& point, const Vector3D& direction,
      double angle) const;

   // Variables
   const CelestialBody* _celestial_body;
   std::vector<Vector3D> _grid;
   mutable bool _init;
   mutable std::vector<Light*> _light;
};


// Constructor
inline CubeSim::Module::Albedo::Albedo(uint32_t resolution) : _celestial_body(), _init()
{
   // Initialize
   this->resolution(resolution);
}


// Constructor
inline CubeSim::Module::Albedo::Albedo(CelestialBody& celestial_body, uint32_t resolution) : _init()
{
   // Initialize
   this->celestial_body(&celestial_body);
   this->resolution(resolution);
}


// Get specific Celestial Body
inline const CubeSim::CelestialBody* CubeSim::Module::Albedo::celestial_body(void) const
{
   // Return specific Celestial Body
   return _celestial_body;
}


// Set specific Celestial Body
inline void CubeSim::Module::Albedo::celestial_body(const CelestialBody* celestial_body)
{
   // Set specific Celestial Body
   _celestial_body = celestial_body;
}


// Clone
inline CubeSim::Module* CubeSim::Module::Albedo::clone(void) const
{
   // Return Copy
   return new Albedo(*this);
}


// Get Resolution (Number of Grid Points)
inline uint32_t CubeSim::Module::Albedo::resolution(void) const
{
   // Return Resolution
   return _grid.size();
}


// Set Resolution (Number of Grid Points)
inline void CubeSim::Module::Albedo::resolution(uint32_t resolution)
{
   // Update Grid
   _grid = Grid3D(resolution).points();
}
