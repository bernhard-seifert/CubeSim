

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
   Vector3D angular_momentum;
   Matrix3D inertia;
   Matrix3D inertia_inverse;
   Vector3D a0, a1, a2, a3, a4;

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

   // Parse Spacecraft List
   for (auto spacecraft = simulation()->spacecraft().begin(); spacecraft != simulation()->spacecraft().end();
      ++spacecraft)
   {
      // Get State
      _State& state_ = state[spacecraft->second];

      // Initialize Acceleration, angular Acceleration, Moment of Inertia (Body Frame)
      state_.acceleration.x(NAN);
/*
      state_.angular_acceleration.x(NAN);
      state_.inertia = Inertia();
*/
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

   // ***
   uint64_t i = 0;
   float time_step_final = _time_step;

   double time_step = 1;

   // Loop
   for (;;++i)
   {
      // Get Time Step
      double time_step = _time_step;

      // ***
//      if (time_step < time_step_final) time_step *= 1.1;
//      dynamic_cast<CubeSim::Module::Gravitation*>(simulation()->module("Gravitation"))->time_step(time_step);



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

         // *** SPACECRAFT TRANSLATION FROM HERE ***********************************************************************************


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

         // *** SPACECRAFT ROTATION FROM HERE ***********************************************************************************

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

         // *** strategy for reaction wheels
         // *** here we compute angular momentum of spacecraft
         // *** if spin rate of wheels was changed => angular momentum changes
         // *** conservation of angular momentum => adjust spacecraft spin rate so that angular momentum stays constant
         // *** => reaction wheel does not need to generate torque, but only change spin rate!
         // *** L = I * w + L_int => w = I_new_inv * L_old
         // *** problem: angular momentum is allowed to change due to external torques!!!
         // *** dw/dt = I_-1 * (T - w x L)
         // *** I * dw/dt + w x L = T, is that correct?


         // Compute angular Acceleration
         Vector3D angular_acceleration = (state_.inertia_inverse + spacecraft->second->rotation()) *
            (wrench.torque() - (spacecraft->second->angular_rate() ^ spacecraft->second->angular_momentum()));

//         auto w = spacecraft->second->wrench();

//            printf("accel: %.3E, %.3E, %.3E\n", angular_acceleration.x(), angular_acceleration.y(), angular_acceleration.z());


         // Check for First Run
         if (first)
         {
            // Initialize angular Acceleration and angular Momentum
            state_.angular_acceleration = angular_acceleration;
            state_.angular_momentum = spacecraft->second->angular_momentum();
         }

         // Compute Rotation
         Vector3D rotation = (spacecraft->second->angular_rate() + (4.0 * angular_acceleration -
            state_.angular_acceleration) * time_step / 6.0) * time_step;

         // Check Rotation
         if (rotation != Vector3D())
         {
            // Compute Rotation Matrix
            CubeSim::Rotation R(rotation, rotation.norm());

            // Get Center of Mass
            Vector3D center = spacecraft->second->center();

            // Update Rotation
            spacecraft->second->rotate(R);

            // Restore Center of Mass (important for Accelerometers)
            spacecraft->second->move(center - spacecraft->second->center());
         }

         // Update angular Rate (due to external Torques)
         spacecraft->second->angular_rate(spacecraft->second->angular_rate() +
            (3.0 * angular_acceleration - state_.angular_acceleration) * time_step / 2.0);

         // Update angular Rate (due to Conservation of angular Momentum)
         spacecraft->second->angular_rate(spacecraft->second->angular_rate() +
            (state_.inertia_inverse + spacecraft->second->rotation()) *
            (state_.angular_momentum - spacecraft->second->angular_momentum()));

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

         if (first)
         {
            state_.a4 = acceleration;
            state_.a3 = acceleration;
            state_.a2 = acceleration;
            state_.a1 = acceleration;
         }
         else
         {
            state_.a4 = state_.a3;
            state_.a3 = state_.a2;
            state_.a2 = state_.a1;
            state_.a1 = acceleration;
         }


         uint8_t model = 3;
         if (i < model) model = i;
         if (model == 0)
         {

            // Update Position
            celestial_body->second->move((celestial_body->second->velocity() + state_.a1 / 2.0 * time_step) * time_step);

            // Update Velocity
            celestial_body->second->velocity(celestial_body->second->velocity() + state_.a1 * time_step);
         }
         else if (model == 1)
         {
            // Update Position
            celestial_body->second->move((celestial_body->second->velocity() + (4.0 * state_.a1 - state_.a2) / 6.0 * time_step) * time_step);

            // Update Velocity
            celestial_body->second->velocity(celestial_body->second->velocity() + (3.0 * state_.a1 - state_.a2) / 2.0 * time_step);
         }
         else if (model == 2)
         {
            // Update Position
            celestial_body->second->move((celestial_body->second->velocity() + (19.0 * state_.a1 - 10.0 * state_.a2 + 3.0 * state_.a3) / 24.0 * time_step) * time_step);

            // Update Velocity
            celestial_body->second->velocity(celestial_body->second->velocity() + (23.0 * state_.a1 - 16.0 * state_.a2 + 5.0 * state_.a3) / 12.0 * time_step);
         }
         else if (model == 3)
         {
            // Update Position
            celestial_body->second->move((celestial_body->second->velocity() + (323.0 * state_.a1 - 264.0 * state_.a2 + 159.0 * state_.a3 - 38.0 * state_.a4) / 360.0 * time_step) * time_step);

            // Update Velocity
            celestial_body->second->velocity(celestial_body->second->velocity() + (55.0 * state_.a1 - 59.0 * state_.a2 + 37.0 * state_.a3 - 9.0 * state_.a4) / 24.0 * time_step);
         }

/*

         // Check Acceleration
         if (isnan(state_.acceleration.x()))
         {
            // Initialize Acceleration
            state_.acceleration = acceleration;

            state_.a0 = state_.a1 = acceleration;
         }

         // Update Position
         celestial_body->second->move((celestial_body->second->velocity() + acceleration / 2.0 * time_step) * time_step);

         // Update Velocity
         celestial_body->second->velocity(celestial_body->second->velocity() + acceleration * time_step);
*/


/* *** UNKNOWN FORMULA
         // Update Position
         celestial_body->second->move((celestial_body->second->velocity() + (4.0 * acceleration - state_.acceleration) *
            time_step / 6.0) * time_step);

         // Update Velocity
         celestial_body->second->velocity(celestial_body->second->velocity() + (3.0 * acceleration -
            state_.acceleration) * time_step / 2.0);
*/
/*
         // Update Position
         celestial_body->second->move((celestial_body->second->velocity() +
            (3.0 * acceleration + 10.0 * state_.a1 - state_.a0) * time_step / 24.0) * time_step);

         // Update Velocity
         celestial_body->second->velocity(celestial_body->second->velocity() +
            (5.0 * acceleration + 8.0 * state_.a1 - state_.a0) * time_step / 12.0);


         state_.a0 = state_.a1;
         state_.a1 = acceleration;
*/
/*
         // Update Position
         celestial_body->second->move((celestial_body->second->velocity() + (state_.acceleration + acceleration / 2.0) *
            time_step / 3.0) * time_step);

         // Update Velocity
         celestial_body->second->velocity(celestial_body->second->velocity() + (acceleration + state_.acceleration) *
            time_step / 2.0);
*/
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

      // Clear first Flag
      first = false;
   }
}
