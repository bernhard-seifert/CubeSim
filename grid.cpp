

// CUBESIM - GRID


// Includes
#include "constant.hpp"
#include "grid.hpp"


// Compute Points
const std::vector<CubeSim::Vector2D> CubeSim::Grid2D::points(void) const
{
   // Grid
   std::vector<Vector2D> grid;

   // Compute Number of Radii
   uint32_t n = static_cast<uint32_t>(sqrt(_resolution / Constant::PI));

   // Parse Radii
   for (uint32_t i = 0; i <= n; ++i)
   {
      // Compute Number of Points
      uint32_t m = i ? static_cast<uint32_t>(2.0 * Constant::PI * i) : 1;

      // Parse Points
      for (uint32_t j = 0; j < m; ++j)
      {
         // Compute Point
         Vector2D point(cos(2.0 * Constant::PI * j / m) * i / n, sin(2.0 * Constant::PI * j / m) * i / n);

         // Insert Point into Grid
         grid.push_back(point);
      }
   }

   // Return Grid
   return grid;
}


// Compute Points
const std::vector<CubeSim::Vector3D> CubeSim::Grid3D::points(void) const
{
   // Grid
   std::vector<Vector3D> grid;

   // Compute Number of Latitudes
   uint32_t n = static_cast<uint32_t>(sqrt(_resolution / 4.0));

   // Parse Latitudes
   for (uint32_t i = 0; i <= n; ++i)
   {
      // Compute Latitude
      double latitude = Constant::PI / 2.0 * i / n;

      // Compute Number of Longitudes
      uint32_t m = (i == n) ? 1 : static_cast<uint32_t>(4.0 * cos(latitude) * n);

      // Parse Longitudes
      for (uint32_t j = 0; j < m; ++j)
      {
         // Compute Longitudes
         double longitude = 2.0 * Constant::PI * j / m;

         // Compute Point
         Vector3D point(cos(longitude) * cos(latitude), sin(longitude) * cos(latitude), sin(latitude));

         // Insert Point into Grid
         grid.push_back(point);

         // Check Latitude
         if (i)
         {
            // Mirror Point
            point.z(-point.z());

            // Insert Point into Grid
            grid.push_back(point);
         }
      }
   }

   // Return Grid
   return grid;
}
