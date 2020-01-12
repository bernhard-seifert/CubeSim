

// CUBESIM - MODULE


// Includes
#include <typeinfo>
#include "behavior.hpp"
#include "exception.hpp"
#include "list.hpp"


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class Module
   class Module;

   // Class Simulation
   class Simulation;

   // Class Spacecraft
   class Spacecraft;
}


// Module
class CubeSim::Module : public Behavior, public List<Module>::Item
{
public:

   // Class Albedo
   class Albedo;

   // Class Ephemeris
   class Ephemeris;

   // Class Gravitation
   class Gravitation;

   // Class Light
   class Light;

   // Class Magnetics
   class Magnetics;

   // Class Motion;
   class Motion;

   // Constructor
   Module(void);

   // Copy Constructor (Simulation Reference is reset)
   Module(const Module& module);

   // Assign (Simulation Reference is maintained)
   Module& operator =(const Module& module);

   // Clone
   virtual Module* clone(void) const = 0;

   // Get Simulation
   Simulation* simulation(void) const;

private:

   // Variables
   Simulation* _simulation;

   // Friends
   friend class Simulation;
};


// Constructor
inline CubeSim::Module::Module(void) : _simulation()
{
}


// Copy Constructor (Simulation Reference is reset)
inline CubeSim::Module::Module(const Module& module) : _simulation()
{
}


// Assign (Simulation Reference is maintained)
inline CubeSim::Module& CubeSim::Module::operator =(const Module& module)
{
   // Check Type
   if (typeid(*this) != typeid(module))
   {
      // Exception
      throw Exception::Parameter();
   }

   // Return Reference
   return *this;
}


// Get Simulation
inline CubeSim::Simulation* CubeSim::Module::simulation(void) const
{
   // Return Simulation
   return _simulation;
}
