

// CUBESIM - SPACECRAFT - HUBBLE


// Includes
#include "hubble.hpp"
#include "../part/cylinder.hpp"


// Class _System
class CubeSim::Spacecraft::Hubble::_System : public System
{
private:

   // Clone
   virtual System* clone() const;
};


// Constructor
CubeSim::Spacecraft::Hubble::Hubble(void) : Spacecraft(Vector3D(-2.518433226E+10, 1.447314179E+11, -2.964402043E+07),
   Vector3D(-3.640777002E+04, -7.406909538E+03, 3.084020937E+03))
{
   // Spacecraft Bus
   Part::Cylinder bus(4.2, 13.2);
   bus.material(Material("", 60.75));

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
inline CubeSim::System* CubeSim::Spacecraft::Hubble::_System::clone() const
{
   // Return Copy
   return new _System(*this);
}
