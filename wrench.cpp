

// CUBESIM - WRENCH


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
#include "wrench.hpp"


// Constructor
CubeSim::Wrench::Wrench(const std::map<std::string, Force*>& force, const std::map<std::string, Torque*>& torque,
   double mass, const Vector3D& center)
{
   // Initialize
   this->mass(mass);
   _force.point(center);

   // Parse Force List
   for (auto force_ = force.begin(); force_ != force.end(); ++force_)
   {
      // Update Force and Torque
      _force += *force_->second;
      _torque += (force_->second->point() - center) ^ *force_->second;
   }

   // Parse Torque List
   for (auto torque_ = torque.begin(); torque_ != torque.end(); ++torque_)
   {
      // Update Torque
      _torque += *torque_->second;
   }
}


// Add and assign
CubeSim::Wrench& CubeSim::Wrench::operator +=(const Wrench& wrench)
{
   // Compute Mass
   double mass = _mass + wrench._mass;

   // Check Mass
   if (mass == 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Compute Center
   Vector3D center = (_force.point() * _mass + wrench._force.point() * wrench._mass) / mass;

   // Update Torque
   _torque += wrench._torque + ((_force.point() - center) ^ _force) +
      ((wrench._force.point() - center) ^ wrench._force);

   // Update Force
   _force += wrench._force;
   _force.point(center);

   // Update Mass
   _mass += wrench._mass;

   // Return Reference
   return *this;
}
