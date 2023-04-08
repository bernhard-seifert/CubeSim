

// CUBESIM - MODULE - LIGHT


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


// Class Light
class CubeSim::Module::Light : public Module
{
public:

   // Default Resolution (Number of Points)
   static const uint32_t DEFAULT_RESOLUTION = 100;

   // Computation Models
   static const uint8_t MODEL_POINT = 1;
   static const uint8_t MODEL_DISK = 2;

   // Constructor
   Light(uint8_t model = MODEL_POINT, uint32_t resolution = DEFAULT_RESOLUTION);
   Light(CelestialBody& celestial_body, uint8_t model = MODEL_POINT, uint32_t resolution = DEFAULT_RESOLUTION);

   // Specific Celestial Body
   const CelestialBody* celestial_body(void) const;
   void celestial_body(const CelestialBody* celestial_body);

   // Clone
   virtual Module* clone(void) const;

   // Compute Irradiance [W/m^2]
   double irradiance(const Vector3D& point, const Vector3D& direction, double angle = Constant::PI) const;

   // Computation Model
   uint8_t model(void) const;
   void model(uint8_t model);

   // Resolution (Number of Grid Points)
   uint32_t resolution(void) const;
   void resolution(uint32_t resolution);

private:

   // Temperature Limit (Red Star) [K]
   static const double _TEMPERATURE;

   // Compute Irradiance [W/m^2]
   double _irradiance(const CelestialBody& celestial_body, const Vector3D& point, const Vector3D& direction,
      double angle) const;

   // Variables
   uint8_t _model;
   const CelestialBody* _celestial_body;
   std::vector<Vector2D> _grid;
};


// Constructor
inline CubeSim::Module::Light::Light(uint8_t model, uint32_t resolution) : _celestial_body()
{
   // Initialize
   this->model(model);
   this->resolution(resolution);
}


// Constructor
inline CubeSim::Module::Light::Light(CelestialBody& celestial_body, uint8_t model, uint32_t resolution)
{
   // Initialize
   this->celestial_body(&celestial_body);
   this->model(model);
   this->resolution(resolution);
}


// Get specific Celestial Body
inline const CubeSim::CelestialBody* CubeSim::Module::Light::celestial_body(void) const
{
   // Return specific Celestial Body
   return _celestial_body;
}


// Set specific Celestial Body
inline void CubeSim::Module::Light::celestial_body(const CelestialBody* celestial_body)
{
   // Set specific Celestial Body
   _celestial_body = celestial_body;
}


// Clone
inline CubeSim::Module* CubeSim::Module::Light::clone(void) const
{
   // Return Copy
   return new Light(*this);
}


// Get Computation Model
inline uint8_t CubeSim::Module::Light::model(void) const
{
   // Return Computation Model
   return _model;
}


// Set Computation Model
inline void CubeSim::Module::Light::model(uint8_t model)
{
   // Check Computation Model
   if ((model != MODEL_POINT) && (model != MODEL_DISK))
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Computation Model
   _model = model;
}


// Get Resolution (Number of Grid Points)
inline uint32_t CubeSim::Module::Light::resolution(void) const
{
   // Return Resolution
   return static_cast<uint32_t>(_grid.size());
}


// Set Resolution (Number of Grid Points)
inline void CubeSim::Module::Light::resolution(uint32_t resolution)
{
   // Update Grid
   _grid = Grid2D(resolution).points();
}
