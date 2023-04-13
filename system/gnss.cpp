

// CUBESIM - SYSTEM - GNSS


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
#include "gnss.hpp"
#include "../simulation.hpp"


// Get Location
const CubeSim::Location CubeSim::System::GNSS::location(void) const
{
   // Check Earth
   if (!_earth)
   {
      // Check Simulation
      if (!simulation())
      {
         // Exception
         throw Exception::Failed();
      }

      // Parse Celestial Body List
      for (auto celestial_body = simulation()->celestial_body().begin(); celestial_body !=
         simulation()->celestial_body().end(); ++celestial_body)
      {
         // Check Celestial Body
         if (dynamic_cast<CelestialBody::Earth*>(celestial_body->second))
         {
            // Set Earth
            _earth = celestial_body->second;
            break;
         }
      }

      // Check Earth
      if (!_earth)
      {
         // Exception
         throw Exception::Failed();
      }
   }

   // Check if enabled
   if (!is_enabled())
   {
      // Return invalid Location
      return Location(*_earth, NAN, NAN, NAN);
   }

   // Get Spacecraft Position
   Vector3D position = spacecraft()->position();

   // Consider spatial Accuracy
   position.x(position.x() + _distribution(_generator) * _spatial_accuracy_ / sqrt(3.0));
   position.y(position.y() + _distribution(_generator) * _spatial_accuracy_ / sqrt(3.0));
   position.z(position.z() + _distribution(_generator) * _spatial_accuracy_ / sqrt(3.0));

   // Get Time (consider temporal Accuracy)
   Time time = simulation()->time() + static_cast<int64_t>(_distribution(_generator) * _temporal_accuracy_ * 1000.0);

   // Return Location
   return Location(*_earth, position, time);
}


// Default spatial Accuracy [m]
const double CubeSim::System::GNSS::_SPATIAL_ACCURACY = 0.0;

// Default temporal Accuracy [s]
const double CubeSim::System::GNSS::_TEMPORAL_ACCURACY = 0.0;
