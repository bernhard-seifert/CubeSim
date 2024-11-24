

// SIDEPANEL MAGNETORQUER


// Includes
#include "sidepanel_torquer.hpp"
#include "../CubeSim/part/box.hpp"


// Constructor
SidepanelTorquer::SidepanelTorquer(void) : Magnetorquer(_AREA, _RANGE, _ACCURACY, _TIME_STEP)
{
   // Make Coil
   CubeSim::Part::Box coil(0.21, 0.07, 0.00007);
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
const double SidepanelTorquer::_ACCURACY = 0.001;

// Effective Coil Area [m^2]
const double SidepanelTorquer::_AREA = 0.64;

// Range [A]
const double SidepanelTorquer::_RANGE = 0.08;

// Time Step [s]
const double SidepanelTorquer::_TIME_STEP = 0.1;
