

// CUBESIM - MODULE - GRAVITATION


// Includes
#include "../celestial_body.hpp"
#include "../module.hpp"


// Preprocessor Directives
#pragma once


// Class Gravitation
class CubeSim::Module::Gravitation : public Module
{
public:

   // Constructor
   Gravitation(double time_step = _TIME_STEP);

   // Clone
   virtual Module* clone(void) const;

   // Compute gravitational Field [m/s^2]
   const Vector3D field(const Vector3D& point) const;

   // Time Step [s]
   double time_step(void) const;
   void time_step(double time_step);

private:

   // Default Time Step [s]
   static const double _TIME_STEP;

   // Force Name
   static const std::string _FORCE;

   // Behavior
   virtual void _behavior(void);

   // Compute gravitational Field [m/s^2]
   const Vector3D _field(const CelestialBody& celestial_body, const Vector3D& point) const;

   // Variables
   double _time_step;
};


// Constructor
inline CubeSim::Module::Gravitation::Gravitation(double time_step)
{
   // Initialize
   this->time_step(time_step);
}


// Clone
inline CubeSim::Module* CubeSim::Module::Gravitation::clone(void) const
{
   // Return Copy
   return new Gravitation(*this);
}


// Get Time Step [s]
inline double CubeSim::Module::Gravitation::time_step(void) const
{
   // Return Time Step
   return _time_step;
}


// Set Time Step [s]
inline void CubeSim::Module::Gravitation::time_step(double time_step)
{
   // Check Time Step
   if (time_step <= 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Time Step
   _time_step = time_step;
}
