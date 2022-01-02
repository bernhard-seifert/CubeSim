

// CUBESIM - BEHAVIOR


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class Behavior
   class Behavior;
}


// Class Behavior
class CubeSim::Behavior
{
private:

   // Behavior
   virtual void _behavior(void);

   // Friends
   friend class Simulation;
};


// Behavior
inline void CubeSim::Behavior::_behavior(void)
{
}
