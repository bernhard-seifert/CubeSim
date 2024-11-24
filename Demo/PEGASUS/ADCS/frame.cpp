

// ADCS - FRAME


// Includes
#include "constant.hpp"
#include "frame.hpp"
#include "spacecraft.hpp"


// Transform from ECEF to ECI Frame
const ADCS::Vector ADCS::Frame::ECEF_ECI(const Vector& position, const double& time)
{
   // Compute Distance from Earth Axis
   numeric_t distance = std::sqrt(position.x() * position.x() + position.y() * position.y());

   // Check Distance
   if (distance == NUM(0.0))
   {
      // Compute and return Position (ECI Frame)
      return Vector(NUM(0.0), NUM(0.0), position.z());
   }

   // Compute Longitude
   numeric_t longitude = std::atan2(position.y(), position.x()) + NUM(std::fmod(time * Constant::EARTH_ANGULAR_RATE,
      2.0 * Constant::PI)) + _OFFSET_ECEF_ECI;

   // Compute and return Position (ECI Frame)
   return Vector(distance * std::cos(longitude), distance * std::sin(longitude), position.z());
}


// Transform from ECEF to ECI Frame
const ADCS::Location ADCS::Frame::ECEF_ECI(const Location& location)
{
   // Copy Location
   Location location_ = location;

   // Update Longitude
   location_.longitude(location.longitude() + NUM(std::fmod(location.time() * Constant::EARTH_ANGULAR_RATE, 2.0 *
      Constant::PI)) + _OFFSET_ECEF_ECI);

   // Return Location
   return location_;
}


// Transform from ECI to ECEF Frame
const ADCS::Vector ADCS::Frame::ECI_ECEF(const Vector& position, const double& time)
{
   // Compute Distance from Earth Axis
   numeric_t distance = std::sqrt(position.x() * position.x() + position.y() * position.y());

   // Check Distance
   if (distance == NUM(0.0))
   {
      // Compute and return Position (ECEF Frame)
      return Vector(NUM(0.0), NUM(0.0), position.z());
   }

   // Compute Longitude
   numeric_t longitude = std::atan2(position.y(), position.x()) - NUM(std::fmod(time * Constant::EARTH_ANGULAR_RATE,
      2.0 * Constant::PI)) - _OFFSET_ECEF_ECI;

   // Compute and return Position (ECEF Frame)
   return Vector(distance * std::cos(longitude), distance * std::sin(longitude), position.z());
}


// Transform from ECI to ECEF Frame
const ADCS::Location ADCS::Frame::ECI_ECEF(const Location& location)
{
   // Copy Location
   Location location_ = location;

   // Update Longitude
   location_.longitude(location.longitude() - NUM(std::fmod(location.time() * Constant::EARTH_ANGULAR_RATE, 2.0 *
      Constant::PI)) - _OFFSET_ECEF_ECI);

   // Return Location
   return location_;
}


// Compute LO Frame (ECI Frame), Z- in Flight Direction
const ADCS::Rotation ADCS::Frame::LO(void)
{
   // Compute Base Vectors of LO Frame
   Vector b1 = -Spacecraft::position();
   Vector b2 = b1 ^ Spacecraft::velocity();
   Vector b3 = b1 ^ b2;

   // Compute and return LO Frame
   return Rotation(b1, b2, b3);
}


// Longitude Offset between ECEF and ECI Frame
const ADCS::numeric_t ADCS::Frame::_OFFSET_ECEF_ECI = NUM(1.749313325);
