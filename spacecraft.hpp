

// CUBESIM - SPACECRAFT


// Includes
#include "behavior.hpp"
#include "celestial_body.hpp"
#include "orbit.hpp"
#include "system.hpp"


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class Spacecraft
   class Spacecraft;
}


// Class Spacecraft
class CubeSim::Spacecraft : public Behavior, public RigidBody, private List<System>, public List<Spacecraft>::Item
{
public:

   // Class Hubble
   class Hubble;

   // Class ISS
   class ISS;

   // Constructor
   Spacecraft(void);

   // Copy Constructor (Simulation Reference is reset)
   Spacecraft(const Spacecraft& spacecraft);

   // Assign (Simulation Reference is maintained)
   Spacecraft& operator =(const Spacecraft& spacecraft);

   // Insert System, Force and Torque
   void insert(const std::string& name, const System& system);
   using RigidBody::insert;

   // Compute Orbit
   const Orbit orbit(const CelestialBody& central, const Rotation& reference = Orbit::REFERENCE_ECLIPTIC) const;

   // Get Simulation
   Simulation* simulation(void) const;

   // Get System
   const std::map<std::string, System*>& system(void) const;
   System* system(const std::string& name) const;

private:

   // Constructor (Vector Constants might not yet be initialized)
   Spacecraft(const Vector3D& position, const Vector3D& velocity, const Vector3D& angular_rate = Vector3D(),
      const Rotation& rotation = Rotation(Vector3D(0.0, 0.0, 1.0), 0.0));

   // Compute angular Momentum (Body Frame) [kg*m^2/s]
   virtual const Vector3D _angular_momentum(void) const;

   // Compute Surface Area [m^2]
   virtual double _area(void) const;

   // Compute Center of Mass (Body Frame) [m]
   virtual const Vector3D _center(void) const;

   // Check if Point is inside (Body Frame)
   virtual bool _contains(const Vector3D& point) const;

   // Compute Momentum of Inertia (Body Frame) [kg*m^2]
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
   Simulation* _simulation;

   // Friends
   friend class Simulation;
};


// Constructor
inline CubeSim::Spacecraft::Spacecraft(void) : _simulation()
{
}


// Constructor
inline CubeSim::Spacecraft::Spacecraft(const Vector3D& position, const Vector3D& velocity, const Vector3D& angular_rate,
   const Rotation& rotation) : RigidBody(position, rotation, velocity, angular_rate), _simulation()
{
}


// Insert System
inline void CubeSim::Spacecraft::insert(const std::string& name, const System& system)
{
   // Insert System
   System& system_ = List<System>::insert(name, system);

   // Set parent Rigid Body, parent System, Spacecraft
   system_._rigid_body = this;
   system_._system = NULL;
   system_._spacecraft = this;
}


// Compute Orbit
inline const CubeSim::Orbit CubeSim::Spacecraft::orbit(const CelestialBody& central, const Rotation& reference) const
{
   // Compute and return Orbit
   return Orbit(central, *this, reference);
}


// Get Simulation
inline CubeSim::Simulation* CubeSim::Spacecraft::simulation(void) const
{
   // Return Simulation
   return _simulation;
}


// Get System List
inline const std::map<std::string, CubeSim::System*>& CubeSim::Spacecraft::system(void) const
{
   // Return System List
   return List<System>::item();
}


// Get System
inline CubeSim::System* CubeSim::Spacecraft::system(const std::string& name) const
{
   // Return System List
   return List<System>::item(name);
}
