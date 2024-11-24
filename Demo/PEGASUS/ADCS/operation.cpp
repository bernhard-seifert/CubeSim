

// ADCS - OPERATION


// Includes
#include "magnetics.hpp"
#include "operation.hpp"
#include "spacecraft.hpp"
#include "sun.hpp"


// Status
const uint8_t ADCS::Operation::STATUS_DISABLED;
const uint8_t ADCS::Operation::STATUS_DETUMBLING;
const uint8_t ADCS::Operation::STATUS_CONTROL;

// South Atlantic Anomaly
const uint8_t ADCS::Operation::SAA_UNKNOWN;
const uint8_t ADCS::Operation::SAA_INSIDE;
const uint8_t ADCS::Operation::SAA_OUTSIDE;


// Get Info
const ADCS::Info& ADCS::Operation::info(void)
{
   // Get Time
   _info.timestamp = Interface::time();

   // Get Status
   _info.status = Operation::status();

   // Check if inside South Atlantic Anomaly
   _info.SAA = SAA();

   // Get Spacecraft Location
   Location location = Spacecraft::location();

   // Set Spacecraft Location
   _info.location.latitude = float_float16(location.latitude());
   _info.location.longitude = float_float16(location.longitude());
   _info.location.altitude = float_float16(location.altitude());

   // Get angular Rate from Gyro
   Vector angular_rate = Interface::angular_rate();

   // Set Gyro Measurement
   _info.gyro.x = float_float16(angular_rate.x());
   _info.gyro.y = float_float16(angular_rate.y());
   _info.gyro.z = float_float16(angular_rate.z());

   // Get Spacecraft angular Rate (Body Frame)
   angular_rate = Spacecraft::angular_rate();

   // Set angular Rate
   _info.angular_rate.x = float_float16(angular_rate.x());
   _info.angular_rate.y = float_float16(angular_rate.y());
   _info.angular_rate.z = float_float16(angular_rate.z());

   // Set Photo Sensor Measurement
   _info.photo.xm = float_float16(Interface::irradiance(Interface::SIDE_XM));
   _info.photo.xp = float_float16(Interface::irradiance(Interface::SIDE_XP));
   _info.photo.ym = float_float16(Interface::irradiance(Interface::SIDE_YM));
   _info.photo.yp = float_float16(Interface::irradiance(Interface::SIDE_YP));
   _info.photo.zm = float_float16(Interface::irradiance(Interface::SIDE_ZM));
   _info.photo.zp = float_float16(Interface::irradiance(Interface::SIDE_ZP));

   // Get Sun Direction (Body Frame)
   Vector sun = Sun::direction();

   // Set Sun Direction (Body Frame)
   _info.sun.x = float_float16(sun.x());
   _info.sun.y = float_float16(sun.y());
   _info.sun.z = float_float16(sun.z());

   // Set Albedo
   _info.albedo = float_float16(Sun::albedo());

   // Get magnetic Field (Body Frame)
   Vector magnetic_field = Magnetics::field();

   // Set magnetic Field (Body Frame)
   _info.magnetometer.x = float_float16(magnetic_field.x());
   _info.magnetometer.y = float_float16(magnetic_field.y());
   _info.magnetometer.z = float_float16(magnetic_field.z());

   // Get Spacecraft Orientation (LO Frame)
   Rotation orientation = Spacecraft::orientation();

   // Set Pitch, Yaw, Roll Angles
   _info.error.pitch = float_float16(orientation.pitch());
   _info.error.yaw = float_float16(orientation.yaw());
   _info.error.roll = float_float16(orientation.roll());

   // Get magnetic Moment [A*m^2]
   Vector magnetic_moment = Magnetics::moment();

   // Set magetic Moment (Body Frame)
   _info.torquer.x = float_float16(magnetic_moment.x());
   _info.torquer.y = float_float16(magnetic_moment.y());
   _info.torquer.z = float_float16(magnetic_moment.z());

   // Return Info
   return _info;
}


// Check if inside South Atlantic Anomaly
uint8_t ADCS::Operation::SAA(void)
{
   // Check Spacecraft Position
   if (std::isnan(Spacecraft::position().x()))
   {
      // Return Result
      return SAA_UNKNOWN;
   }

   // Get Spacecraft Location (ECEF Frame)
   Location location(Frame::ECI_ECEF(Spacecraft::position()));

   // Check Longitude and Latitude and return Result
   return (((_SAA_LATITUDE_MIN <= location.latitude()) && (location.latitude() <= _SAA_LATITUDE_MAX) &&
      (_SAA_LONGITUDE_MIN <= location.longitude()) && (location.longitude() <= _SAA_LONGITUDE_MAX)) ? SAA_INSIDE :
      SAA_OUTSIDE);
}


// South Atlantic Anomaly Limits
float ADCS::Operation::_SAA_LATITUDE_MIN = DEG_RAD(-50);
float ADCS::Operation::_SAA_LATITUDE_MAX = DEG_RAD(0);
float ADCS::Operation::_SAA_LONGITUDE_MIN = DEG_RAD(-85);
float ADCS::Operation::_SAA_LONGITUDE_MAX = DEG_RAD(35);


// Variables
bool ADCS::Operation::_enable = true;
ADCS::Info ADCS::Operation::_info;
uint8_t ADCS::Operation::_status = STATUS_DISABLED;
