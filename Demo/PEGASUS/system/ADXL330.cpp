

// ADXL330 DIGITAL ACCELEROMETER


// Includes
#include "ADXL330.hpp"
#include "../CubeSim/part/box.hpp"


// Constructor
ADXL330::ADXL330(void) : Accelerometer(_ACCURACY, _RANGE, 0.1)
{
   // Make digital Accelerometer
   CubeSim::Part::Box digital_accelerometer(0.004, 0.004, 0.0011);
   digital_accelerometer.position(-digital_accelerometer.length() / 2.0, -digital_accelerometer.width() / 2.0, 0.0);
   digital_accelerometer.material(CubeSim::Material::EPOXY);

   // Insert digital Gyroscope
   CubeSim::Assembly assembly;
   assembly.insert("Digital Accelerometer", digital_accelerometer);

   // Insert Assembly
   insert("Assembly", assembly);

   // Set Part
   _part(*this->assembly("Assembly")->part("Digital Accelerometer"));
}


// Accuracy for 1g Range [m/s^2]
const double ADXL330::_ACCURACY = 0.03;

// Range [m/s^2]
const double ADXL330::_RANGE = 36.0;
