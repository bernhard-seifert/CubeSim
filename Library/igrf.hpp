

// IGRF 1.3.1


// Includes
#include <vector>
#include <time.hpp>


// Preprocessor Directives
#pragma once


// Class IGRF
class IGRF
{
public:

   // Class Field
   class Field;

   // Constructor
   IGRF(const Time& time = _TIME);

   // Compute magnetic Field
   const Field operator ()(double x, double y, double z) const;

   // Time
   const Time& time(void) const;
   void time(const Time& time);

private:

   // Earth Radius
   static const double _RADIUS;

   // Model Time
   static const Time _TIME;

   // Model Values
   static const double _G[];
   static const double _DG[];
   static const double _H[];
   static const double _DH[];

   // Model Dimension
   static const uint8_t _N = 13;

   // Delta Distance
   static const double _D;

   // Compute scalar Potential (Parameters are not checked)
   double _V(double x, double y, double z) const;

   // Variables
   Time _time;
   std::vector<double> _g;
   std::vector<double> _h;
   std::vector<double> _k;
};


// Class Field
class IGRF::Field
{
public:

   // Get Strength
   double strength(void) const;

   // Get X Coordinate
   double x(void) const;

   // Get Y Coordinate
   double y(void) const;

   // Get Z Coordinate
   double z(void) const;

private:

   // Constructor
   Field(void);
   Field(double x, double y, double z);

   // Variables
   double _strength;
   double _x;
   double _y;
   double _z;

   // Friends
   friend class IGRF;
};


// Get Time
inline const Time& IGRF::time(void) const
{
   // Return Time
   return _time;
}


// Get Strength
inline double IGRF::Field::strength(void) const
{
   // Return Strength
   return _strength;
}


// Get X Coordinate
inline double IGRF::Field::x(void) const
{
   // Return X Coordinate
   return _x;
}


// Get Y Coordinate
inline double IGRF::Field::y(void) const
{
   // Return Y Coordinate
   return _y;
}


// Get Z Coordinate
inline double IGRF::Field::z(void) const
{
   // Return Z Coordinate
   return _z;
}
