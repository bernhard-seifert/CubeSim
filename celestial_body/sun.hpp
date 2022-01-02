

// CUBESIM - CELESTIAL BODY - SUN


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


// Preprocessor Directives
#pragma once


// Class Sun
class CubeSim::CelestialBody::Sun : public CelestialBody
{
public:

   // Constructor
   Sun(void);

   // Clone
   virtual CelestialBody* clone(void) const;
};


// Constructor (Density modified to match total Mass of 1.98847E30 kg)
inline CubeSim::CelestialBody::Sun::Sun(void) : CelestialBody(6.957E8, 5.0E-5, 1409.892950, 5772.0, Vector3D(),
   Vector3D())
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Sun::clone(void) const
{
   // Return Copy
   return new Sun(*this);
}
