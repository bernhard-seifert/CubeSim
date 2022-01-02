

// CUBESIM - MODULE - MOTION


// Includes
#include "motion.hpp"
#include "../simulation.hpp"


// Class _State
class CubeSim::Module::Motion::_State
{
public:

   // Variables
   Vector3D acceleration;
   Vector3D angular_acceleration;
   Vector3D angular_momentum;
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

   // State List, first Flag
   std::map<void*, _State> state;
   bool first = true;

   // Loop
   for (;;)
   {
      // Delay
      simulation()->delay(_time_step);

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

         // Check for first Run
         if (first)
         {
            // Initialize Acceleration
            state_.acceleration = acceleration;
         }

         // Update Position (Acceleration is extrapolated and integrated)
         spacecraft->second->move((spacecraft->second->velocity() +
            (4.0 * acceleration - state_.acceleration) * _time_step / 6.0) * _time_step);

         // Update Velocity (Acceleration is extrapolated and integrated)
         spacecraft->second->velocity(spacecraft->second->velocity() +
            (3.0 * acceleration - state_.acceleration) * _time_step / 2.0);

         // Update Acceleration
         state_.acceleration = acceleration;

         // Compute Moment of Inertia (Body Frame)
         Matrix3D inertia = spacecraft->second->inertia() - spacecraft->second->rotation();

         // Check for first Run or if Moment of Inertia (Body Frame) was modified
         if (first || (inertia != state_.inertia))
         {
            // Update inverse Moment of Inertia (Body Frame)
            state_.inertia_inverse = inertia.inverse();

            // Set Moment of Inertia (Body Frame)
            state_.inertia = inertia;
         }

         // Update angular Rate (due to Conservation of angular Momentum)
         spacecraft->second->angular_rate(spacecraft->second->angular_rate() +
            (state_.inertia_inverse + spacecraft->second->rotation()) *
            (state_.angular_momentum - spacecraft->second->angular_momentum()));

         // Compute angular Acceleration
         Vector3D angular_acceleration = (state_.inertia_inverse + spacecraft->second->rotation()) *
            (wrench.torque() - (spacecraft->second->angular_rate() ^ spacecraft->second->angular_momentum()));

         // Check for First Run
         if (first)
         {
            // Initialize angular Acceleration and angular Momentum
            state_.angular_acceleration = angular_acceleration;
            state_.angular_momentum = spacecraft->second->angular_momentum();
         }

         // Compute Rotation (angular Acceleration is extrapolated and integrated)
         Vector3D rotation = (spacecraft->second->angular_rate() +
            (4.0 * angular_acceleration - state_.angular_acceleration) * _time_step / 6.0) * _time_step;

         // Check Rotation
         if (rotation != Vector3D())
         {
            // Compute Rotation Matrix
            CubeSim::Rotation R(rotation, rotation.norm());

            // Get Center of Mass
            Vector3D center = spacecraft->second->center();

            // Update Rotation (around Origin, not Center of Mass)
            spacecraft->second->rotate(R);

            // Restore Center of Mass (important for Accelerometers)
            spacecraft->second->move(center - spacecraft->second->center());
         }

         // Update angular Rate (due to external Torques, angular Acceleration is extrapolated and integrated)
         spacecraft->second->angular_rate(spacecraft->second->angular_rate() +
            (3.0 * angular_acceleration - state_.angular_acceleration) * _time_step / 2.0);

         // Update angular Acceleration and angular Momentum
         state_.angular_acceleration = angular_acceleration;
         state_.angular_momentum = spacecraft->second->angular_momentum();
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

         // Check for first Run
         if (first)
         {
            // Initialize Acceleration
            state_.acceleration = acceleration;
         }

         // Update Position (Acceleration is extrapolated and integrated)
         celestial_body->second->move((celestial_body->second->velocity() +
            (4.0 * acceleration - state_.acceleration) * _time_step / 6.0) * _time_step);

         // Update Velocity (Acceleration is extrapolated and integrated)
         celestial_body->second->velocity(celestial_body->second->velocity() +
            (3.0 * acceleration - state_.acceleration) * _time_step / 2.0);

         // Update Acceleration
         state_.acceleration = acceleration;
      }

      // Clear first Flag
      first = false;
   }
}
