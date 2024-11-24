

// ADCS - TASK


// Includes
#include "constant.hpp"
#include "magnetics.hpp"
#include "operation.hpp"
#include "spacecraft.hpp"
#include "task.hpp"


// Check Compiler
#ifndef _MSC_VER

   // OBC Measurement Task Semaphore
   extern SemaphoreHandle_t adcs_task_trigger_semaphore;

#endif


// Task
void ADCS::task(void)
{
   // Loop
   for (;;)
   {
      // Check if enabled
      if (Operation::_enable)
      {
         // Disable Magnetorquers
         Magnetics::moment(Vector());
      }

      // Wait until generated magnetic Field ceased
      Interface::delay(Constant::MAGNETORQUER_SHUTDOWN_TIME);

      // Check Compiler
      #ifndef _MSC_VER

         // Synchronize with OBC Measurement Task (Timeout must be greater than calling Period)
         xSemaphoreTake(adcs_task_trigger_semaphore, (TickType_t) 1200);

      #endif

      // Measure magnetic Field
      Magnetics::measure();

      // Update Spacecraft Position and Rotation
      Spacecraft::update();

      // Check if enabled
      if (Operation::_enable)
      {
         // Check angular Rate
         if (std::isnan(Spacecraft::angular_rate().x()))
         {
            // Update Status
            Operation::_status = Operation::STATUS_DISABLED;
         }
         else if (Spacecraft::angular_rate().norm() <= Constant::DETUMBLE_LIMIT_LOW)
         {
            // Update Status
            Operation::_status = Operation::STATUS_CONTROL;
         }
         else if (Constant::DETUMBLE_LIMIT_HIGH <= Spacecraft::angular_rate().norm())
         {
            // Update Status
            Operation::_status = Operation::STATUS_DETUMBLING;
         }

         // Torque (Body Frame)
         Vector torque;

         // Check Status
         if (Operation::_status == Operation::STATUS_DETUMBLING)
         {
            // Compute Torque (Body Frame)
            torque = -Constant::DETUMBLE_GAIN * Spacecraft::angular_momentum();
         }
         else if (Operation::_status == Operation::STATUS_CONTROL)
         {

            // Compute local orbital Frame
            Rotation lof = Frame::LO();

            // Compute differential Rotation (Body Frame), compensate Angle Deviation of ~30° due to P Controller
            Rotation dR = lof - Spacecraft::rotation() - Rotation(Vector::Y, DEG_RAD(30));

            // Compute Error
            Vector error = dR.axis() * dR.angle();

            // Compute required angular Rate
            Vector angular_rate = 0.002 * error;


            // Compute Torque
            torque = (Matrix(Constant::INERTIA) * (angular_rate - Spacecraft::angular_rate()) * NUM(0.005) +
               (Spacecraft::angular_rate() ^ Spacecraft::angular_momentum()));
         }

         // Compute mean magnetic Field in this Round (Body Frame)
         Vector magnetic_field = Magnetics::field() - (Spacecraft::angular_rate() ^ Magnetics::field()) *
            Constant::UPDATE_INTERVAL / NUM(2.0);

         // Compute Angle between required Torque and magnetic Field
         float angle_torque_magnetic_field = std::abs(magnetic_field % torque);

         // Check Angle
         if (std::abs(angle_torque_magnetic_field - Constant::PI / NUM(2.0)) <= DEG_RAD(30.0))
         {
            // Compute magnetic Moment
            Vector magnetic_moment = (magnetic_field ^ torque) / std::pow(magnetic_field.norm(), NUM(2.0));

            // Set Magnetorquers
            Magnetics::moment(magnetic_moment);
         }
      }
      else
      {
         // Update Status
         Operation::_status = Operation::STATUS_DISABLED;
      }

      // Wait for next Round
      Interface::delay(Constant::UPDATE_INTERVAL - Constant::MAGNETORQUER_SHUTDOWN_TIME);
   }
}
