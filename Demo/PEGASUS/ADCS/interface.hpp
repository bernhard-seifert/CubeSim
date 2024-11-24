

// ADCS - INTERFACE


// Includes
#include <CubeSim/simulation.hpp>
#include "location.hpp"


// Preprocessor Directives
#pragma once


// Namespace ADCS
namespace ADCS
{
   // Class Interface
   class Interface;
}


// Class Interface
class ADCS::Interface : public CubeSim::System
{
public:

   // Spacecraft Sides
   static const uint8_t SIDE_XM = 0;
   static const uint8_t SIDE_XP = 1;
   static const uint8_t SIDE_YM = 2;
   static const uint8_t SIDE_YP = 3;
   static const uint8_t SIDE_ZM = 4;
   static const uint8_t SIDE_ZP = 5;

   // Get angular Rate [rad/s]
   static const ADCS::Vector& angular_rate(void);

   // Clone
   virtual System* clone(void) const;

   // Delay [s]
   static void delay(const ADCS::numeric_t& time);

   // Get Irradiance [W/m^2]
   static const ADCS::numeric_t& irradiance(uint8_t side);

   // Get GPS Location
   static const Location& location(void);

   // Get magnetic Field [T]
   static const ADCS::Vector& magnetic_field(void);

   // Set Magnetorquer Current [A]
   static void magnetorquer(uint8_t side, const ADCS::numeric_t& current);

   // Print Debug Message
   static void print(const char* label, float value, uint8_t quality = 1);

   // Get Temperature [K]
   static const numeric_t temperature(uint8_t side);

   // Get Time [s] (since 2000-01-01 00:00:00)
   static double time(void);


private:

   // Default Measurement Delay [s]
   static const double _DELAY;

   // CubeSim-ADCS Conversions
   static const ADCS::Vector _convert(const CubeSim::Vector3D& vector);

   // Behavior
   virtual void _behavior(void);

   // Initialization
   virtual void _init(void);

   // Variables
   static ADCS::numeric_t _irradiance[6];
   static ADCS::Vector _angular_rate;
   static ADCS::Vector _magnetic_field;
   static Location _location;
   static Time _epoch;
   static CubeSim::Simulation* _simulation;
};


// Get angular Rate [rad/s]
inline const ADCS::Vector& ADCS::Interface::angular_rate(void)
{
   // Return angular Rate
   return _angular_rate;
}


// Clone
inline CubeSim::System* ADCS::Interface::clone(void) const
{
   // Return Copy
   return new Interface(*this);
}


// Delay [s]
inline void ADCS::Interface::delay(const ADCS::numeric_t& time)
{
   // Delay
   _simulation->delay(time);
}


// Get Irradiance [W/m^2]
inline const ADCS::numeric_t& ADCS::Interface::irradiance(uint8_t side)
{
   // Return Irradiance
   return _irradiance[side];
}


// Get GPS Location
inline const ADCS::Location& ADCS::Interface::location(void)
{
   // Return GPS Location
   return _location;
}


// Get magnetic Field [T]
inline const ADCS::Vector& ADCS::Interface::magnetic_field(void)
{
   // Return magnetic Field
   return _magnetic_field;
}


// Print Debug Message (is ignored)
inline void ADCS::Interface::print(const char* label, float value, uint8_t quality)
{
}


// Get Temperature [K] (default Values)
inline const ADCS::numeric_t ADCS::Interface::temperature(uint8_t side)
{
   // Return default Temperature
   return static_cast<numeric_t>(273.15 + 25);
}


// Get Time [s] (since 2000-01-01 00:00:00)
inline double ADCS::Interface::time(void)
{
   // Return Time
   return ((_simulation->time() - _epoch) / 1000.0);
}
