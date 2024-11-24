

// MONITOR


// Includes
#include <conio.h>
#include "monitor.hpp"
#include "../CubeSim/simulation.hpp"
#include "../CubeSim/system/accelerometer.hpp"
#include "../CubeSim/system/gnss.hpp"
#include "../CubeSim/system/gyroscope.hpp"
#include "../ADCS/magnetics.hpp"
#include "../ADCS/operation.hpp"
#include "../ADCS/spacecraft.hpp"
#include "../ADCS/sun.hpp"


// Behavior
void Monitor::_behavior(void)
{
   // Get Epoch
   Time epoch = Time(2000, 1, 1);

   // Get ADCS, GPS, Gyroscope, Accelerometer Systems
   CubeSim::System& adcs = *_spacecraft().system("ADCS");
   CubeSim::System::GNSS& gps = *dynamic_cast<CubeSim::System::GNSS*>(adcs.system("GPS"));
   CubeSim::System::Gyroscope& gyroscope = *dynamic_cast<CubeSim::System::Gyroscope*>(adcs.system("Gyroscope"));
   CubeSim::System::Accelerometer& accelerometer =
      *dynamic_cast<CubeSim::System::Accelerometer*>(adcs.system("Accelerometer"));
   CubeSim::CelestialBody& earth = *simulation()->celestial_body("Earth");

   // Get Start Time
   Time start = simulation()->time();

   // Loop
   for (;;)
   {
      try
      {
         // Get ADCS Information
         auto& info = ADCS::Operation::info();

         // Get Simulation Time
         Time sim_time = simulation()->time();

         // Time Header
         uint8_t y = 0;
         _print(0, y++, "TIME            ABS            REL                     DATE                               ", 0,
            Console::COLOR_WHITE, Console::COLOR_BLUE);

         // Simulation Time
         _print(0, y, "SIM                                                                                         ");
         _print(5, y, "%14.3f", (sim_time - epoch) / 1000.0);
         _print(20, y, "%14.3f", (sim_time - start) / 1000.0);
         _print(36, y, "%04.0f-", sim_time.year());
         _print(41, y, "%02.0f-", sim_time.month());
         _print(44, y, "%02.0f ", sim_time.day());
         _print(47, y, "%02.0f:", sim_time.hour());
         _print(50, y, "%02.0f:", sim_time.minute());
         _print(53, y, "%02.0f.", sim_time.second());
         _print(56, y++, "%03.0f", sim_time.milli());
         ++y;

         // Position Header
         _print(0, y, "POS      LONG      LAT       ALT     ECEF X     ECEF Y     ECEF Z       DIST  GPS         ", 0,
            Console::COLOR_WHITE, Console::COLOR_BLUE);
         _print(78, y++, "G", 0, Console::COLOR_RED, Console::COLOR_BLUE);

         // Get GPS Status
         bool enabled = gps.is_enabled();

         // Enable GPS
         gps.enable();

         // Get GPS Location and Position
         CubeSim::Location sim_location = gps.location();
         CubeSim::Vector3D sim_position = sim_location.point();

         // Check GPS Status
         if (!enabled)
         {
            // Disable GPS
            gps.disable();
         }

         // Simulation Position
         _print(0, y, "SIM                                                                                       ");
         _print(6, y, "%+6.1f\xF8", sim_location.longitude() * 180.0 / CubeSim::Constant::PI);
         _print(15, y, "%+6.1f\xF8", sim_location.latitude() * 180.0 / CubeSim::Constant::PI);
         _print(24, y, "%6.1fkm", sim_location.altitude() / 1000.0);
         _print(34, y, "%+7.1fkm", sim_position.x() / 1000.0);
         _print(45, y, "%+7.1fkm", sim_position.y() / 1000.0);
         _print(56, y, "%+7.1fkm", sim_position.z() / 1000.0);
         _print(67, y, "%7.1fkm", sim_position.norm() / 1000.0);
         _print(79, y++, gps.is_enabled() ? "ON" : "OFF", 0, gps.is_enabled() ? Console::COLOR_LIGHT_GREEN :
            Console::COLOR_LIGHT_RED);

         // Get Spacecraft Location and Position
         ADCS::Location adcs_location = ADCS::Spacecraft::location();
         ADCS::Vector adcs_position = adcs_location.point();

         // ADCS Position
         _print(0, y, "ADCS                                                                                      ");
         _print(6, y, "%+6.1f\xF8", adcs_location.longitude() * 180.0 / CubeSim::Constant::PI);
         _print(15, y, "%+6.1f\xF8", adcs_location.latitude() * 180.0 / CubeSim::Constant::PI);
         _print(24, y, "%6.1fkm", adcs_location.altitude() / 1000.0);
         _print(34, y, "%+7.1fkm", adcs_position.x() / 1000.0);
         _print(45, y, "%+7.1fkm", adcs_position.y() / 1000.0);
         _print(56, y, "%+7.1fkm", adcs_position.z() / 1000.0);
         _print(67, y++, "%7.1fkm", adcs_position.norm() / 1000.0);

         // Position Difference
         _print(0, y, "DIFF                                                                            ");
         double diff = (adcs_location.longitude() - sim_location.longitude()) * 180.0 / CubeSim::Constant::PI;
         _print(6, y, "%+6.1f\xF8", diff, (fabs(diff) <= 0.1) ? Console::COLOR_LIGHT_GREEN : Console::COLOR_LIGHT_RED);
         diff = (adcs_location.latitude() - sim_location.latitude()) * 180.0 / CubeSim::Constant::PI;
         _print(15, y, "%+6.1f\xF8", diff, (fabs(diff) <= 0.1) ? Console::COLOR_LIGHT_GREEN : Console::COLOR_LIGHT_RED);
         diff = (adcs_location.altitude() - sim_location.altitude()) / 1000.0;
         _print(24, y, "%+6.1fkm", diff, (fabs(diff) <= 10.0) ? Console::COLOR_LIGHT_GREEN : Console::COLOR_LIGHT_RED);
         diff = (adcs_position.x() - sim_position.x()) / 1000.0;
         _print(34, y, "%+7.1fkm", diff, (fabs(diff) <= 10.0) ? Console::COLOR_LIGHT_GREEN : Console::COLOR_LIGHT_RED);
         diff = (adcs_position.y() - sim_position.y()) / 1000.0;
         _print(45, y, "%+7.1fkm", diff, (fabs(diff) <= 10.0) ? Console::COLOR_LIGHT_GREEN : Console::COLOR_LIGHT_RED);
         diff = (adcs_position.z() - sim_position.z()) / 1000.0;
         _print(56, y, "%+7.1fkm", diff, (fabs(diff) <= 10.0) ? Console::COLOR_LIGHT_GREEN : Console::COLOR_LIGHT_RED);
         diff = std::sqrt(std::pow(sim_position.x() - adcs_position.x(), 2.0) + std::pow(sim_position.y() -
            adcs_position.y(), 2.0) + std::pow(sim_position.z() - adcs_position.z(), 2.0)) / 1000.0;
         _print(67, y++, "%+7.1fkm", diff, (fabs(diff) <= 10.0) ? Console::COLOR_LIGHT_GREEN : Console::COLOR_LIGHT_RED);
         ++y;

         // Get Orbit
         CubeSim::Orbit sim_orbit = _spacecraft().orbit(_earth(), CubeSim::Orbit::REFERENCE_ECI);
         ADCS::Orbit adcs_orbit = ADCS::Spacecraft::orbit();

         // Orbit Header
         _print(0, y++, "ORBIT  SEMIAXIS    ECC  ARG-PERIAP  LONG-ASC  INCLIN  MEAN-ANOM   PERIOD                  ", 0,
            Console::COLOR_WHITE, Console::COLOR_BLUE);

         // Simulation Orbit
         _print(0, y, "SIM                                                                                       ");
         _print(7, y, "%6.1fkm", sim_orbit.semimajor_axis() / 1000.0);
         _print(17, y, "%5.3f", sim_orbit.eccentricity());
         _print(28, y, "%5.1f\xF8", sim_orbit.argument_periapsis() * 180.0 / CubeSim::Constant::PI);
         _print(38, y, "%5.1f\xF8", sim_orbit.longitude_ascending() * 180.0 / CubeSim::Constant::PI);
         _print(46, y, "%5.1f\xF8", sim_orbit.inclination() * 180.0 / CubeSim::Constant::PI);
         _print(57, y, "%5.1f\xF8", sim_orbit.mean_anomaly() * 180.0 / CubeSim::Constant::PI);
         _print(65, y++, "%6.1fs", sim_orbit.period());

         // ADCS Orbit
         _print(0, y, "ADCS                                                                                      ");
         _print(7, y, "%6.1fkm", adcs_orbit.semimajor_axis() / 1000.0);
         _print(17, y, "%5.3f", adcs_orbit.eccentricity());
         _print(28, y, "%5.1f\xF8", adcs_orbit.argument_periapsis() * 180.0 / CubeSim::Constant::PI);
         _print(38, y, "%5.1f\xF8", adcs_orbit.longitude_ascending() * 180.0 / CubeSim::Constant::PI);
         _print(46, y, "%5.1f\xF8", adcs_orbit.inclination() * 180.0 / CubeSim::Constant::PI);
         _print(57, y, "%5.1f\xF8", adcs_orbit.mean_anomaly() * 180.0 / CubeSim::Constant::PI);
         _print(65, y++, "%6.1fs", adcs_orbit.period());
         ++y;

         // Rotation Header
         _print(0, y++, "ROT   LO ROLL    PITCH      YAW  B RATE ROLL      PITCH        YAW      TOTAL             ", 0,
            Console::COLOR_WHITE, Console::COLOR_BLUE);

         // Compute Spacecraft Rotation (LO Frame) and angular Rate (Body Frame)
         CubeSim::Rotation sim_rotation = _spacecraft().rotation() - _LO();
         CubeSim::Vector3D sim_angular_rate = _spacecraft().angular_rate() - _spacecraft().rotation();

         // Simulation Rotation
         _print(0, y, "SIM                                                                                       ");
         _print(6, y, "%+6.1f\xF8", sim_rotation.roll() * 180.0 / CubeSim::Constant::PI);
         _print(15, y, "%+6.1f\xF8", sim_rotation.pitch() * 180.0 / CubeSim::Constant::PI);
         _print(24, y, "%+6.1f\xF8", sim_rotation.yaw() * 180.0 / CubeSim::Constant::PI);
         _print(35, y, "%+6.2f\xF8/s", sim_angular_rate.x() * 180.0 / CubeSim::Constant::PI);
         _print(46, y, "%+6.2f\xF8/s", sim_angular_rate.y() * 180.0 / CubeSim::Constant::PI);
         _print(57, y, "%+6.2f\xF8/s", sim_angular_rate.z() * 180.0 / CubeSim::Constant::PI);
         _print(68, y++, "%+6.2f\xF8/s", sim_angular_rate.norm() * 180.0 / CubeSim::Constant::PI);

         // ADCS Rotation
         _print(0, y, "ADCS                                                                                      ");
         _print(6, y, "%+6.1f\xF8", ADCS::Spacecraft::orientation().roll() * 180.0 / CubeSim::Constant::PI);
         _print(15, y, "%+6.1f\xF8", ADCS::Spacecraft::orientation().pitch() * 180.0 / CubeSim::Constant::PI);
         _print(24, y, "%+6.1f\xF8", ADCS::Spacecraft::orientation().yaw() * 180.0 / CubeSim::Constant::PI);
         _print(35, y, "%+6.2f\xF8/s", ADCS::Spacecraft::angular_rate().x() * 180.0 / CubeSim::Constant::PI);
         _print(46, y, "%+6.2f\xF8/s", ADCS::Spacecraft::angular_rate().y() * 180.0 / CubeSim::Constant::PI);
         _print(57, y, "%+6.2f\xF8/s", ADCS::Spacecraft::angular_rate().z() * 180.0 / CubeSim::Constant::PI);
         _print(68, y++, "%+6.2f\xF8/s", ADCS::Spacecraft::angular_rate().norm() * 180.0 / CubeSim::Constant::PI);

         // Rotation Difference
         _print(0, y, "DIFF                                                                                      ");
         diff = (ADCS::Spacecraft::orientation().roll() - sim_rotation.roll()) * 180.0 / CubeSim::Constant::PI;
         _print(6, y, "%+6.1f\xF8", diff, (fabs(diff) <= 10.0) ? Console::COLOR_LIGHT_GREEN : Console::COLOR_LIGHT_RED);
         diff = (ADCS::Spacecraft::orientation().pitch() - sim_rotation.pitch()) * 180.0 / CubeSim::Constant::PI;
         _print(15, y, "%+6.1f\xF8", diff, (fabs(diff) <= 10.0) ? Console::COLOR_LIGHT_GREEN :
            Console::COLOR_LIGHT_RED);
         diff = (ADCS::Spacecraft::orientation().yaw() - sim_rotation.yaw()) * 180.0 / CubeSim::Constant::PI;
         _print(24, y, "%+6.1f\xF8", diff, (fabs(diff) <= 10.0) ? Console::COLOR_LIGHT_GREEN :
            Console::COLOR_LIGHT_RED);
         diff = (ADCS::Spacecraft::angular_rate().x() - sim_angular_rate.x()) * 180.0 / CubeSim::Constant::PI;
         _print(35, y, "%+6.2f\xF8/s", diff, (fabs(diff) <= 1.0) ? Console::COLOR_LIGHT_GREEN :
            Console::COLOR_LIGHT_RED);
         diff = (ADCS::Spacecraft::angular_rate().y() - sim_angular_rate.y()) * 180.0 / CubeSim::Constant::PI;
         _print(46, y, "%+6.2f\xF8/s", diff, (fabs(diff) <= 1.0) ? Console::COLOR_LIGHT_GREEN :
            Console::COLOR_LIGHT_RED);
         diff = (ADCS::Spacecraft::angular_rate().z() - sim_angular_rate.z()) * 180.0 / CubeSim::Constant::PI;
         _print(57, y++, "%+6.2f\xF8/s", diff, (fabs(diff) <= 1.0) ? Console::COLOR_LIGHT_GREEN :
            Console::COLOR_LIGHT_RED);
         ++y;

         // Photo Diodes Header
         _print(0, y, "PHOTO       X-        X+        Y-        Y+        Z-        Z+     TOTAL    ALBEDO      ", 0,
            Console::COLOR_WHITE, Console::COLOR_BLUE);
         _print(0, y++, "P", 0, Console::COLOR_RED, Console::COLOR_BLUE);

         // Compute total Irradiance
         float irrandiance = sqrt(pow(ADCS::Interface::irradiance(ADCS::Interface::SIDE_XM), 2) +
            pow(ADCS::Interface::irradiance(ADCS::Interface::SIDE_XP), 2) +
            pow(ADCS::Interface::irradiance(ADCS::Interface::SIDE_YM), 2) +
            pow(ADCS::Interface::irradiance(ADCS::Interface::SIDE_YP), 2) +
            pow(ADCS::Interface::irradiance(ADCS::Interface::SIDE_ZM), 2) +
            pow(ADCS::Interface::irradiance(ADCS::Interface::SIDE_ZP), 2));

         // Simulation Photo Diodes
         _print(0, y, "ADCS                                                                                      ");
         _print(6, y, "%4.0fW/m2", ADCS::Interface::irradiance(ADCS::Interface::SIDE_XM));
         _print(16, y, "%4.0fW/m2", ADCS::Interface::irradiance(ADCS::Interface::SIDE_XP));
         _print(26, y, "%4.0fW/m2", ADCS::Interface::irradiance(ADCS::Interface::SIDE_YM));
         _print(36, y, "%4.0fW/m2", ADCS::Interface::irradiance(ADCS::Interface::SIDE_YP));
         _print(46, y, "%4.0fW/m2", ADCS::Interface::irradiance(ADCS::Interface::SIDE_ZM));
         _print(56, y, "%4.0fW/m2", ADCS::Interface::irradiance(ADCS::Interface::SIDE_ZP));
         _print(66, y, "%4.0fW/m2", irrandiance);
         _print(76, y++, "%4.0fW/m2", ADCS::Sun::albedo());
         ++y;

         // Magnetorquer
         _print(0, y++, "MAGNETORQUER          X          Y          Z                                             ", 0,
            Console::COLOR_WHITE, Console::COLOR_BLUE);

         // ADCS Magnetorquer
         _print(0, y, "ADCS                                                                                      ");
         _print(14, y, "%6.2fmAm2", ADCS::Magnetics::moment().x() * 1000.0);
         _print(25, y, "%6.2fmAm2", ADCS::Magnetics::moment().y() * 1000.0);
         _print(36, y++, "%6.2fmAm2", ADCS::Magnetics::moment().z() * 1000.0);
         ++y;

         // Information
         _print(0, y++, "INFO  STATUS   ECLIPSE  ROTATION   ANG.RATE                                               ", 0,
            Console::COLOR_WHITE, Console::COLOR_BLUE);

         // ADCS Information
         _print(0, y, "ADCS                                                                                      ");
         _print(6, y, (info.status == ADCS::Operation::STATUS_DISABLED) ? "DISABLE" : ((info.status ==
            ADCS::Operation::STATUS_CONTROL ? "CONTROL" : "DETUMB")), 0);
         _print(15, y, (info.eclipse == ADCS::Info::ECLIPSE_UNKNOWN) ? "UNKNOWN" : ((info.eclipse ==
            ADCS::Info::ECLIPSE_INSIDE) ? "INSIDE" : "OUTSIDE"), 0, (info.eclipse == ADCS::Info::ECLIPSE_UNKNOWN) ?
            Console::COLOR_LIGHT_RED : Console::COLOR_LIGHT_GREEN);
         _print(24, y, (info.rotation_mode == ADCS::Info::ROTATION_MODE_DIRECT) ? "DIRECT" : "PROPAGATE", 0);
         _print(35, y++, (info.angular_rate_mode == ADCS::Info::ANGULAR_RATE_MODE_GYRO) ? "GYRO" : "MATRIX", 0);
         ++y;

         // Check for Key
         if (_kbhit())
         {
            // Check Key
            switch (tolower(_getch()))
            {
               // Photo Diodes
               case 'p':
               {
                  // Check Photo Diode Status
                  if (adcs.system("PhotoDiodeXM")->is_enabled())
                  {
                     // Disable Photo Diodes
                     adcs.system("PhotoDiodeXM")->disable();
                     adcs.system("PhotoDiodeXP")->disable();
                     adcs.system("PhotoDiodeYM")->disable();
                     adcs.system("PhotoDiodeYP")->disable();
                     adcs.system("PhotoDiodeZM")->disable();
                     adcs.system("PhotoDiodeZP")->disable();
                  }
                  else
                  {
                     // Enable Photo Diodes
                     adcs.system("PhotoDiodeXM")->enable();
                     adcs.system("PhotoDiodeXP")->enable();
                     adcs.system("PhotoDiodeYM")->enable();
                     adcs.system("PhotoDiodeYP")->enable();
                     adcs.system("PhotoDiodeZM")->enable();
                     adcs.system("PhotoDiodeZP")->enable();
                  }

                  // Break
                  break;
               }

               // GPS
               case 'g':
               {
                  // Check GPS Status
                  if (adcs.system("GPS")->is_enabled())
                  {
                     // Disable GPS
                     adcs.system("GPS")->disable();
                  }
                  else
                  {
                     // Enable GPS
                     adcs.system("GPS")->enable();
                  }

                  // Break
                  break;
               }

               // Pause
               case ' ':
               {
                  // Wait for Key
                  _getch();

                  // Break
                  break;
               }
            }
         }
      }
      catch (...)
      {

      }

      // Delay
      simulation()->delay(1);
   }
}


