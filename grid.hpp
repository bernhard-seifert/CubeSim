

// CUBESIM - GRID


// Includes
#include <stdint.h>
#include "vector.hpp"


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class Grid2D
   class Grid2D;

   // Class Grid3D
   class Grid3D;
}


// Class Grid2D
class CubeSim::Grid2D
{
public:

   // Constructor
   Grid2D(uint32_t resolution);

   // Resolution (Number of Points)
   uint32_t resolution(void) const;
   void resolution(uint32_t resolution);

   // Compute Points
   const std::vector<Vector2D> points(void) const;

private:

   // Variables
   uint32_t _resolution;
};


// Class Grid3D
class CubeSim::Grid3D
{
public:

   // Constructor
   Grid3D(uint32_t resolution);

   // Resolution (Number of Points)
   uint32_t resolution(void) const;
   void resolution(uint32_t resolution);

   // Compute Points
   const std::vector<Vector3D> points(void) const;

private:

   // Variables
   uint32_t _resolution;
};


// Constructor
inline CubeSim::Grid2D::Grid2D(uint32_t resolution)
{
   // Initialize
   this->resolution(resolution);
}


// Get Resolution (Number of Points)
inline uint32_t CubeSim::Grid2D::resolution(void) const
{
   // Return Resolution
   return _resolution;
}


// Set Resolution (Number of Points)
inline void CubeSim::Grid2D::resolution(uint32_t resolution)
{
   if (resolution < 7)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Resolution
   _resolution = resolution;
}


// Constructor
inline CubeSim::Grid3D::Grid3D(uint32_t resolution)
{
   // Initialize
   this->resolution(resolution);
}


// Get Resolution (Number of Points)
inline uint32_t CubeSim::Grid3D::resolution(void) const
{
   // Return Resolution
   return _resolution;
}


// Set Resolution (Number of Points)
inline void CubeSim::Grid3D::resolution(uint32_t resolution)
{
   if (resolution < 6)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Resolution
   _resolution = resolution;
}
