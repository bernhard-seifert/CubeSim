

// CUBESIM - CONSTANT


// Includes
#include <limits>
#include "constant.hpp"


// Gravitational Constant [m^3/kg/s^2]
const double CubeSim::Constant::G = 6.67430E-11;

// Pi
const double CubeSim::Constant::PI = 3.14159265358979323846;

// Stefan-Boltzmann Constant [W/m^2/K^4]
const double CubeSim::Constant::SIGMA = 5.670374419E-8;

// Epsilon (for Vector and Matrix Comparison)
const double CubeSim::Constant::EPSILON = std::numeric_limits<double>::epsilon() * 100.0;
