

// CUBESIM - POLYGON


// Includes
#include "vector.hpp"


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class _Polygon
   template <typename T> class _Polygon;

   // Class Polygon2D
   class Polygon2D;

   // Class Polygon3D
   class Polygon3D;
}


// Class _Polygon
template <typename T> class CubeSim::_Polygon
{
public:

   // Constructor
   _Polygon(void);
   _Polygon(const std::vector<T>& vertex);

   // Insert Vertex
   void operator +=(const T& vertex);
   void operator +=(const std::vector<T>& vertex);
   void insert(const T& vertex);
   void insert(const std::vector<T>& vertex);

   // Get Vertex
   const std::vector<T>& vertex(void) const;
   T& vertex(size_t index) const;

   // Compute Perimeter
   double perimeter(void) const;

   // Remove Vertex
   void remove(size_t index);

protected:

   // Variables
   std::vector<T> _vertex;
};


// Class Polygon2D
class CubeSim::Polygon2D : public _Polygon<Vector2D>
{
public:

   // Order of Vertices
   static const uint8_t ORDER_CW = 1;
   static const uint8_t ORDER_CCW = 2;

   // Constructor
   Polygon2D(void);
   Polygon2D(const std::vector<Vector2D>& vertex);

   // Compute Area
   double area(void) const;

   // Compute Center of Mass
   const Vector2D center(void) const;

   // Insert Vertex
   void insert(double x, double y);
   using _Polygon<Vector2D>::insert;

   // Check if Point is inside
   bool inside(const Vector2D& point) const;

   // Compute Order of Vertices
   uint8_t order(void) const;

   // Check if Star-shaped
   bool star(void) const;
};


// Class Polygon3D
class CubeSim::Polygon3D : public _Polygon<Vector3D>
{
public:

   // Constructor
   Polygon3D(void);
   Polygon3D(const std::vector<Vector3D>& vertex);

   // Insert Vertex
   void insert(double x, double y, double z);
   using _Polygon<Vector3D>::insert;
};


// Constructor
template <typename T> inline CubeSim::_Polygon<T>::_Polygon(void)
{
}


// Constructor
template <typename T> inline CubeSim::_Polygon<T>::_Polygon(const std::vector<T>& vertex) : _vertex(vertex)
{
}


// Insert Vertex
template <typename T> inline void CubeSim::_Polygon<T>::operator +=(const T& vertex)
{
   // Insert Vertex
   insert(vertex);
}


// Insert Vertex List
template <typename T> inline void CubeSim::_Polygon<T>::operator +=(const std::vector<T>& vertex)
{
   // Insert Vertex List
   insert(vertex);
}


// Insert Vertex
template <typename T> inline void CubeSim::_Polygon<T>::insert(const T& vertex)
{
   // Insert Vertex
   _vertex.push_back(vertex);
}


// Insert Vertex List
template <typename T> inline void CubeSim::_Polygon<T>::insert(const std::vector<T>& vertex)
{
   // Insert Vertex List
   _vertex.insert(_vertex.end(), vertex.begin(), vertex.end());
}


// Compute Perimeter
template <typename T> double CubeSim::_Polygon<T>::perimeter(void) const
{
   // Perimeter
   double perimeter = 0.0;

   // Parse Vertices
   for (size_t i = 0; i < _vertex.size(); ++i)
   {
      // Compute and update Perimeter
      perimeter += (_vertex[(i + 1) % _vertex.size()] - _vertex[i]).norm();
   }

   // Return Perimeter
   return perimeter;
}


// Get Vertex List
template <typename T> inline const std::vector<T>& CubeSim::_Polygon<T>::vertex(void) const
{
   // Return Vertex List
   return _vertex;
}


// Get Vertex
template <typename T> inline T& CubeSim::_Polygon<T>::vertex(size_t index) const
{
   // Check Index
   if (_vertex.size() <= index)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Return Vertex
   return const_cast<T&>(_vertex[index]);
}


// Remove Vertex
template <typename T> inline void CubeSim::_Polygon<T>::remove(size_t index)
{
   // Check Index
   if (_vertex.size() <= index)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Remove Vertex
   _vertex.erase(_vertex.begin() + index);
}


// Constructor
inline CubeSim::Polygon2D::Polygon2D(void)
{
}


// Constructor
inline CubeSim::Polygon2D::Polygon2D(const std::vector<Vector2D>& vertex) : _Polygon(vertex)
{
}


// Insert Vertex
inline void CubeSim::Polygon2D::insert(double x, double y)
{
   // Insert Vertex
   insert(Vector2D(x, y));
}


// Constructor
inline CubeSim::Polygon3D::Polygon3D(void)
{
}


// Constructor
inline CubeSim::Polygon3D::Polygon3D(const std::vector<Vector3D>& vertex) : _Polygon(vertex)
{
}


// Insert Vertex
inline void CubeSim::Polygon3D::insert(double x, double y, double z)
{
   // Insert Vertex
   insert(Vector3D(x, y, z));
}
