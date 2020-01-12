

// CUBESIM - MATERIAL


// Includes
#include "color.hpp"
#include "exception.hpp"


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class Material
   class Material;
}


// Class Material
class CubeSim::Material
{
public:

   // Default Materials
   static const Material ALUMINUM;
   static const Material COPPER;
   static const Material EPOXY;
   static const Material FR4;
   static const Material NYLON;
   static const Material PEEK;
   static const Material PTFE;
   static const Material STEEL;

   // Constructor
   Material(double density = 0.0, const Color& color = Color::BLACK);

   // Color
   const Color& color(void) const;
   void color(const Color& color);

   // Density [kg/m^3]
   double density(void) const;
   void density(double density);

private:

   // Variables
   double _density;
   Color _color;
};


// Constructor
inline CubeSim::Material::Material(double density, const Color& color) : _color(color)
{
   // Initialize
   this->density(density);
}


// Get Color
inline const CubeSim::Color& CubeSim::Material::color(void) const
{
   // Return Color
   return _color;
}


// Set Color
inline void CubeSim::Material::color(const Color& color)
{
   // Set Color
   _color = color;
}


// Get Density [kg/m^3]
inline double CubeSim::Material::density(void) const
{
   // Return Density
   return _density;
}


// Set Density [kg/m^3]
inline void CubeSim::Material::density(double density)
{
   // Check Density
   if (density < 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Density
   _density = density;
}
