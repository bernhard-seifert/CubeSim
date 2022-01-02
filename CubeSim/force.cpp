

// CUBESIM - FORCE


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
