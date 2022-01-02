

// CUBESIM - PART


// Includes
#include "material.hpp"
#include "rigid_body.hpp"


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class Part
   class Part;
}


// Class Part
class CubeSim::Part : public RigidBody, public List<Part>::Item
{
public:

   // Class Box
   class Box;

   // Class Cone
   class Cone;

   // Class Cylinder
   class Cylinder;

   // Class Prism
   class Prism;

   // Class Sphere
   class Sphere;

   // Constructor
   Part(void);

   // Copy Constructor
   Part(const Part& part);

   // Assign
   Part& operator =(const Part& part);

   // Clone
   virtual Part* clone(void) const = 0;

   // Material
   const Material& material(void) const;
   void material(const Material& material);

private:

   // Update Properties
   static const uint8_t _UPDATE_DIMENSION = 1;
   static const uint8_t _UPDATE_MATERIAL = 2;

   // Compute Mass
   virtual double _mass(void) const;

   // Update Property
   void _update(uint8_t update);

   // Variables
   Material _material;

   // Friends
   friend class Material;
};


// Constructor
inline CubeSim::Part::Part(void)
{
   // Initialize
   _material._part = this;
}


// Copy Constructor
inline CubeSim::Part::Part(const Part& part) : RigidBody(part), List<Part>::Item(part)
{
   // Initialize
   _material = part._material;
   _material._part = this;
}


// Get Material
inline const CubeSim::Material& CubeSim::Part::material(void) const
{
   // Return Material
   return _material;
}


// Set Material
inline void CubeSim::Part::material(const Material& material)
{
   // Set Material
   _material = material;
}


// Compute Mass
inline double CubeSim::Part::_mass(void) const
{
   // Compute Mass and return Result
   return (volume() * _material.density());
}
