

// DEMO - PEGASUS


// Includes
#include "main.hpp"


// Clone
CubeSim::System* PegasusADCS::clone() const
{
   // Return Copy
   return new PegasusADCS(*this);
}


// Behavior
void PegasusADCS::_behavior(void)
{
   // Call ADCS Task
   ADCS::task();
}


// Initialize
void PegasusADCS::_init(void)
{
   // Get Earth and Spacecraft Objects
   CubeSim::CelestialBody& earth = *simulation()->celestial_body("Earth");
   CubeSim::Spacecraft& spacecraft = *simulation()->spacecraft("Spacecraft");

   // Compute Spacecraft Orbit: 400 km, 0.01 Eccentricity, 70° Inclination
   CubeSim::Orbit orbit(earth, (6370 + 400) * 1000, 0.01, 120 * CubeSim::Constant::PI / 180,
      50 * CubeSim::Constant::PI / 180, 70 * CubeSim::Constant::PI / 180, 20.0 * CubeSim::Constant::PI / 180,
      simulation()->time(), CubeSim::Orbit::REFERENCE_ECI);

   // Initialize Spacecraft Position, Velocity, Orientation, angular Rate
   spacecraft.position(earth.position() + orbit.position());
   spacecraft.velocity(earth.velocity() + orbit.velocity());
}


// Main
int main(void)
{
   // Pegasus ADCS System
   PegasusADCS adcs;

   // Insert six Visible Light Photo Diodes
   TEMD6200FX01 photo_diode;
   photo_diode.position(-0.05, 0.00, 0.00);
   photo_diode.rotation(CubeSim::Vector3D::Y, -CubeSim::Constant::PI / 2.0);
   adcs.insert("PhotoDiodeXM", photo_diode);
   photo_diode.position(0.05, 0.00, 0.00);
   photo_diode.rotation(CubeSim::Vector3D::Y, CubeSim::Constant::PI / 2.0);
   adcs.insert("PhotoDiodeXP", photo_diode);
   photo_diode.position(0.00, -0.05, 0.00);
   photo_diode.rotation(CubeSim::Vector3D::X, CubeSim::Constant::PI / 2.0);
   adcs.insert("PhotoDiodeYM", photo_diode);
   photo_diode.position(0.00, 0.05, 0.00);
   photo_diode.rotation(CubeSim::Vector3D::X, -CubeSim::Constant::PI / 2.0);
   adcs.insert("PhotoDiodeYP", photo_diode);
   photo_diode.position(0.00, 0.00, -0.10);
   photo_diode.rotation(CubeSim::Vector3D::X, CubeSim::Constant::PI);
   adcs.insert("PhotoDiodeZM", photo_diode);
   photo_diode.position(0.00, 0.00, 0.10);
   photo_diode.rotation(CubeSim::Rotation());
   adcs.insert("PhotoDiodeZP", photo_diode);

   // Insert Magnetometer
   HMC5983 magnetometer;
   adcs.insert("Magnetometer", magnetometer);

   // Insert Gyroscope
   L3G4200D gyroscope;
   adcs.insert("Gyroscope", gyroscope);

   // Insert Accelerometer
   ADXL330 accelerometer;
   adcs.insert("Accelerometer", accelerometer);

   // Insert GPS
   OEM615 gps;
   adcs.insert("GPS", gps);

   // Insert Sidepanel Magnetorquers
   SidepanelTorquer sidepanel_torquer;
   sidepanel_torquer.position(-0.05, 0.00, 0.00);
   sidepanel_torquer.rotation(CubeSim::Vector3D::Y, -CubeSim::Constant::PI / 2.0);
   adcs.insert("MagnetorquerXM", sidepanel_torquer);
   sidepanel_torquer.position(0.05, 0.00, 0.00);
   sidepanel_torquer.rotation(CubeSim::Vector3D::Y, CubeSim::Constant::PI / 2.0);
   adcs.insert("MagnetorquerXP", sidepanel_torquer);
   sidepanel_torquer.position(0.00, -0.05, 0.00);
   sidepanel_torquer.rotation(CubeSim::Vector3D::X, CubeSim::Constant::PI / 2.0);
   adcs.insert("MagnetorquerYM", sidepanel_torquer);
   sidepanel_torquer.position(0.00, 0.05, 0.00);
   sidepanel_torquer.rotation(CubeSim::Vector3D::X, -CubeSim::Constant::PI / 2.0);
   adcs.insert("MagnetorquerYP", sidepanel_torquer);

   // Insert Adapter Board Magnetorquer
   AdapterTorquer adapter_torquer;
   adapter_torquer.position(0.00, 0.00, 0.10);
   adapter_torquer.rotation(CubeSim::Rotation());
   adcs.insert("MagnetorquerZ", adapter_torquer);

   // Spacecraft Bus
   CubeSim::Part::Box bus_part(0.1, 0.1, 0.2);
   bus_part.material(CubeSim::Material("", 1000.0));
   CubeSim::Assembly bus_assembly;
   bus_assembly.insert("Bus", bus_part);
   adcs.insert("Bus", bus_assembly);

   // Monitor System
   Monitor monitor;

   // Interface System
   ADCS::Interface interface_;

   // Spacecraft
   CubeSim::Spacecraft spacecraft;
   spacecraft.position(1E9, 1E9, 1E9);
   spacecraft.insert("ADCS", adcs);
   spacecraft.insert("Monitor", monitor);
   spacecraft.insert("Interface", interface_);

   // Simulation
   CubeSim::Simulation simulation;
   simulation.insert("Spacecraft", spacecraft);
   CubeSim::CelestialBody& sun = simulation.insert("Sun", CubeSim::CelestialBody::Sun());
   CubeSim::CelestialBody& earth = simulation.insert("Earth", CubeSim::CelestialBody::Earth());
   simulation.insert("Moon", CubeSim::CelestialBody::Moon());
   simulation.insert("Mars", CubeSim::CelestialBody::Mars());
   simulation.insert("Ephemeris", CubeSim::Module::Ephemeris());
   simulation.insert("Motion", CubeSim::Module::Motion(1));
   simulation.insert("Gravitation", CubeSim::Module::Gravitation(1));
   simulation.insert("Magnetics", CubeSim::Module::Magnetics(earth));
   simulation.insert("Light", CubeSim::Module::Light());
   simulation.insert("Albedo", CubeSim::Module::Albedo(earth));

   // Set Simulation Time
   simulation.time(Time(2017, 6, 23));

   // Run Simulation
   simulation.run(3600 * 24 * 365);

   // Return
   return 0;
}
