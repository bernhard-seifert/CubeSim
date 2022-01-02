

// CUBESIM - MATERIAL


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
#include "material.hpp"
#include "part.hpp"


// Default Materials
const CubeSim::Material CubeSim::Material::ALUMINUM("Aluminum", 2700.0, Color(173, 178, 189));
const CubeSim::Material CubeSim::Material::COPPER("Copper", 8900.0, Color(192, 105, 53));
const CubeSim::Material CubeSim::Material::EPOXY("Epoxy Resin", 1700.0, Color(80, 80, 80));
const CubeSim::Material CubeSim::Material::FR4("FR4", 2000.0, Color(40, 80, 0));
const CubeSim::Material CubeSim::Material::PEEK("PEEK", 1300.0, Color(140, 120, 70));
const CubeSim::Material CubeSim::Material::POLYAMIDE("Polyamide", 1150.0, Color(242, 242, 242));
const CubeSim::Material CubeSim::Material::PTFE("PTFE", 2160.0, Color(255, 255, 255));
const CubeSim::Material CubeSim::Material::STEEL("Steel", 7900.0, Color(224, 223, 219));


// Assign (Part is maintained)
CubeSim::Material& CubeSim::Material::operator =(const Material& material)
{
   // Check Material
   if (this != &material)
   {
      // Assign
      _density = material._density;
      _color = material._color;
      _name = material._name;
   }

   // Return Reference
   return *this;
}


// Set Density [kg/m^3]
void CubeSim::Material::density(double density)
{
   // Check Density
   if (density < 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Density
   _density = density;

   // Check for Part
   if (_part)
   {
      // Update Properties
      _part->_update(Part::_UPDATE_MATERIAL);
   }
}
