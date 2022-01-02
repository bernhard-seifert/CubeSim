

// CUBESIM - CELESTIAL BODY - MOON


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


// Class Moon
class CubeSim::CelestialBody::Moon : public CelestialBody
{
public:

   // Constructor
   Moon(void);

   // Clone
   virtual CelestialBody* clone(void) const;
};


// Constructor
inline CubeSim::CelestialBody::Moon::Moon(void) : CelestialBody(1.73753E6, 0.0012, 3344.588581, 270.4,
   Vector3D(-2.659657953E10, 1.442683562E11, 6.678400538E7), Vector3D(-2.926974097E4, -6.020397948E3, -1.740793458E0))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Moon::clone(void) const
{
   // Return Copy
   return new Moon(*this);
}
