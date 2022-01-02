

// CUBESIM - PART


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
