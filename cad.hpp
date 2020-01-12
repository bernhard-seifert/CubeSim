

// CUBESIM - CAD


// Includes
#include "celestial_body.hpp"
#include "spacecraft.hpp"


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class CAD
   class CAD;
}


// Class CAD
class CubeSim::CAD
{
public:

   // Export Code
   const std::string code(void) const;

   // Insert Item
   void operator +=(const Assembly& assembly);
   void operator +=(const CelestialBody& celestial_body);
   void operator +=(const Part& part);
   void operator +=(const Spacecraft& spacecraft);
   void operator +=(const System& system);
   void insert(const Assembly& assembly);
   void insert(const CelestialBody& celestial_body);
   void insert(const Part& part);
   void insert(const Spacecraft& spacecraft);
   void insert(const System& system);

private:

   // Export Code
   const std::string _code(const Assembly& assembly) const;
   const std::string _code(const CelestialBody& celestial_body) const;
   const std::string _code(const Part& part) const;
   const std::string _code(const Spacecraft& spacecraft) const;
   const std::string _code(const System& system) const;

   // Transform Item
   const std::string _transform(const std::string& code, const Vector3D& position,
      const Rotation& rotation = Rotation()) const;

   // Variables
   std::vector<const Assembly*> _assembly;
   std::vector<const CelestialBody*> _celestial_body;
   std::vector<const Part*> _part;
   std::vector<const Spacecraft*> _spacecraft;
   std::vector<const System*> _system;
};


// Insert Assembly
inline void CubeSim::CAD::operator +=(const Assembly& assembly)
{
   // Insert Assembly
   insert(assembly);
}


// Insert Celestial Body
inline void CubeSim::CAD::operator +=(const CelestialBody& celestial_body)
{
   // Insert Celestial Body
   insert(celestial_body);
}


// Insert Part
inline void CubeSim::CAD::operator +=(const Part& part)
{
   // Insert Part
   insert(part);
}


// Insert Spacecraft
inline void CubeSim::CAD::operator +=(const Spacecraft& spacecraft)
{
   // Insert Spacecraft
   insert(spacecraft);
}


// Insert System
inline void CubeSim::CAD::operator +=(const System& system)
{
   // Insert System
   insert(system);
}


// Insert Celestial Body
inline void CubeSim::CAD::insert(const CelestialBody& celestial_body)
{
   // Insert Celestial Body into List
   _celestial_body.push_back(&celestial_body);
}


// Insert Assembly
inline void CubeSim::CAD::insert(const Assembly& assembly)
{
   // Insert Assembly into List
   _assembly.push_back(&assembly);
}


// Insert Part
inline void CubeSim::CAD::insert(const Part& part)
{
   // Insert Part into List
   _part.push_back(&part);
}


// Insert Spacecraft
inline void CubeSim::CAD::insert(const Spacecraft& spacecraft)
{
   // Insert Spacecraft into List
   _spacecraft.push_back(&spacecraft);
}


// Insert System
inline void CubeSim::CAD::insert(const System& system)
{
   // Insert System into List
   _system.push_back(&system);
}
