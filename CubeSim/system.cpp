

// CUBESIM - SYSTEM


// Includes
#include <typeinfo>
#include "spacecraft.hpp"


// Copy Constructor (Spacecraft and System References are reset)
CubeSim::System::System(const System& system) : Behavior(system), RigidBody(system), List<Assembly>(system),
   List<System>(system), List<System>::Item(system), _enabled(system._enabled), _spacecraft(), _system()
{
   // Parse Assembly List
   for (auto assembly = this->assembly().begin(); assembly != this->assembly().end(); ++assembly)
   {
      // Set Parent rigid Body
      assembly->second->_rigid_body = this;
   }

   // Parse System List
   for (auto system = this->system().begin(); system != this->system().end(); ++system)
   {
      // Set Parent System and Parent rigid Body
      system->second->_system = this;
      system->second->_rigid_body = this;
   }
}


// Assign (Spacecraft and System References are maintained)
CubeSim::System& CubeSim::System::operator =(const System& system)
{
   // Check System
   if (this != &system)
   {
      // Check Type to avoid Object Slicing
      if (typeid(*this) != typeid(system))
      {
         // Exception
         throw Exception::Parameter();
      }

      // Assign
      static_cast<Behavior&>(*this) = system;
      static_cast<RigidBody&>(*this) = system;
      static_cast<List<Assembly>&>(*this) = system;
      static_cast<List<System>&>(*this) = system;
      static_cast<List<System>::Item&>(*this) = system;

      // Parse Assembly List
      for (auto assembly = this->assembly().begin(); assembly != this->assembly().end(); ++assembly)
      {
         // Set Parent rigid Body
         assembly->second->_rigid_body = this;
      }

      // Parse System List
      for (auto system = this->system().begin(); system != this->system().end(); ++system)
      {
         // Set Parent rigid Body, Parent System, Spacecraft
         system->second->_rigid_body = this;
         system->second->_system = this;
         system->second->_spacecraft = nullptr;
      }
   }

   // Return Reference
   return *this;
}


// Get Simulation
CubeSim::Simulation* CubeSim::System::simulation(void) const
{
   // Get Spacecraft
   Spacecraft* spacecraft = this->spacecraft();

   // Return Simulation
   return (spacecraft ? spacecraft->simulation() : nullptr);
}


// Compute angular Momentum (Body Frame) [kg*m^2/s]
const CubeSim::Vector3D CubeSim::System::_angular_momentum(void) const
{
   // Angular Momentum
   Vector3D angular_momentum;

   // Parse Assembly List
   for (auto assembly = this->assembly().begin(); assembly != this->assembly().end(); ++assembly)
   {
      // Update angular Momentum
      angular_momentum += assembly->second->angular_momentum();
   }

   // Parse System List
   for (auto system = this->system().begin(); system != this->system().end(); ++system)
   {
      // Update angular Momentum
      angular_momentum += system->second->angular_momentum();
   }

   // Return angular Momentum
   return angular_momentum;
}


// Compute Surface Area [m^2]
double CubeSim::System::_area(void) const
{
   // Surface Area
   double area = 0.0;

   // Parse System List
   for (auto system = this->system().begin(); system != this->system().end(); ++system)
   {
      // Get System Surface Area and update Surface Area
      area += system->second->area();
   }

   // Parse Assembly List
   for (auto assembly = this->assembly().begin(); assembly != this->assembly().end(); ++assembly)
   {
      // Get Assembly Surface Area and update Surface Area
      area += assembly->second->area();
   }

   // Return Surface Area
   return area;
}


