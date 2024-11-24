

// CUBESIM - MODULE


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
   // Return Reference
   return *this;
}


// Get Simulation
inline CubeSim::Simulation* CubeSim::Module::simulation(void) const
{
   // Return Simulation
   return _simulation;
}
