

// CUBESIM - SIMULATION


// Copyright (c) 2022 Bernhard Seifert
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sub-license, and / or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
// Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
// OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


// Includes
#include <fiber.hpp>
#include "celestial_body.hpp"
#include "module.hpp"
#include "spacecraft.hpp"


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class Simulation
   class Simulation;
}


// Class Simulation
class CubeSim::Simulation : private List<CelestialBody>, private List<Module>, private List<Spacecraft>
{
public:

   // Constructor
   Simulation(const Time& time = _TIME);

   // Get Celestial Body
   const std::map<std::string, CelestialBody*>& celestial_body(void) const;
   CelestialBody* celestial_body(const std::string& name) const;

   // Delay [s]
   void delay(double time);
   void delay(const Time& time);

   // Insert celestial Body, Module and Spacecraft
   CelestialBody& insert(const std::string& name, const CelestialBody& celestial_body);
   Module& insert(const std::string& name, const Module& module);
   Spacecraft& insert(const std::string& name, const Spacecraft& spacecraft);

   // Get Module
   const std::map<std::string, Module*>& module(void) const;
   Module* module(const std::string& name) const;

   // Run
   void run(double time);
   void run(const Time& time);

   // Get Spacecraft
   const std::map<std::string, Spacecraft*>& spacecraft(void) const;
   Spacecraft* spacecraft(const std::string& name) const;

   // Stop
   void stop(void);

   // Time
   const Time time(void) const;
   void time(const Time& time);

private:

   // Default Time
   static const Time _TIME;

   // Behavior
   static void _behavior(void* parameter);

   // Parse Systems
   static void _parse(std::vector<Fiber*>& fiber, const std::map<std::string, System*>& system);

   // Variables
   bool _stop;
   uint64_t _delay;
   uint64_t _time;
};


// Constructor
inline CubeSim::Simulation::Simulation(const Time& time) : _stop(), _delay(), _time(time)
{
}


// Get Celestial Body List
inline const std::map<std::string, CubeSim::CelestialBody*>& CubeSim::Simulation::celestial_body(void) const
{
   // Return Celestial Body List
   return List<CelestialBody>::item();
}


// Get Celestial Body
inline CubeSim::CelestialBody* CubeSim::Simulation::celestial_body(const std::string& name) const
{
   // Return Celestial Body
   return List<CelestialBody>::item(name);
}


// Delay [s]
inline void CubeSim::Simulation::delay(double time)
{
   // Check Time
   if (time <= 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Delay Time
   _delay = _time + static_cast<uint64_t>(round(time * 1000.0));

   // Suspend
   Fiber::suspend();
}


// Delay
inline void CubeSim::Simulation::delay(const Time& time)
{
   // Get Time
   uint64_t time_ = time;

   // Check Time
   if (time_ < _time)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Delay Time
   _delay = time_;

   // Suspend
   Fiber::suspend();
}


// Insert Celestial Body
inline CubeSim::CelestialBody& CubeSim::Simulation::insert(const std::string& name, const CelestialBody& celestial_body)
{
   // Insert Celestial Body
   CelestialBody& celestial_body_ = List<CelestialBody>::insert(name, celestial_body);

   // Set Simulation
   celestial_body_._simulation = this;

   // Return Reference
   return celestial_body_;
}


// Insert Module
inline CubeSim::Module& CubeSim::Simulation::insert(const std::string& name, const Module& module)
{
   // Insert Module
   Module& module_ = List<Module>::insert(name, module);

   // Set Simulation
   module_._simulation = this;

   // Return Reference
   return module_;
}


// Insert Spacecraft
inline CubeSim::Spacecraft& CubeSim::Simulation::insert(const std::string& name, const Spacecraft& spacecraft)
{
   // Insert Spacecraft
   Spacecraft& spacecraft_ = List<Spacecraft>::insert(name, spacecraft);

   // Set Simulation
   spacecraft_._simulation = this;

   // Return Reference
   return spacecraft_;
}


// Get Module List
inline const std::map<std::string, CubeSim::Module*>& CubeSim::Simulation::module(void) const
{
   // Return Module List
   return List<Module>::item();
}


// Get Module
inline CubeSim::Module* CubeSim::Simulation::module(const std::string& name) const
{
   // Return Module
   return List<Module>::item(name);
}


// Run [s]
inline void CubeSim::Simulation::run(double time)
{
   // Check Time
   if (time <= 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Run
   run(Time(_time + static_cast<int64_t>(time * 1000)));
}


// Get Spacecraft List
inline const std::map<std::string, CubeSim::Spacecraft*>& CubeSim::Simulation::spacecraft(void) const
{
   // Return Spacecraft List
   return List<Spacecraft>::item();
}


// Get Spacecraft
inline CubeSim::Spacecraft* CubeSim::Simulation::spacecraft(const std::string& name) const
{
   // Return Spacecraft
   return List<Spacecraft>::item(name);
}


// Stop
inline void CubeSim::Simulation::stop(void)
{
   // Set Stop Flag
   _stop = true;
}


// Get Time
inline const CubeSim::Time CubeSim::Simulation::time(void) const
{
   // Return Time
   return _time;
}


// Set Time
inline void CubeSim::Simulation::time(const Time& time)
{
   // Set Time
   _time = time;
}
