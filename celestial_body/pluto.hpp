

// CUBESIM - CELESTIAL BODY - PLUTO


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


// Class Pluto
class CubeSim::CelestialBody::Pluto : public CelestialBody
{
public:

   // Constructor
   Pluto(void);

   // Clone
   virtual CelestialBody* clone(void) const;
};


// Constructor
inline CubeSim::CelestialBody::Pluto::Pluto(void) : CelestialBody(1.1883E6, 0.0, 1859.553540, 37.5,
   Vector3D(-1.478626341E12, -4.182878119E12, 8.753002593E11), Vector3D(5.271230990E3, -2.661751412E3, -1.242036207E3))
{
}


// Clone
inline CubeSim::CelestialBody* CubeSim::CelestialBody::Pluto::clone(void) const
{
   // Return Copy
   return new Pluto(*this);
}
