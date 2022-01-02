

// CUBESIM - SPACECRAFT - ISS


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
#include "iss.hpp"
#include "../part/box.hpp"


// Class _System
class CubeSim::Spacecraft::ISS::_System : public System
{
private:

   // Clone
   virtual System* clone() const;
};


// Constructor
CubeSim::Spacecraft::ISS::ISS(void) : Spacecraft(Vector3D(-2.517666808E+10, 1.447271656E+11, -1.972759848E+07),
   Vector3D(-2.414136217E+04, -2.525467722E+03, -4.370673682E+03))
{
   // Spacecraft Bus (Envelope)
   Part::Box bus(72.8, 108.5, 20.0);
   bus.material(Material("", 2.849));

   // Make Assembly
   Assembly assembly;
   assembly.insert("Bus", bus);

   // Make System
   _System system;
   system.insert("Assembly", assembly);

   // Insert System
   insert("System", system);
}


// Clone
inline CubeSim::System* CubeSim::Spacecraft::ISS::_System::clone() const
{
   // Return Copy
   return new _System(*this);
}
