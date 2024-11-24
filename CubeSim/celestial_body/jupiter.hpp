

// CUBESIM - CELESTIAL BODY - JUPITER


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


// Class Earth
class CubeSim::CelestialBody::Jupiter : public CelestialBody
{
 public:

  // Constructor
   Jupiter(void);

   // Clone
   virtual CelestialBody* clone(void) const;
};


// Constructor
inline CubeSim::CelestialBody::Jupiter::Jupiter(void) : CelestialBody(6.991100E+7, 6.487E-2, 1418.214440, 109.9,
   Vector3D(5.978410556E11, 4.387048656E11, -1.520164176E10), Vector3D(-7.892632216E3, 1.115034526E4, 1.305100444E2))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Jupiter::clone(void) const
{
   // Return Copy
   return new Jupiter(*this);
}
