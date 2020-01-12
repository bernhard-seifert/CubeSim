

// CUBESIM - CONSTANT


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class Constant
   class Constant;
}


// Class Constant
class CubeSim::Constant
{
public:

   // Gravitational Constant [m^3/kg/s^2]
   static const double G;

   // Pi
   static const double PI;

   // Stefan-Boltzmann Constant [W/m^2/K^4]
   static const double SIGMA;

   // Epsilon (for Vector and Matrix Comparison)
   static const double EPSILON;
};
