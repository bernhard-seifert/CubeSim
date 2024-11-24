

// HMC5983 DIGITAL COMPASS


// Includes
#include "hmc5983.hpp"
#include "../CubeSim/part/box.hpp"


// Constructor
HMC5983::HMC5983(void) : Magnetometer(_ACCURACY, _RANGE)
{
   // Make digital Compass
   CubeSim::Part::Box digital_compass(0.003, 0.003, 0.0009);
   digital_compass.position(-digital_compass.length() / 2.0, -digital_compass.width() / 2.0, 0.0);
   digital_compass.material(CubeSim::Material::EPOXY);

   // Insert digital Compass
   CubeSim::Assembly assembly;
   assembly.insert("Digital Compass", digital_compass);

   // Insert Assembly
   insert("Assembly", assembly);

   // Set Part
   _part(*this->assembly("Assembly")->part("Digital Compass"));
}


// Accuracy [T]
const double HMC5983::_ACCURACY = 2.0E-7;

// Range [T]
const double HMC5983::_RANGE = 8.8E-5;
