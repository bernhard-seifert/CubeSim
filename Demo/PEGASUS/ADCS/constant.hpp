

// ADCS - CONSTANT


// Includes
#include "vector.hpp"


// Preprocessor Directives
#pragma once


// Namespace ADCS
namespace ADCS
{
   // Class Constant
   class Constant;
}


// Class Constant
class ADCS::Constant
{
public:

   // Earth Angular Rate [rad/s]
   static const double EARTH_ANGULAR_RATE;

   // Earth Axis Tilt [rad]
   static const numeric_t EARTH_AXIS_TILT;

   // Earth Mass [kg]
   static const numeric_t EARTH_MASS;

   // Earth Year [s]
   static const numeric_t EARTH_YEAR;

   // Mean Earth Radius (WGS 84 Model) [m]
   static const numeric_t EARTH_RADIUS;

   // Earth Flattening (WGS 84 Model)
   static const numeric_t EARTH_FLATTENING;

   // Gravitational Constant [N*m^2/kg^2]
   static const numeric_t G;

   // Pi
   static const numeric_t PI;

   // Solar Constant [W/m^2]
   static const numeric_t SOLAR_IRRADIANCE;

   // Magnetorquer Shutdown Time [s]
   static const numeric_t MAGNETORQUER_SHUTDOWN_TIME;

   // Update Interval [s]
   static const numeric_t UPDATE_INTERVAL;

   // Detumble Gain
   static const numeric_t DETUMBLE_GAIN;

   // Detumble Limit (with Hysteresis) [rad/s]
   static const numeric_t DETUMBLE_LIMIT_LOW;
   static const numeric_t DETUMBLE_LIMIT_HIGH;

   // PI Controller Settings
   static const numeric_t CONTROL_P;
   static const numeric_t CONTROL_I;

   // GPS Position Acquisition Interval [s]
   static const numeric_t GPS_INTERVAL;

   // Gyro Lower angular Rate Limit [rad/s]
   static const numeric_t GYRO_LIMIT;

   // Moment of Inertia (Body Frame, diagonal Elements)
   static const Vector INERTIA;

   // Inverse Moment of Inertia (Body Frame, diagonal Elements)
   static const Vector INERTIA_INV;

   // Rate Filter
   static const numeric_t RATE_FILTER;
};
