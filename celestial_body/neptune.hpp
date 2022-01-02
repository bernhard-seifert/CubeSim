

// CUBESIM - CELESTIAL BODY - NEPTUNE


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


// Class Neptune
class CubeSim::CelestialBody::Neptune : public CelestialBody
{
public:

   // Constructor
   Neptune(void);

   // Clone
   virtual CelestialBody* clone(void) const;
};


// Constructor
inline CubeSim::CelestialBody::Neptune::Neptune(void) : CelestialBody(2.4766E+7, 1.71E-2, 1637.483061, 46.6,
   Vector3D(2.513785452E12, -3.739265136E12, 1.907027541E10), Vector3D(4.475107950E3, 3.062850548E3, -1.667293984E2))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Neptune::clone(void) const
{
   // Return Copy
   return new Neptune(*this);
}
