

// CUBESIM - FORCE


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
#include "force.hpp"
#include "rigid_body.hpp"


// Assign (Rigid Body Reference is maintained)
CubeSim::Force& CubeSim::Force::operator =(const Force& force)
{
   // Check Force
   if (this != &force)
   {
      // Assign
      static_cast<Vector3D&>(*this) = force;
      _point = force._point;

      // Update Property
      _update(_UPDATE_MAGNITUDE);
   }

   // Return Reference
   return *this;
}


// Update Properties
const uint8_t CubeSim::Force::_UPDATE_MAGNITUDE;
const uint8_t CubeSim::Force::_UPDATE_POINT;


// Update Property
void CubeSim::Force::_update(uint8_t update)
{
   // Check Update Property
   switch (update)
   {
      // Magnitude
      case _UPDATE_MAGNITUDE:
      {
         // Check Parent Rigid Body
         if (_rigid_body)
         {
            // Update Property
            _rigid_body->_update(RigidBody::_UPDATE_FORCE);
         }

         // Break
         break;
      }

      // Point of Application
      case _UPDATE_POINT:
      {
         // Check Parent Rigid Body
         if (_rigid_body)
         {
            // Update Property
            _rigid_body->_update(RigidBody::_UPDATE_FORCE);
         }

         // Break
         break;
      }
   }
}
