

// CUBESIM - MODULE - MOTION


// Includes
#include "motion.hpp"
#include "../simulation.hpp"


// Class _State
class CubeSim::Module::Motion::_State
{
public:

   // Variables *** we add angular momentum here ***
   Vector3D acceleration;
   Vector3D angular_acceleration;
   Matrix3D inertia;
   Matrix3D inertia_inverse;
};


// Default Time Step [s]
const double CubeSim::Module::Motion::_TIME_STEP = 1.0;


// Behavior
void CubeSim::Module::Motion::_behavior(void)
{
   // Check Simulation
   if (!simulation())
   {
      // Exception
      throw Exception::Failed();
   }

   // State List
   std::map<void*, _State> state;

   // Parse Spacecraft List
   for (auto spacecraft = simulation()->spacecraft().begin(); spacecraft != simulation()->spacecraft().end();
      ++spacecraft)
   {
      // Get State
      _State& state_ = state[spacecraft->second];

      // Initialize Acceleration, angular Acceleration, Momentum of Inertia (Body Frame)
      state_.acceleration.x(NAN);
      state_.angular_acceleration.x(NAN);
      state_.inertia = Inertia();
   }

   // Parse Celestial Body List
   for (auto celestial_body = simulation()->celestial_body().begin();
      celestial_body != simulation()->celestial_body().end(); ++celestial_body)
   {
      // Get State
      _State& state_ = state[celestial_body->second];

      // Initialize Acceleration
      state_.acceleration.x(NAN);
   }

   // Loop
   for (;;)
   {
      // Get Time Step
      double time_step = _time_step;

      // Delay
      simulation()->delay(time_step);

      // Parse Spacecraft List
      for (auto spacecraft = simulation()->spacecraft().begin(); spacecraft != simulation()->spacecraft().end();
         ++spacecraft)
      {
         // Get State
         _State& state_ = state[spacecraft->second];

         // Compute Wrench
         Wrench wrench = spacecraft->second->wrench();

         // Compute Acceleration
         Vector3D acceleration = wrench.force() / spacecraft->second->mass();

         // Check Acceleration
         if (isnan(state_.acceleration.x()))
         {
            // Initialize Acceleration
            state_.acceleration = acceleration;
         }

         // Update Position (Acceleration is extrapolated and integrated) *** make this with t^2 fit ***
         spacecraft->second->move((spacecraft->second->velocity() + (4.0 * acceleration - state_.acceleration) *
            time_step / 6.0) * time_step);

         // Update Velocity (Acceleration is extrapolated and integrated) *** make this with t^2 fit ***
         spacecraft->second->velocity(spacecraft->second->velocity() + (3.0 * acceleration - state_.acceleration) *
            time_step / 2.0);

         // Update Acceleration
         state_.acceleration = acceleration;

         // Compute Momentum of Inertia (Body Frame)
         Matrix3D inertia = spacecraft->second->inertia() - spacecraft->second->rotation();

         // Check if Momentum of Inertia (Body Frame) was modified
         if (inertia != state_.inertia)
         {
            // Update inverse Momentum of Inertia (Body Frame)
            state_.inertia_inverse = inertia.inverse();

            // Set Momentum of Inertia (Body Frame)
            state_.inertia = inertia;
         }

         // *** strategy for reaction wheels
         // *** here we compute angular momentum of spacecraft
         // *** if spin rate of wheels was changed => angular momentum changes
         // *** conservation of angular momentum => adjust spacecraft spin rate so that angular momentum stays constant
         // *** => reaction wheel does not need to generate torque, but only change spin rate!
         // *** L = I * w + L_int => w = I_new_inv * L_old
         // *** problem: angular momentum is allowed to change due to external torques!!!

         // Compute angular Acceleration
         Vector3D angular_acceleration = (state_.inertia_inverse + spacecraft->second->rotation()) *
            (wrench.torque() - (spacecraft->second->angular_rate() ^ spacecraft->second->angular_momentum()));

         // Check angular Acceleration
         if (isnan(state_.angular_acceleration.x()))
         {
            // Initialize angular Acceleration
            state_.angular_acceleration = angular_acceleration;
         }

         // Compute Rotation *** whrere is this formula coming from?
         Vector3D rotation = (spacecraft->second->angular_rate() + (4.0 * angular_acceleration -
            state_.angular_acceleration) * time_step / 6.0) * time_step;

         // Check Rotation
         if (rotation != Vector3D())
         {
            // Update Rotation
            spacecraft->second->rotate(rotation, rotation.norm());
         }

         // Update angular Rate *** whrere is this formula coming from?
         spacecraft->second->angular_rate(spacecraft->second->angular_rate() +
            (3.0 * angular_acceleration - state_.angular_acceleration) * time_step / 2.0);

         // *** here we should save angular momentum for next round

         // Update angular Acceleration
         state_.angular_acceleration = angular_acceleration;
      }

      // Parse Celestial Body List
      for (auto celestial_body = simulation()->celestial_body().begin();
         celestial_body != simulation()->celestial_body().end(); ++celestial_body)
      {
         // Get State
         _State& state_ = state[celestial_body->second];

         // Compute Wrench
         Wrench wrench = celestial_body->second->wrench();

         // Compute Acceleration
         Vector3D acceleration = wrench.force() / celestial_body->second->mass();

         // Check Acceleration
         if (isnan(state_.acceleration.x()))
         {
            // Initialize Acceleration
            state_.acceleration = acceleration;
         }

         // Update Position
         celestial_body->second->move((celestial_body->second->velocity() + (4.0 * acceleration - state_.acceleration) *
            time_step / 6.0) * time_step);

         // Update Velocity
         celestial_body->second->velocity(celestial_body->second->velocity() + (3.0 * acceleration -
            state_.acceleration) * time_step / 2.0);

         // Update Acceleration
         state_.acceleration = acceleration;

         // Check angular Rate
         if (celestial_body->second->angular_rate() != Vector3D())
         {
            // Update Rotation
            celestial_body->second->rotate(celestial_body->second->angular_rate(),
               celestial_body->second->angular_rate().norm() * time_step);
         }
      }
   }
}
