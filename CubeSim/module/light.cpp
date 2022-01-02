

// CUBESIM - MODULE - LIGHT


// Includes
#include "light.hpp"
#include "../simulation.hpp"


// Default Resolution (Number of Points)
const uint32_t CubeSim::Module::Light::DEFAULT_RESOLUTION;

// Computation Models
const uint8_t CubeSim::Module::Light::MODEL_POINT;
const uint8_t CubeSim::Module::Light::MODEL_DISK;


// Compute Irradiance [W/m^2]
double CubeSim::Module::Light::irradiance(const Vector3D& point, const Vector3D& direction, double angle) const
{
   // Check Direction and Angle
   if (direction == Vector3D() || (angle < 0.0) || (Constant::PI < angle))
   {
      // Exception
      throw Exception::Parameter();
   }

   // Check for specific Celestial Body
   if (_celestial_body)
   {
      // Compute and return Irradiance
      return _irradiance(*_celestial_body, point, direction, angle);
   }

   // Check Simulation
   if (!simulation())
   {
      // Exception
      throw Exception::Failed();
   }

   // Irradiance
   double irradiance = 0.0;

   // Parse Celestial Body List
   for (auto celestial_body = simulation()->celestial_body().begin();
      celestial_body != simulation()->celestial_body().end(); ++celestial_body)
   {
      // Update Irradiance
      irradiance += _irradiance(*celestial_body->second, point, direction, angle);
   }

   // Return Irradiance
   return irradiance;
}


// Temperature Limit (Red Star) [K]
const double CubeSim::Module::Light::_TEMPERATURE = 2000.0;


// Compute Irradiance [W/m^2]
double CubeSim::Module::Light::_irradiance(const CelestialBody& celestial_body, const Vector3D& point,
   const Vector3D& direction, double angle) const
{
   // Irradiance
   double irradiance = 0.0;

   // Check Temperature (only red Stars or hotter)
   if (_TEMPERATURE <= celestial_body.temperature())
   {
      // Compute Direction to Star
      Vector3D direction_star = celestial_body.position() - point;

      // Check Computation Model
      if (_model == MODEL_POINT)
      {
         // Check if Ray of Light is within opening angle
         if ((direction_star | direction) <= (angle / 2.0))
         {
            // Compute Distance to Star
            double distance_star = direction_star.norm();

            // Shadow Flag
            bool shadow = false;

            // Parse Celestial Body List
            for (auto celestial_body_ = simulation()->celestial_body().begin();
               celestial_body_ != simulation()->celestial_body().end(); ++celestial_body_)
            {
               // Check if Celestial Body is different from Star
               if (&celestial_body != celestial_body_->second)
               {
                  // Compute Direction to Celestial Body
                  Vector3D direction_celestial_body = celestial_body_->second->position() - point;

                  // Check if Ray of Light intersects with Celestial Body (Flattening is neglected)
                  if ((((direction_celestial_body ^ direction_star).norm() / distance_star) <
                     celestial_body_->second->radius()) && (0.0 < (direction_star * direction_celestial_body)))
                  {
                     // Set Shadow Flag
                     shadow = true;
                     break;
                  }
               }
            }

            // Check Shadow Flag
            if (!shadow)
            {
               // Update Irradiance
               irradiance += Constant::SIGMA * pow(celestial_body.temperature(), 4.0) *
                  pow(celestial_body.radius(), 2.0) / pow(distance_star, 3.0) * (direction_star * direction.unit());
            }
         }
      }
      else
      {
         // Rotation
         Rotation rotation;

         // Check Distance to Star
         if ((direction_star.x() != 0.0) || (direction_star.y() != 0.0))
         {
            // Compute Base Vectors of Rotation
            Vector3D b1 = Vector3D(direction_star.y(), -direction_star.x(), 0.0);
            Vector3D b2 = b1 ^ direction_star;

            // Set Rotation
            rotation = Rotation(b1, b2, direction_star);
         }

         // Compute Distance to Star
         double distance_star = direction_star.norm();

         // Number of Light Rays
         uint32_t n = 0;

         // Parse Grid Points
         for (auto grid = _grid.begin(); grid != _grid.end(); ++grid)
         {
            // Compute Direction to Grid Point
            Vector3D direction_grid = (*grid * celestial_body.radius()) + rotation + direction_star;

            // Check if Ray of Light is within opening angle
            if ((direction_grid | direction) <= (angle / 2.0))
            {
               // Shadow Flag
               bool shadow = false;

               // Parse Celestial Body List
               for (auto celestial_body_ = simulation()->celestial_body().begin();
                  celestial_body_ != simulation()->celestial_body().end(); ++celestial_body_)
               {
                  // Check if Celestial Body is different from Star
                  if (&celestial_body != celestial_body_->second)
                  {
                     // Compute Direction to Celestial Body
                     Vector3D direction_celestial_body = celestial_body_->second->position() - point;

                     // Check if Ray of Light intersects with Celestial Body (Flattening is neglected,
                     // Radius of Star << Distance is assumed)
                     if ((((direction_celestial_body ^ direction_grid).norm() / distance_star) <
                        celestial_body_->second->radius()) && (0.0 < (direction_grid * direction_celestial_body)))
                     {
                        // Set Shadow Flag
                        shadow = true;
                        break;
                     }
                  }
               }

               // Check Shadow Flag
               if (!shadow)
               {
                  // Increment Number of Light Rays
                  ++n;
               }
            }
         }

         // Update Irradiance
         irradiance += Constant::SIGMA * pow(celestial_body.temperature(), 4.0) * n / _grid.size() *
            pow(celestial_body.radius(), 2.0) / pow(distance_star, 3.0) * (direction_star * direction.unit());
      }
   }

   // Return Irradiance
   return irradiance;
}