// Compute ECI Frame
const CubeSim::Rotation& Monitor::_ECI(void) const
{
   // ECI Frame
   static CubeSim::Rotation* ECI;

   // Check ECI Frame
   if (!ECI)
   {
      // Compute Base Vectors
      auto b3 = _earth().rotation().matrix() * CubeSim::Vector3D::Z;
      auto b1 = b3 ^ CubeSim::Vector3D::Z;
      auto b2 = b3 ^ b1;

      // Compute ECI Frame
      ECI = new CubeSim::Rotation(b1, b2, b3);
   }

   // Return ECI Frame
   return *ECI;
}


// Compute LO Frame
const CubeSim::Rotation Monitor::_LO(void) const
{
   // Compute Spacecraft Position and Velocity (ECI Frame)
   CubeSim::Vector3D position = _spacecraft().position() - _earth().position();
   CubeSim::Vector3D velocity = _spacecraft().velocity() - _earth().velocity();

   // Z- in flight direction
   CubeSim::Vector3D b1 = -position;
   CubeSim::Vector3D b2 = b1 ^ velocity;
   CubeSim::Vector3D b3 = b1 ^ b2;

   // Compute and return LO Frame
   return CubeSim::Rotation(b1, b2, b3);
}


// Get Earth
const CubeSim::CelestialBody& Monitor::_earth(void) const
{
   // Earth
   static CubeSim::CelestialBody* earth;

   // Check Earth
   if (!earth)
   {
      // Get Earth
      earth = simulation()->celestial_body("Earth");
   }

   // Return Earth
   return *earth;
}


// Print Number
void Monitor::_print(uint8_t x, uint8_t y, const char* format, double number, uint8_t color, uint8_t background)
{
   // Set Position
   Console::position(x, y);

   // Set Background Color
   Console::background(background);

   // Check Number
   if (std::isnan(number))
   {
      // Set Text Color
      Console::color(Console::COLOR_LIGHT_RED);

      // Print NaN
      printf("NAN");
   }
   else
   {
      // Set Text Color
      Console::color(color);

      // Print Number
      printf(format, number);
   }
}


// Get Spacecraft
const CubeSim::Spacecraft& Monitor::_spacecraft(void) const
{
   // Spacecraft
   static CubeSim::Spacecraft* spacecraft;

   // Check Spacecraft
   if (!spacecraft)
   {
      // Get Spacecraft
      spacecraft = simulation()->spacecraft("Spacecraft");
   }

   // Return Spacecraft
   return *spacecraft;
}
