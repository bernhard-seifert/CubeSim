

// CUBESIM - MODULE - MAGNETICS


// Includes
#include "../celestial_body.hpp"
#include "../module.hpp"


// Preprocessor Directives
#pragma once


// Class Magnetics
class CubeSim::Module::Magnetics : public Module
{
public:

   // Constructor
   Magnetics(void);
   Magnetics(CelestialBody& celestial_body);

   // Specific Celestial Body
   const CelestialBody* celestial_body(void) const;
   void celestial_body(const CelestialBody* celestial_body);

   // Clone
   virtual Module* clone(void) const;

   // Compute magnetic Field [T]
   const Vector3D field(const Vector3D& point) const;

private:

   // Compute magnetic Field [T]
   const Vector3D _field(const CelestialBody& celestial_body, const Vector3D& point) const;

   // Variables
   const CelestialBody* _celestial_body;
};


// Constructor
inline CubeSim::Module::Magnetics::Magnetics(void) : _celestial_body()
{
}


// Constructor
inline CubeSim::Module::Magnetics::Magnetics(CelestialBody& celestial_body)
{
   // Initialize
   this->celestial_body(&celestial_body);
}


// Get specific Celestial Body
inline const CubeSim::CelestialBody* CubeSim::Module::Magnetics::celestial_body(void) const
{
   // Return specific Celestial Body
   return _celestial_body;
}


// Set specific Celestial Body
inline void CubeSim::Module::Magnetics::celestial_body(const CelestialBody* celestial_body)
{
   // Set specific Celestial Body
   _celestial_body = celestial_body;
}


// Clone
inline CubeSim::Module* CubeSim::Module::Magnetics::clone(void) const
{
   // Return Copy
   return new Magnetics(*this);
}
