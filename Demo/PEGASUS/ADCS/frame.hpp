

// ADCS - FRAME


// Includes
#include "interface.hpp"
#include "location.hpp"
#include "rotation.hpp"


// Preprocessor Directives
#pragma once


// Namespace ADCS
namespace ADCS
{
   // Class Frame
   class Frame;
}


// Class Frame
class ADCS::Frame
{
public:

   // Transform from ECEF to ECI Frame
   static const Vector ECEF_ECI(const Vector& position);
   static const Vector ECEF_ECI(const Vector& position, const double& time);
   static const Location ECEF_ECI(const Location& location);

   // Transform from ECI to ECEF Frame
   static const Vector ECI_ECEF(const Vector& position);
   static const Vector ECI_ECEF(const Vector& position, const double& time);
   static const Location ECI_ECEF(const Location& location);

   // Compute LO Frame (ECI Frame)
   static const Rotation LO(void);

private:

   // Longitude Offset between ECEF and ECI Frame at 2000-01-01 00:00:00
   static const numeric_t _OFFSET_ECEF_ECI;
};


// Transform from ECEF to ECI Frame
inline const ADCS::Vector ADCS::Frame::ECEF_ECI(const Vector& position)
{
   // Transform and return Result
   return ECEF_ECI(position, Interface::time());
}


// Transform from ECI to ECEF Frame
inline const ADCS::Vector ADCS::Frame::ECI_ECEF(const Vector& position)
{
   // Transform and return Result
   return ECI_ECEF(position, Interface::time());
}
