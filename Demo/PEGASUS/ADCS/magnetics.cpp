

// ADCS - MAGNETICS


// Includes
#include <algorithm>
#include "frame.hpp"
#include "igrf.hpp"
#include "magnetics.hpp"
#include "spacecraft.hpp"


// Measure Field (pauses Torquers)
void ADCS::Magnetics::measure(void)
{
   // Measure magnetic Field
   _field = Interface::magnetic_field();
}


// Predict Field (ECI Frame)
const ADCS::Vector ADCS::Magnetics::predict_field(void)
{
   // IGRF Model
   static IGRF _igrf;

   // Get Time
   double time = Interface::time();

   // Check Refresh Interval
   if ((_igrf.time() + _REFRESH) < time)
   {
      // Set Time
      _igrf.time(time);
   }

   // Get Spacecraft Position (ECEF)
   Vector position = Frame::ECI_ECEF(Spacecraft::position(), time);

   // Compute, transform and return magnetic Field
   return Frame::ECEF_ECI(_igrf(position), time);
}


// Set magnetic Moment of Torquer (Body Frame) [A*m^2]
void ADCS::Magnetics::moment(const Vector& moment)
{
   // Ratio
   numeric_t ratio = NUM(1.0);

   // Parse Axes
   for (uint8_t i = 1; i <= 3; ++i)
   {
      // Compute and update Ratio
      ratio = std::max(std::abs(moment(i)) / _TORQUER_AREA[i - 1] / _TORQUER_CURRENT[i - 1], ratio);
   }

   // Compute magnetic Moment
   _moment = moment / ratio;

   // Set Magnetorquers
   Interface::magnetorquer(Interface::SIDE_XM, -_moment.x() / _TORQUER_AREA[0]);
   Interface::magnetorquer(Interface::SIDE_XP, _moment.x() / _TORQUER_AREA[0]);
   Interface::magnetorquer(Interface::SIDE_YM, -_moment.y() / _TORQUER_AREA[1]);
   Interface::magnetorquer(Interface::SIDE_YP, _moment.y() / _TORQUER_AREA[1]);
   Interface::magnetorquer(Interface::SIDE_ZP, _moment.z() / _TORQUER_AREA[2]);
}


// Torquer Areas [m^2]
ADCS::numeric_t ADCS::Magnetics::_TORQUER_AREA[] = {NUM(2 * 0.64), NUM(2 * 0.64), NUM(0.38)};

// Torquer Current Limits [A]
ADCS::numeric_t ADCS::Magnetics::_TORQUER_CURRENT[] = {NUM(0.07), NUM(0.07), NUM(0.07)};

// IGRF Model Refresh Interval [s]
ADCS::numeric_t ADCS::Magnetics::_REFRESH = NUM(24.0 * 3600.0);


// Variables
ADCS::Vector ADCS::Magnetics::_field;
ADCS::Vector ADCS::Magnetics::_moment;
