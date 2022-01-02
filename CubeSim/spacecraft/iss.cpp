

// CUBESIM - SPACECRAFT - ISS


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
