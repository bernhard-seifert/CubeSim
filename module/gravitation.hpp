

// CUBESIM - MODULE - GRAVITATION


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
