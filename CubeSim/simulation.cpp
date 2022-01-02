

// CUBESIM - SIMULATION


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
         delay[n] = fiber[n]->done() ? time : _delay;
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
