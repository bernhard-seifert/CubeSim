

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
#include "simulation.hpp"


// Run
void CubeSim::Simulation::run(const Time& time)
{
   // Get Time
   uint64_t time_ = time;

   // Check Time
   if (time_ <= _time)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Fiber List
   std::vector<Fiber*> fiber;

   // Parse Module List
   for (auto module = this->module().begin(); module != this->module().end(); ++module)
   {
      try
      {
         // Create Fiber
         Fiber* fiber_ = new Fiber(_behavior, dynamic_cast<Behavior*>(module->second));

         // Insert Fiber into List
         fiber.push_back(fiber_);

         // Initialize
         module->second->_init();
      }
      catch (const Fiber::Exception&)
      {
         // Exception
         throw Exception::Internal();
      }
   }

   // Parse Spacecraft List
   for (auto spacecraft = this->spacecraft().begin(); spacecraft != this->spacecraft().end(); ++spacecraft)
   {
      try
      {
         // Create Fiber
         Fiber* fiber_ = new Fiber(_behavior, dynamic_cast<Behavior*>(spacecraft->second));

         // Insert Fiber into List
         fiber.push_back(fiber_);

         // Initialize
         spacecraft->second->_init();
      }
      catch (const Fiber::Exception&)
      {
         // Exception
         throw Exception::Internal();
      }

      // Parse Systems
      _parse(fiber, spacecraft->second->system());
   }

   // Check Fiber List
   if (fiber.size())
   {
      // Create Delay List
      std::vector<uint64_t> delay(fiber.size(), _time);

      // Clear Stop Flag
      _stop = false;

      // Loop until Stop Flag is set or End Time is reached
      while (!_stop && (_time < time_))
      {
         // Time
         uint64_t time_ = delay[0];
         size_t n = 0;

         // Parse Wait List
         for (size_t i = 1; i < fiber.size(); ++i)
         {
            // Check Time
            if (delay[i] < time_)
            {
               // Update Time and Index
               time_ = delay[i];
               n = i;
            }
         }

         // Update Time
         _time = time_;

         // Run Fiber
         fiber[n]->run();

         // Update Delay List
         delay[n] = fiber[n]->done() ? static_cast<uint64_t>(time) : _delay;
      }

      // Parse Fiber List
      for (auto fiber_ = fiber.begin(); fiber_ != fiber.end(); ++fiber_)
      {
         // Destroy Fiber
         delete *fiber_;
      }
   }
}


// Behavior
inline void CubeSim::Simulation::_behavior(void* parameter)
{
   // Call Behavior
   reinterpret_cast<Behavior*>(parameter)->_behavior();
}


// Parse Systems
void CubeSim::Simulation::_parse(std::vector<Fiber*>& fiber, const std::map<std::string, System*>& system)
{
   // Parse System List
   for (auto system_ = system.begin(); system_ != system.end(); ++system_)
   {
      try
      {
         // Create Fiber
         Fiber* fiber_ = new Fiber(_behavior, dynamic_cast<Behavior*>(system_->second));

         // Insert Fiber into List
         fiber.push_back(fiber_);

         // Initialize
         system_->second->_init();
      }
      catch (const Fiber::Exception&)
      {
         // Exception
         throw Exception::Internal();
      }

      // Parse Systems
      _parse(fiber, system_->second->system());
   }
}


// Default Time
const CubeSim::Time CubeSim::Simulation::_TIME(2015, 1, 1);
