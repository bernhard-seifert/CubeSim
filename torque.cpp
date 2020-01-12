

// CUBESIM - TORQUE


// Includes
#include "rigid_body.hpp"


// Update Property
void CubeSim::Torque::_update(uint8_t update)
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
            _rigid_body->_update(RigidBody::_UPDATE_TORQUE);
         }

         // Break
         break;
      }
   }
}
