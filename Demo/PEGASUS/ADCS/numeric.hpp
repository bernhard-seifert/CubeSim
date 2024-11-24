

// ADCS - NUMERIC


// Preprocessor Directives
#pragma once


// Numeric Constant
#define NUM(x)                         static_cast<ADCS::numeric_t>(x)

// Degrees to Radians Conversion
#define DEG_RAD(x)                     (NUM(x) * ADCS::Constant::PI / NUM(180.0))

// Radians to Degrees Conversion
#define RAD_DEG(x)                     (NUM(x) * NUM(180.0) / ADCS::Constant::PI)


// Namespace ADCS
namespace ADCS
{
   // Numeric Type
   typedef float numeric_t;
}
