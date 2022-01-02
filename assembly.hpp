

// CUBESIM - ASSEMBLY


// Includes
#include "part.hpp"


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class Assembly
   class Assembly;
}


// Class Assembly
class CubeSim::Assembly : public RigidBody, private List<Assembly>, private List<Part>, public List<Assembly>::Item
{
public:

   // Constructor
   Assembly(void);

   // Copy Constructor
   Assembly(const Assembly& assembly);

   // Assign
   Assembly& operator =(const Assembly& assembly);

   // Get Assembly
   const std::map<std::string, Assembly*>& assembly(void) const;
   Assembly* assembly(const std::string& name) const;

   // Insert Assembly, Part, Force (Body Frame) and Torque (Body Frame)
   Assembly& insert(const std::string& name, const Assembly& assembly);
   Part& insert(const std::string& name, const Part& part);
   using RigidBody::insert;

   // Get Part
   const std::map<std::string, Part*>& part(void) const;
   Part* part(const std::string& name) const;

private:

   // Compute angular Momentum (Body Frame) [kg*m^2/s]
   virtual const Vector3D _angular_momentum(void) const;

   // Compute Surface Area [m^2]
   virtual double _area(void) const;

   // Compute Center of Mass (Body Frame) [m]
   virtual const Vector3D _center(void) const;

   // Check if Point is inside (Body Frame)
   virtual bool _contains(const Vector3D& point) const;

   // Compute Moment of Inertia (Body Frame) [kg*m^2]
   virtual const Inertia _inertia(void) const;

   // Compute Mass [kg]
   virtual double _mass(void) const;

   // Compute Momentum (Body Frame) [kg*m/s]
   virtual const Vector3D _momentum(void) const;

   // Compute Volume [m^3]
   virtual double _volume(void) const;

   // Compute Wrench (Body Frame)
   virtual const Wrench _wrench(void) const;
};


// Constructor
inline CubeSim::Assembly::Assembly(void)
{
}


// Get Assembly List
inline const std::map<std::string, CubeSim::Assembly*>& CubeSim::Assembly::assembly(void) const
{
   // Return Assembly List
   return List<Assembly>::item();
}


// Get Assembly
inline CubeSim::Assembly* CubeSim::Assembly::assembly(const std::string& name) const
{
   // Return Assembly
   return List<Assembly>::item(name);
}


// Insert Assembly
inline CubeSim::Assembly& CubeSim::Assembly::insert(const std::string& name, const Assembly& assembly)
{
   // Insert Assembly
   Assembly& assembly_ = List<Assembly>::insert(name, assembly);

   // Set Parent rigid Body
   assembly_._rigid_body = this;

   // Return Reference
   return assembly_;
}


// Insert Part
inline CubeSim::Part& CubeSim::Assembly::insert(const std::string& name, const Part& part)
{
   // Insert Part
   Part& part_ = List<Part>::insert(name, part);

   // Set Parent rigid Body
   part_._rigid_body = this;

   // Return Reference
   return part_;
}


// Get Part List
inline const std::map<std::string, CubeSim::Part*>& CubeSim::Assembly::part(void) const
{
   // Return Part List
   return List<Part>::item();
}


// Get Part
inline CubeSim::Part* CubeSim::Assembly::part(const std::string& name) const
{
   // Return Part
   return List<Part>::item(name);
}
