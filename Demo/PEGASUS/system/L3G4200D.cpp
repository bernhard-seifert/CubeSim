

// L3G4200D DIGITAL GYROSCOPE


// Includes
#include "l3g4200d.hpp"
#include "../CubeSim/part/box.hpp"


// Constructor
L3G4200D::L3G4200D(void) : Gyroscope(_ACCURACY, _RANGE)
{
   // Make digital Gyroscope
   CubeSim::Part::Box digital_gyroscope(0.004, 0.004, 0.0011);
   digital_gyroscope.position(-digital_gyroscope.length() / 2.0, -digital_gyroscope.width() / 2.0, 0.0);
   digital_gyroscope.material(CubeSim::Material::EPOXY);

   // Insert digital Gyroscope
   CubeSim::Assembly assembly;
   assembly.insert("Digital Gyroscope", digital_gyroscope);

   // Insert Assembly
   insert("Assembly", assembly);

   // Set Part
   _part(*this->assembly("Assembly")->part("Digital Gyroscope"));
}


// Accuracy [rad/s]
const double L3G4200D::_ACCURACY = 0.0005;

// Range [rad/s]
const double L3G4200D::_RANGE = 4.36;
