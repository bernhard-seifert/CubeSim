

// CUBESIM - PART


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
#include "part.hpp"


// Assign
CubeSim::Part& CubeSim::Part::operator =(const Part& part)
{
   // Check Part
   if (this != &part)
   {
      // Assign
      static_cast<RigidBody&>(*this) = part;
      static_cast<List<Part>::Item&>(*this) = part;

      // Set Material and Part
      _material = part._material;
      _material._part = this;
   }

   // Return Reference
   return *this;
}


// Update Properties
const uint8_t CubeSim::Part::_UPDATE_DIMENSION;
const uint8_t CubeSim::Part::_UPDATE_MATERIAL;


// Update Property
void CubeSim::Part::_update(uint8_t update)
{
   // Check Update Property
   switch (update)
   {
      // Dimension
      case _UPDATE_DIMENSION:
      {
         // Update Properties
         RigidBody::_update(RigidBody::_UPDATE_AREA);
         RigidBody::_update(RigidBody::_UPDATE_CENTER);
         RigidBody::_update(RigidBody::_UPDATE_INERTIA);
         RigidBody::_update(RigidBody::_UPDATE_VOLUME);
         break;
      }

      // Material
      case _UPDATE_MATERIAL:
      {
         // Update Property
         RigidBody::_update(RigidBody::_UPDATE_MASS);
         break;
      }
   }
}
