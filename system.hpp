

// CUBESIM - SYSTEM


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
#include "assembly.hpp"
#include "behavior.hpp"


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class Simulation
   class Simulation;

   // Class Spacecraft
   class Spacecraft;

   // Class System
   class System;
}


// Class System
class CubeSim::System : public Behavior, public RigidBody, private List<Assembly>, private List<System>,
   public List<System>::Item
{
public:

   // Accelerometer
   class Accelerometer;

   // Class GNSS
   class GNSS;

   // Class Gyroscope
   class Gyroscope;

   // Class Magnetometer
   class Magnetometer;

   // Class Magnetorquer
   class Magnetorquer;

   // Class Photodetector
   class Photodetector;

   // Class ReactionWheel
   class ReactionWheel;

   // Class Thruster
   class Thruster;

   // Constructor
   System(void);

   // Copy Constructor (Spacecraft and System References are reset)
   System(const System& system);

   // Assign (Spacecraft and System References are maintained)
   System& operator =(const System& system);

   // Get Assembly
   const std::map<std::string, Assembly*>& assembly(void) const;
   Assembly* assembly(const std::string& name) const;

   // Clone
   virtual System* clone(void) const;

   // Disable
   void disable(void);

   // Enable
   void enable(void);

   // Insert Assembly, System, Force (Body Frame) and Torque (Body Frame)
   Assembly& insert(const std::string& name, const Assembly& assembly);
   System& insert(const std::string& name, const System& system);
   using RigidBody::insert;

   // Check if enabled
   bool is_enabled(void) const;

   // Get Simulation
   Simulation* simulation(void) const;

   // Get Spacecraft
   Spacecraft* spacecraft(void) const;

   // Get System
   const std::map<std::string, System*>& system(void) const;
   System* system(const std::string& name) const;

private:

   // Compute angular Momentum (Body Frame) [kg*m^2/s]
   virtual const Vector3D _angular_momentum(void) const;

   // Compute Surface Area [m^2]
   virtual double _area(void) const;

   // Compute Center of Mass (Body Frame) [m]
   virtual const Vector3D _center(void) const;

   // Check if contains Point (Body Frame)
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

   // Variables
   bool _enabled;
   Spacecraft* _spacecraft;
   System* _system;

   // Friends
   friend class Spacecraft;
};


// Constructor
inline CubeSim::System::System(void) : _enabled(true), _spacecraft(), _system()
{
}


// Get Assembly List
inline const std::map<std::string, CubeSim::Assembly*>& CubeSim::System::assembly(void) const
{
   // Return Assembly List
   return List<Assembly>::item();
}


// Get Assembly
inline CubeSim::Assembly* CubeSim::System::assembly(const std::string& name) const
{
   // Return Assembly
   return List<Assembly>::item(name);
}


// Clone
inline CubeSim::System* CubeSim::System::clone(void) const
{
   // Return Copy
   return new System(*this);
}


// Disable
inline void CubeSim::System::disable(void)
{
   // Clear enabled Flag
   _enabled = false;
}


// Enable
inline void CubeSim::System::enable(void)
{
   // Set enabled Flag
   _enabled = true;
}


// Insert Assembly
inline CubeSim::Assembly& CubeSim::System::insert(const std::string& name, const Assembly& assembly)
{
   // Insert Assembly
   Assembly& assembly_ = List<Assembly>::insert(name, assembly);

   // Set Parent Rigid Body
   assembly_._rigid_body = this;

   // Update Properties
   _update(_UPDATE_AREA);
   _update(_UPDATE_CENTER);
   _update(_UPDATE_VOLUME);
   _update(_UPDATE_WRENCH);

   // Return Reference
   return assembly_;
}


// Insert System
inline CubeSim::System& CubeSim::System::insert(const std::string& name, const System& system)
{
   // Insert System
   System& system_ = List<System>::insert(name, system);

   // Set Parent Rigid Body and Parent System
   system_._rigid_body = this;
   system_._system = this;

   // Update Properties
   _update(_UPDATE_AREA);
   _update(_UPDATE_CENTER);
   _update(_UPDATE_VOLUME);
   _update(_UPDATE_WRENCH);

   // Return Reference
   return system_;
}


// Check if enabled
inline bool CubeSim::System::is_enabled(void) const
{
   // Return enabled Flag
   return _enabled;
}


// Get Spacecraft
inline CubeSim::Spacecraft* CubeSim::System::spacecraft(void) const
{
   // Return Spacecraft
   return (_system ? _system->spacecraft() : _spacecraft);
}


// Get System List
inline const std::map<std::string, CubeSim::System*>& CubeSim::System::system(void) const
{
   // Return System List
   return List<System>::item();
}


// Get System
inline CubeSim::System* CubeSim::System::system(const std::string& name) const
{
   // Return System
   return List<System>::item(name);
}