// Compute Center of Mass (Body Frame) [m]
const CubeSim::Vector3D CubeSim::System::_center(void) const
{
   // Mass, Center of Mass
   double mass = 0.0;
   Vector3D center;

   // Parse System List
   for (auto system = this->system().begin(); system != this->system().end(); ++system)
   {
      // Get System Mass
      double mass_ = system->second->mass();

      // Update Mass and Center of Mass
      mass += mass_;
      center += system->second->center() * mass_;
   }

   // Parse Assembly List
   for (auto assembly = this->assembly().begin(); assembly != this->assembly().end(); ++assembly)
   {
      // Get Assembly Mass
      double mass_ = assembly->second->mass();

      // Update Mass and Center of Mass
      mass += mass_;
      center += assembly->second->center() * mass_;
   }

   // Compute and return Center of Mass
   return ((mass == 0.0) ? Vector3D() : (center / mass));
}


// Check if contains Point (Body Frame)
bool CubeSim::System::_contains(const Vector3D& point) const
{
   // Parse System List
   for (auto system = this->system().begin(); system != this->system().end(); ++system)
   {
      // Check if contains Point
      if (system->second->contains(point))
      {
         // Return Result
         return true;
      }
   }

   // Parse Assembly List
   for (auto assembly = this->assembly().begin(); assembly != this->assembly().end(); ++assembly)
   {
      // Check if contains Point
      if (assembly->second->contains(point))
      {
         // Return Result
         return true;
      }
   }

   // Return Result
   return false;
}


// Compute Moment of Inertia (Body Frame) [kg*m^2]
const CubeSim::Inertia CubeSim::System::_inertia(void) const
{
   // Moment of Inertia
   Inertia I;

   // Parse System List
   for (auto system = this->system().begin(); system != this->system().end(); ++system)
   {
      // Update Moment of Inertia
      I += system->second->inertia();
   }

   // Parse Assembly List
   for (auto assembly = this->assembly().begin(); assembly != this->assembly().end(); ++assembly)
   {
      // Update Moment of Inertia
      I += assembly->second->inertia();
   }

   // Return Moment of Inertia
   return I;
}


// Compute Mass [kg]
double CubeSim::System::_mass(void) const
{
   // Mass
   double mass = 0.0;

   // Parse System List
   for (auto system = this->system().begin(); system != this->system().end(); ++system)
   {
      // Update Mass
      mass += system->second->mass();
   }

   // Parse Assembly List
   for (auto assembly = this->assembly().begin(); assembly != this->assembly().end(); ++assembly)
   {
      // Update Mass
      mass += assembly->second->mass();
   }

   // Return Mass
   return mass;
}


// Compute Momentum (Body Frame) [kg*m/s]
const CubeSim::Vector3D CubeSim::System::_momentum(void) const
{
   // Momentum
   Vector3D momentum;

   // Parse System List
   for (auto system = this->system().begin(); system != this->system().end(); ++system)
   {
      // Update Momentum
      momentum += system->second->momentum();
   }

   // Parse Assembly List
   for (auto assembly = this->assembly().begin(); assembly != this->assembly().end(); ++assembly)
   {
      // Update Momentum
      momentum += assembly->second->momentum();
   }

   // Return Momentum
   return momentum;
}


// Compute Volume [m^3]
double CubeSim::System::_volume(void) const
{
   // Volume
   double volume = 0.0;

   // Parse System List
   for (auto system = this->system().begin(); system != this->system().end(); ++system)
   {
      // Update Volume
      volume += system->second->volume();
   }

   // Parse Assembly List
   for (auto assembly = this->assembly().begin(); assembly != this->assembly().end(); ++assembly)
   {
      // Update Volume
      volume += assembly->second->volume();
   }

   // Return Volume
   return volume;
}


// Compute Wrench (Body Frame)
const CubeSim::Wrench CubeSim::System::_wrench(void) const
{
   // Wrench
   Wrench wrench = Wrench(force(), torque());

   // Parse System List
   for (auto system = this->system().begin(); system != this->system().end(); ++system)
   {
      // Update Wrench
      wrench += system->second->wrench();
   }

   // Parse Assembly List
   for (auto assembly = this->assembly().begin(); assembly != this->assembly().end(); ++assembly)
   {
      // Update Wrench
      wrench += assembly->second->wrench();
   }

   // Return Wrench
   return wrench;
}
