

// TEMD6200FX01 VISIBLE LIGHT PHOTO DIODE


// Includes
#include "TEMD6200FX01.hpp"
#include "../CubeSim/part/box.hpp"


// Constructor
TEMD6200FX01::TEMD6200FX01(void) : Photodetector(_AREA, _ANGLE, _ACCURACY, _RANGE)
{
   // Make Photo Diode
   CubeSim::Part::Box photo_diode(0.002, 0.00125, 0.00085);
   photo_diode.material(CubeSim::Material::POLYAMIDE);

   // Insert Photo Diode
   CubeSim::Assembly assembly;
   assembly.insert("Photo Diode", photo_diode);

   // Insert Assembly
   insert("Assembly", assembly);

   // Set Part
   _part(*this->assembly("Assembly")->part("Photo Diode"));
}


// Accuracy [W/m^2]
const double TEMD6200FX01::_ACCURACY = 20.0;

// Opening Angle [rad]
const double TEMD6200FX01::_ANGLE = CubeSim::Constant::PI;

// Area [m^2]
const double TEMD6200FX01::_AREA = 0.27E-6;

// Range [W/m^2]
const double TEMD6200FX01::_RANGE = 1400.0;
