

// CUBESIM - MODULE - ALBEDO


// Copyright (c) 2022 Bernhard Seifert
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sub-license, and / or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
// Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
// OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


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
   static const uint32_t _RESOLUTION = 400;

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
