

// INTERFACE


// Includes
#include "interface.hpp"
#include "../CubeSim/system/gnss.hpp"
#include "../CubeSim/system/gyroscope.hpp"
#include "../CubeSim/system/magnetometer.hpp"
#include "../CubeSim/system/magnetorquer.hpp"
#include "../CubeSim/system/photodetector.hpp"
#include "../ADCS/constant.hpp"


// Set Magnetorquer Current [A]
void ADCS::Interface::magnetorquer(uint8_t side, const ADCS::numeric_t& current)
{
   // Get ADCS System
   static CubeSim::System& adcs = *_simulation->spacecraft("Spacecraft")->system("ADCS");

   // Get Magnetorquer Systems
   static CubeSim::System::Magnetorquer& magnetorquer_xm = *dynamic_cast<CubeSim::System::Magnetorquer*>(
      adcs.system("MagnetorquerXM"));
   static CubeSim::System::Magnetorquer& magnetorquer_xp = *dynamic_cast<CubeSim::System::Magnetorquer*>(
      adcs.system("MagnetorquerXP"));
   static CubeSim::System::Magnetorquer& magnetorquer_ym = *dynamic_cast<CubeSim::System::Magnetorquer*>(
      adcs.system("MagnetorquerYM"));
   static CubeSim::System::Magnetorquer& magnetorquer_yp = *dynamic_cast<CubeSim::System::Magnetorquer*>(
      adcs.system("MagnetorquerYP"));
   static CubeSim::System::Magnetorquer& magnetorquer_z = *dynamic_cast<CubeSim::System::Magnetorquer*>(
      adcs.system("MagnetorquerZ"));

   // Current List
   static ADCS::numeric_t _current[6] = { NUM(0.0) };

   // Update Current
   _current[side] = current;

   // Set Magnetorquer Currents
   magnetorquer_xm.current(_current[SIDE_XM]);
   magnetorquer_xp.current(_current[SIDE_XP]);
   magnetorquer_ym.current(_current[SIDE_YM]);
   magnetorquer_yp.current(_current[SIDE_YP]);
   magnetorquer_z.current(_current[SIDE_ZP]);
}


// CubeSim-ADCS Conversions
inline const ADCS::Vector ADCS::Interface::_convert(const CubeSim::Vector3D& vector)
{
   // Return ADCS Vector
   return ADCS::Vector(NUM(vector.x()), NUM(vector.y()), NUM(vector.z()));
}


// Behavior
void ADCS::Interface::_behavior(void)
{
   // Get ADCS System
   CubeSim::System& adcs = *_simulation->spacecraft("Spacecraft")->system("ADCS");

   // Get GPS System
   CubeSim::System::GNSS& gps = *dynamic_cast<CubeSim::System::GNSS*>(adcs.system("GPS"));

   // Get Gyroscope System
   CubeSim::System::Gyroscope& gyroscope = *dynamic_cast<CubeSim::System::Gyroscope*>(adcs.system("Gyroscope"));

   // Get Magnetometer System
   CubeSim::System::Magnetometer& magnetometer = *dynamic_cast<CubeSim::System::Magnetometer*>(
      adcs.system("Magnetometer"));

   // Get Magnetorquer Systems
   CubeSim::System::Magnetorquer& magnetorquer_xm = *dynamic_cast<CubeSim::System::Magnetorquer*>(
      adcs.system("MagnetorquerXM"));
   CubeSim::System::Magnetorquer& magnetorquer_xp = *dynamic_cast<CubeSim::System::Magnetorquer*>(
      adcs.system("MagnetorquerXP"));
   CubeSim::System::Magnetorquer& magnetorquer_ym = *dynamic_cast<CubeSim::System::Magnetorquer*>(
      adcs.system("MagnetorquerYM"));
   CubeSim::System::Magnetorquer& magnetorquer_yp = *dynamic_cast<CubeSim::System::Magnetorquer*>(
      adcs.system("MagnetorquerYP"));
   CubeSim::System::Magnetorquer& magnetorquer_z = *dynamic_cast<CubeSim::System::Magnetorquer*>(
      adcs.system("MagnetorquerZ"));

   // Get Photo Diode Systems
   CubeSim::System::Photodetector& photo_diode_xm = *dynamic_cast<CubeSim::System::Photodetector*>(
      adcs.system("PhotoDiodeXM"));
   CubeSim::System::Photodetector& photo_diode_xp = *dynamic_cast<CubeSim::System::Photodetector*>(
      adcs.system("PhotoDiodeXP"));
   CubeSim::System::Photodetector& photo_diode_ym = *dynamic_cast<CubeSim::System::Photodetector*>(
      adcs.system("PhotoDiodeYM"));
   CubeSim::System::Photodetector& photo_diode_yp = *dynamic_cast<CubeSim::System::Photodetector*>(
      adcs.system("PhotoDiodeYP"));
   CubeSim::System::Photodetector& photo_diode_zm = *dynamic_cast<CubeSim::System::Photodetector*>(
      adcs.system("PhotoDiodeZM"));
   CubeSim::System::Photodetector& photo_diode_zp = *dynamic_cast<CubeSim::System::Photodetector*>(
      adcs.system("PhotoDiodeZP"));

   // Photo Diode effective Area
   double photo_diode_area = 0.27E-6;

   // Delay
   _simulation->delay(ADCS::Constant::UPDATE_INTERVAL - _DELAY);

   // Loop
   for (;;)
   {
      // Get GPS Location
      CubeSim::Location location = gps.location();

      // Set GPS Location
      _location = Location(NUM(location.latitude()), NUM(location.longitude()), NUM(location.altitude()),
         (location.time() - _epoch) / 1000.0);

      // Measure angular Rate
      _angular_rate = _convert(gyroscope.angular_rate());

      // Measure magnetic Field
      _magnetic_field = _convert(magnetometer.magnetic_field());

      // Measure Irradiance
      _irradiance[SIDE_XM] = NUM(photo_diode_xm.radiant_flux() / photo_diode_area);
      _irradiance[SIDE_XP] = NUM(photo_diode_xp.radiant_flux() / photo_diode_area);
      _irradiance[SIDE_YM] = NUM(photo_diode_ym.radiant_flux() / photo_diode_area);
      _irradiance[SIDE_YP] = NUM(photo_diode_yp.radiant_flux() / photo_diode_area);
      _irradiance[SIDE_ZM] = NUM(photo_diode_zm.radiant_flux() / photo_diode_area);
      _irradiance[SIDE_ZP] = NUM(photo_diode_zp.radiant_flux() / photo_diode_area);

      // Delay
      _simulation->delay(ADCS::Constant::UPDATE_INTERVAL);
   }
}


// Initialize
void ADCS::Interface::_init(void)
{
   // Get Simulation
   _simulation = simulation();
}


// Default Measurement Delay [s]
const double ADCS::Interface::_DELAY = 0.001;


// Variables
ADCS::numeric_t ADCS::Interface::_irradiance[];
ADCS::Vector ADCS::Interface::_angular_rate;
ADCS::Vector ADCS::Interface::_magnetic_field;
ADCS::Location ADCS::Interface::_location;
CubeSim::Time ADCS::Interface::_epoch = Time(2000, 1, 1);
CubeSim::Simulation* ADCS::Interface::_simulation;
