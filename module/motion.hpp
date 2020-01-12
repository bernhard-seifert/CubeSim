

// CUBESIM - MODULE - MOTION


// Includes
#include "../module.hpp"


// Preprocessor Directives
#pragma once


// Class Motion
class CubeSim::Module::Motion : public Module
{
public:

   // Constructor
   Motion(double time_step = _TIME_STEP);

   // Clone
   virtual Module* clone(void) const;

   // Time Step [S]
   double time_step(void) const;
   void time_step(double time_step);

private:

   // Class _State
   class _State;

   // Default Time Step [s]
   static const double _TIME_STEP;

   // Behavior
   virtual void _behavior(void);

   // Variables
   double _time_step;
};


// Constructor
inline CubeSim::Module::Motion::Motion(double time_step)
{
   // Initialize
   this->time_step(time_step);
}


// Clone
inline CubeSim::Module* CubeSim::Module::Motion::clone(void) const
{
   // Return Copy
   return new Motion(*this);
}


// Get Time Step [s]
inline double CubeSim::Module::Motion::time_step(void) const
{
   // Return Time Step
   return _time_step;
}


// Set Time Step [s]
inline void CubeSim::Module::Motion::time_step(double time_step)
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
