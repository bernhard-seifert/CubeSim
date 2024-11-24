

// CUBESIM - MODULE - MAGNETICS


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
