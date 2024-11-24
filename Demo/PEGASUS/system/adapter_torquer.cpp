

// ADAPTER BOARD MAGNETORQUER


// Includes
#include "adapter_torquer.hpp"
#include "../CubeSim/part/box.hpp"


// Constructor
AdapterTorquer::AdapterTorquer(void) : Magnetorquer(_AREA, _RANGE, _ACCURACY, _TIME_STEP)
{
   // Make Coil
   CubeSim::Part::Box coil(0.08, 0.08, 0.00007);
   coil.position(-coil.length() / 2.0, -coil.width() / 2.0, 0.0);
   coil.material(CubeSim::Material::COPPER);

   // Insert Coil
   CubeSim::Assembly assembly;
   assembly.insert("Coil", coil);

   // Insert Assembly
   insert("Assembly", assembly);

   // Set Part
   _part(*this->assembly("Assembly")->part("Coil"));
}


// Accuracy [A]
const double AdapterTorquer::_ACCURACY = 0.001;

// Effective Coil Area [m^2]
const double AdapterTorquer::_AREA = 0.38;

// Range [A]
const double AdapterTorquer::_RANGE = 0.08;

// Time Step [s]
const double AdapterTorquer::_TIME_STEP = 0.1;
