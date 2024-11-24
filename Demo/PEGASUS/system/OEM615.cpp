

// OEM615 GNSS RECEIVER


// Includes
#include "oem615.hpp"
#include "../CubeSim/part/box.hpp"


// Constructor
OEM615::OEM615(void) : GNSS(_SPATIAL_ACCURACY, _TEMPORAL_ACCURACY)
{
   // Make GNSS Receiver
   CubeSim::Part::Box gnss_receiver(0.071, 0.046, 0.00003);
   gnss_receiver.position(-gnss_receiver.length() / 2.0, -gnss_receiver.width() / 2.0, 0.0);
   gnss_receiver.material(CubeSim::Material::EPOXY);

   // Insert GNSS Receiver
   CubeSim::Assembly assembly;
   assembly.insert("GNSS Receiver", gnss_receiver);

   // Insert Assembly
   insert("Assembly", assembly);
}


// Spatial Accuracy [m]
const double OEM615::_SPATIAL_ACCURACY = 1.5;

// Temporal Accuracy [s]
const double OEM615::_TEMPORAL_ACCURACY = 20.0E-9;
