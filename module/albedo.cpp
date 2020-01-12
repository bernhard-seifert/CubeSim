

// CUBESIM - MODULE - ALBEDO


// Includes
#include "albedo.hpp"
#include "../simulation.hpp"
#include "../module/light.hpp"


// Compute Irradiance [W/m^2]
double CubeSim::Module::Albedo::irradiance(const Vector3D& point, const Vector3D& direction, double angle) const
{
   // Check Direction and Angle
   if (direction == Vector3D() || (angle < 0.0) || (Constant::PI < angle))
   {
      // Exception
      throw Exception::Parameter();
   }

   // Check Initialization Flag
   if (!_init)
   {
      // Check Simulation
      if (!simulation())
      {
         // Exception
         throw Exception::Failed();
      }

      // Parse Module List
      for (auto module = simulation()->module().begin(); module != simulation()->module().end(); ++module)
      {
         // Check Module
         if (dynamic_cast<CubeSim::Module::Light*>(module->second))
         {
            // Insert Light Module into List
            _light.push_back(dynamic_cast<CubeSim::Module::Light*>(module->second));
         }
      }

      // Set Initialization Flag
      _init = true;
   }

   // Check for specific Celestial Body
   if (_celestial_body)
   {
      // Compute and return Irradiance
      return _irradiance(*_celestial_body, point, direction, angle);
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


// Default Resolution (Number of Grid Points)
const uint32_t CubeSim::Module::Albedo::_RESOLUTION;


// Compute Irradiance [W/m^2]
double CubeSim::Module::Albedo::_irradiance(const CelestialBody& celestial_body, const Vector3D& point,
   const Vector3D& direction, double angle) const
{
   // Compute Direction Unit Vector
   Vector3D direction0 = direction.unit();

   // Irradiance
   double irradiance = 0.0;

   // Parse Grid Points
   for (auto grid = _grid.begin(); grid != _grid.end(); ++grid)
   {
      // Compute Point on Celestial Body Surface (Flattening is neglected)
      Vector3D point_ = celestial_body.position() + celestial_body.radius() * *grid;

      // Compute relative Distance
      Vector3D distance = point - point_;

      // Compute first Cosine Factor
      double k1 = *grid * distance;

      // Check first Cosine Factor
      if (0.0 < k1)
      {
         // Irradiance
         double irradiance_ = 0.0;

         // Parse Light Module List
         for (auto light = _light.begin(); light != _light.end(); ++light)
         {
            // Update Irradiance
            irradiance_ += (*light)->irradiance(point_, *grid);
         }

         // Check Irradiance
         if (0.0 < irradiance_)
         {
            // Compute second Cosine Factor
            double k2 = -(distance * direction0);

            // Compute scalar Distance
            double distance_ = distance.norm();

            // Compute and check Angle
            if (acos(k2 / distance_) <= (angle / 2.0))
            {
               // Compute Point (Unit Vector) on Celestial Body (Body Frame)
               point_ = *grid - celestial_body.rotation();

               // Compute equatorial Distance
               double d = sqrt(point_.x() * point_.x() + point_.y() * point_.y());

               // Longitude, Latitude
               double longitude;
               double latitude;

               // Check equatorial Distance
               if (0.0 < d)
               {
                  // Compute Longitude and Latitude
                  longitude = atan2(point_.y(), point_.x());
                  latitude = atan(point_.z() / d);
               }
               else
               {
                  // Set Longitude and Latitude
                  longitude = 0.0;
                  latitude = (0.0 <= point_.z()) ? (Constant::PI / 2.0) : -(Constant::PI / 2.0);
               }

               // Compute and update Irradiance
               irradiance += irradiance_ * celestial_body.reflectivity(longitude, latitude) * k1 * k2 /
                  pow(distance_, 4.0);
            }
         }
      }
   }

   // Compute and return Irradiance
   return (irradiance * celestial_body.area() / _grid.size() / 4.0 / Constant::PI);
}
