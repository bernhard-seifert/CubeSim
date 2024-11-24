

// ADCS - CONSTANT


// Includes
#include "constant.hpp"


// Earth Angular Rate [rad/s]
const double ADCS::Constant::EARTH_ANGULAR_RATE = 7.2921150E-5;

// Earth Axis Tilt [rad]
const ADCS::numeric_t ADCS::Constant::EARTH_AXIS_TILT = NUM(0.409105177);

// Earth Mass [kg]
const ADCS::numeric_t ADCS::Constant::EARTH_MASS = NUM(5.97219E24);

// Earth Year [s]
const ADCS::numeric_t ADCS::Constant::EARTH_YEAR = NUM(365.25636 * 24.0 * 3600.0);

// Mean Earth Radius (WGS 84 Model) [m]
const ADCS::numeric_t ADCS::Constant::EARTH_RADIUS = NUM(6.378137E6);

// Earth Flattening (WGS 84 Model)
const ADCS::numeric_t ADCS::Constant::EARTH_FLATTENING = NUM(3.352811E-3);

// Gravitational Constant [N*m^2/kg^2]
const ADCS::numeric_t ADCS::Constant::G = NUM(6.67384E-11);

// Pi
const ADCS::numeric_t ADCS::Constant::PI = NUM(3.14159265359);

// Solar Constant [W/m^2]
const ADCS::numeric_t ADCS::Constant::SOLAR_IRRADIANCE = NUM(1360.8);

// Magnetorquer Shutdown Time [s]
const ADCS::numeric_t ADCS::Constant::MAGNETORQUER_SHUTDOWN_TIME = NUM(0.1);

// Update Interval [s]
const ADCS::numeric_t ADCS::Constant::UPDATE_INTERVAL = NUM(1.0);

// Detumble Gain
const ADCS::numeric_t ADCS::Constant::DETUMBLE_GAIN = NUM(0.01);

// Detumble Limit (with Hysteresis) [rad/s]
const ADCS::numeric_t ADCS::Constant::DETUMBLE_LIMIT_LOW = NUM(0.005);
const ADCS::numeric_t ADCS::Constant::DETUMBLE_LIMIT_HIGH = NUM(0.010);

// GPS Position Acquisition Interval [s]
const ADCS::numeric_t ADCS::Constant::GPS_INTERVAL = NUM(30.0);

// Gyro Lower angular Rate Limit [rad/s]
const ADCS::numeric_t ADCS::Constant::GYRO_LIMIT = NUM(0.005);

// Moment of Inertia (Body Frame, diagonal Elements)
const ADCS::Vector ADCS::Constant::INERTIA(NUM(0.00893), NUM(0.00899), NUM(0.0037));

// Inverse Moment of Inertia (Body Frame, diagonal Elements)
const ADCS::Vector ADCS::Constant::INERTIA_INV(1.0 / 0.00893, 1.0 / 0.00899, 1.0 / 0.0037);

// Rate Filter
const ADCS::numeric_t ADCS::Constant::RATE_FILTER = NUM(0.01);
