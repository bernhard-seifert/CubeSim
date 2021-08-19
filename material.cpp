

// CUBESIM - MATERIAL


// Includes
#include "material.hpp"
#include "part.hpp"


// Default Materials
const CubeSim::Material CubeSim::Material::ALUMINUM("Aluminum", 2700.0, Color(173, 178, 189));
const CubeSim::Material CubeSim::Material::COPPER("Copper", 8900.0, Color(192, 105, 53));
const CubeSim::Material CubeSim::Material::EPOXY("Epoxy Resin", 2400.0, Color(40, 40, 40));
const CubeSim::Material CubeSim::Material::FR4("FR4", 1850.0, Color(40, 80, 0));
const CubeSim::Material CubeSim::Material::NYLON("Nylon", 1150.0, Color(242, 242, 242));
const CubeSim::Material CubeSim::Material::PEEK("PEEK", 1310.0, Color(140, 120, 70));
const CubeSim::Material CubeSim::Material::PTFE("PTFE", 2320.0, Color(255, 255, 255));
const CubeSim::Material CubeSim::Material::STEEL("Steel", 8030.0, Color(224, 223, 219));


// Assign (Part is maintained)
CubeSim::Material& CubeSim::Material::operator =(const Material& material)
{
   // Check Material
   if (this != &material)
   {
      // Assign
      _density = material._density;
      _color = material._color;
      _name = material._name;
   }

   // Return Reference
   return *this;
}


// Set Density [kg/m^3]
void CubeSim::Material::density(double density)
{
   // Check Density
   if (density < 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Density
   _density = density;

   // Check for Part
   if (_part)
   {
      // Update Properties
      _part->_update(Part::_UPDATE_MATERIAL);
   }
}
