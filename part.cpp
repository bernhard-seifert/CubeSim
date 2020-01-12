

// CUBESIM - PART


// Includes
#include "part.hpp"


// Update Property
void CubeSim::Part::_update(uint8_t update)
{
   // Check Update Property
   switch (update)
   {
      // Dimension
      case _UPDATE_DIMENSION:
      {
         // Update Properties (Update of Volume updates Mass automatically)
         RigidBody::_update(RigidBody::_UPDATE_AREA);
         RigidBody::_update(RigidBody::_UPDATE_VOLUME);
         break;
      }
   }
}
