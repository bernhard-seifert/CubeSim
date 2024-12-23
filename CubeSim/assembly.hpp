

// CUBESIM - ASSEMBLY


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

   // Update Properties
   _update(_UPDATE_AREA);
   _update(_UPDATE_CENTER);
   _update(_UPDATE_VOLUME);
   _update(_UPDATE_WRENCH);

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

   // Update Properties
   _update(_UPDATE_AREA);
   _update(_UPDATE_CENTER);
   _update(_UPDATE_VOLUME);
   _update(_UPDATE_WRENCH);

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
