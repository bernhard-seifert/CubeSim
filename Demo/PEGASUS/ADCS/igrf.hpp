

// ADCS - IGRF


// Includes
#include <vector>
#include "vector.hpp"


// Preprocessor Directives
#pragma once


// Undefine Symbols
#undef _N


// Namespace ADCS
namespace ADCS
{
   // Class IGRF
   class IGRF;
}


// Class IGRF
class ADCS::IGRF
{
public:

   // Constructor
   IGRF(const numeric_t& time = _TIME);

   // Compute magnetic Field
   const Vector operator ()(const Vector& position) const;
   const Vector operator ()(const numeric_t& x, const numeric_t& y, const numeric_t& z) const;

   // Time
   const double& time(void) const;
   void time(const double& time);

private:

   // Earth Radius
   static const numeric_t _RADIUS;

   // Model Time [s] (since 2000-01-01 00:00:00)
   static const double _TIME;

   // Model Values
   static const numeric_t _G[];
   static const numeric_t _DG[];
   static const numeric_t _H[];
   static const numeric_t _DH[];

   // Model Dimension
   static const uint8_t _N = 13;

   // Delta Distance [m]
   static const numeric_t _D;

   // Compute scalar Potential (Parameters are not checked)
   numeric_t _V(const numeric_t& x, const numeric_t& y, const numeric_t& z) const;

   // Variables
   double _time;
   std::vector<numeric_t> _g;
   std::vector<numeric_t> _h;
   std::vector<numeric_t> _k;
};


// Compute magnetic Field
inline const ADCS::Vector ADCS::IGRF::operator ()(const Vector& position) const
{
   // Compute and return magnetic Field
   return (*this)(position.x(), position.y(), position.z());
}


// Get Time
inline const double& ADCS::IGRF::time(void) const
{
   // Return Time
   return _time;
}
