

// CUBESIM - CELESTIAL BODY - SATURN


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


// Class Saturn
class CubeSim::CelestialBody::Saturn : public CelestialBody
{
public:

   // Constructor
   Saturn(void);

   // Clone
   virtual CelestialBody* clone(void) const;
};


// Constructor
inline CubeSim::CelestialBody::Saturn::Saturn(void) : CelestialBody(5.8232E+7, 9.796E-2, 761.743397, 81.0,
   Vector3D(9.576383365E+11, 9.821475308E11, -5.518981181E10), Vector3D(-7.419580383E3, 6.725982471E3, 1.775012040E2))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Saturn::clone(void) const
{
   // Return Copy
   return new Saturn(*this);
}
