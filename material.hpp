

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

   // Class Part
   class Part;
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
   Material(const std::string& name = "", double density = 0.0, const Color& color = Color::BLACK);

   // Copy Constructor (Part is reset)
   Material(const Material& material);

   // Assign (Part is maintained)
   Material& operator =(const Material& material);

   // Color
   const Color& color(void) const;
   void color(const Color& color);

   // Density [kg/m^3]
   double density(void) const;
   void density(double density);

   // Name
   const std::string& name(void) const;
   void name(const std::string& name);

private:

   // Variables
   double _density;
   Color _color;
   std::string _name;
   Part* _part;

   // Friends
   friend class Part;
};


// Constructor
inline CubeSim::Material::Material(const std::string& name, double density, const Color& color) : _color(color),
   _name(name), _part()
{
   // Initialize
   this->density(density);
}


// Copy Constructor (Part is reset)
inline CubeSim::Material::Material(const Material& material) : _density(material._density), _color(material._color),
   _name(material._name), _part()
{
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


// Get Name
inline const std::string& CubeSim::Material::name(void) const
{
   // Return Name
   return _name;
}


// Set Name
inline void CubeSim::Material::name(const std::string& name)
{
   // Set Name
   _name = name;
}
