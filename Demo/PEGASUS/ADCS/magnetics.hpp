

// ADCS - MAGNETICS


// Includes
#include "interface.hpp"


// Preprocessor Directives
#pragma once


// Namespace ADCS
namespace ADCS
{
   // Class Magnetics
   class Magnetics;
}


// Class Magnetics
class ADCS::Magnetics
{
public:

   // Get Field (Body Frame, cached)
   static const Vector& field(void);

   // Measure Field (pauses Torquers)
   static void measure(void);

   // Predict Field (ECI Frame)
   static const Vector predict_field(void);

   // Moment of Torquer (Body Frame) [A*m^2]
   static void moment(const Vector& moment);
   static const Vector& moment(void);

private:

   // Torquer Areas [m^2]
   static numeric_t _TORQUER_AREA[];

   // Torquer Current Limits [A]
   static numeric_t _TORQUER_CURRENT[];

   // IGRF Model Refresh Interval [s]
   static numeric_t _REFRESH;

   // Variables
   static Vector _field;
   static Vector _moment;
};


// Get Field (Body Frame, cached)
inline const ADCS::Vector& ADCS::Magnetics::field(void)
{
   // Return Field
   return _field;
}


// Get Moment of Torquer (Body Frame) [A*m^2]
inline const ADCS::Vector& ADCS::Magnetics::moment(void)
{
   // Return magnetic Moment
   return _moment;
}
