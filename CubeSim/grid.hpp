

// CUBESIM - GRID


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
