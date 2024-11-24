

// CUBESIM - POLYGON


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
#include "polygon.hpp"


// Compute Area
double CubeSim::Polygon2D::area(void) const
{
   // Check if Star-shaped
   if (!star())
   {
      // Exception
      throw Exception::Failed();
   }

   // Area
   double area = 0.0;

   // Parse Vertices
   for (size_t i = 0; i < _vertex.size(); ++i)
   {
      // Update Area
      area += abs(_vertex[i] ^ _vertex[(i + 1) % _vertex.size()]) / 2.0;
   }

   // Return Area
   return area;
}


// Compute Order of Vertices
uint8_t CubeSim::Polygon2D::order(void) const
{
   // Check if Star-shaped and Number of Vertices
   if (!star() || (_vertex.size() < 2))
   {
      // Exception
      throw Exception::Failed();
   }

   // Return Result
   return (((_vertex[0] ^ _vertex[1]) <= 0.0) ? ORDER_CW : ORDER_CCW);
}


// Check if Star-shaped
bool CubeSim::Polygon2D::star(void) const
{
   // Cross Product
   double p = 0.0;

   // Parse Vertices
   for (size_t i = 0; i < _vertex.size(); ++i)
   {
      // Compute Cross Product
      double p_ = _vertex[i] ^ _vertex[(i + 1) % _vertex.size()];

      // Check Cross Product
      if ((p * p_) < 0.0)
      {
         // Return Result
         return false;
      }

      // Update Cross Product
      p = p_;
   }

   // Return Result
   return true;
}


// Compute Center of Mass
const CubeSim::Vector2D CubeSim::Polygon2D::center(void) const
{
   // Check if Star-shaped
   if (!star())
   {
      // Exception
      throw Exception::Failed();
   }

   // Area, Center of Mass
   double area = 0.0;
   Vector2D center;

   // Parse Vertices
   for (size_t i = 0; i < _vertex.size(); ++i)
   {
      // Get Vertices of Triangle
      const Vector2D& v1 = _vertex[i];
      const Vector2D& v2 = _vertex[(i + 1) % _vertex.size()];

      // Compute Area and Center of Mass of Triangle
      double area_ = abs(v1 ^ v2) / 2.0;
      Vector2D center_ = (v1 + v2) / 3.0;

      // Update Area and Center of Mass
      area += area_;
      center += center_ * area_;
   }

   // Check Area
   if (area == 0.0)
   {
      // Exception
      throw Exception::Failed();
   }

   // Return Center of Mass
   return (center / area);
}


// Check if Point is inside
bool CubeSim::Polygon2D::inside(const Vector2D& point) const
{
   // Check if Star-shaped
   if (!star())
   {
      // Exception
      throw Exception::Failed();
   }

   // Parse Vertices
   for (size_t i = 0; i < _vertex.size(); ++i)
   {
      // Compute Cross Products
      double p1 = point ^ _vertex[i];
      double p2 = _vertex[(i + 1) % _vertex.size()] ^ point;
      double p3 = (point ^ (_vertex[(i + 1) % _vertex.size()] - _vertex[i])) -
         (_vertex[i] ^ _vertex[(i + 1) % _vertex.size()]);

      // Check Cross Products
      if (((0.0 <= p1) && (0.0 <= p2) && (0.0 <= p3)) || ((p1 < 0.0) && (p2 < 0.0) && (p3 < 0.0)))
      {
         // Return Result
         return true;
      }
   }

   // Return Result
   return false;
}
