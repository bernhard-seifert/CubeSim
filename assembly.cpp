

// CUBESIM - ASSEMBLY


// Includes
#include "assembly.hpp"


// Copy Constructor
CubeSim::Assembly::Assembly(const Assembly& assembly) : RigidBody(assembly), List<Assembly>(assembly),
   List<Part>(assembly), List<Assembly>::Item(assembly)
{
   // Parse Assembly List
   for (auto assembly = this->assembly().begin(); assembly != this->assembly().end(); ++assembly)
   {
      // Set parent Rigid Body
      assembly->second->_rigid_body = this;
   }

   // Parse Part List
   for (auto part = this->part().begin(); part != this->part().end(); ++part)
   {
      // Set parent Rigid Body
      part->second->_rigid_body = this;
   }
}


// Assign
CubeSim::Assembly& CubeSim::Assembly::operator =(const Assembly& assembly)
{
   // Assign
   static_cast<RigidBody&>(*this) = assembly;
   static_cast<List<Assembly>&>(*this) = assembly;
   static_cast<List<Part>&>(*this) = assembly;
   static_cast<List<Assembly>::Item&>(*this) = assembly;

   // Parse Assembly List
   for (auto assembly = this->assembly().begin(); assembly != this->assembly().end(); ++assembly)
   {
      // Set parent Rigid Body
      assembly->second->_rigid_body = this;
   }

   // Parse Part List
   for (auto part = this->part().begin(); part != this->part().end(); ++part)
   {
      // Set parent Rigid Body
      part->second->_rigid_body = this;
   }

   // Return Reference
   return *this;
}


// Compute angular Momentum (Body Frame) [kg*m^2/s]
const CubeSim::Vector3D CubeSim::Assembly::_angular_momentum(void) const
{
   // Angular Momentum
   Vector3D angular_momentum;

   // Parse Assembly List
   for (auto assembly = this->assembly().begin(); assembly != this->assembly().end(); ++assembly)
   {
      // Update angular Momentum
      angular_momentum += assembly->second->angular_momentum();
   }

   // Parse Part List
   for (auto part = this->part().begin(); part != this->part().end(); ++part)
   {
      // Update angular Momentum
      angular_momentum += part->second->angular_momentum();
   }

   // Return angular Momentum
   return angular_momentum;
}


// Compute Surface Area [m^2]
double CubeSim::Assembly::_area(void) const
{
   // Surface Area
   double area = 0.0;

   // Parse Assembly List
   for (auto assembly = this->assembly().begin(); assembly != this->assembly().end(); ++assembly)
   {
      // Get Assembly Surface Area and update Surface Area
      area += assembly->second->area();
   }

   // Parse Part List
   for (auto part = this->part().begin(); part != this->part().end(); ++part)
   {
      // Get Part Surface Area and update Surface Area
      area += part->second->area();
   }

   // Return Surface Area
   return area;
}


// Compute Center of Mass (Body Frame) [m]
const CubeSim::Vector3D CubeSim::Assembly::_center(void) const
{
   // Mass, Center of Mass
   double mass = 0.0;
   Vector3D center;

   // Parse Assembly List
   for (auto assembly = this->assembly().begin(); assembly != this->assembly().end(); ++assembly)
   {
      // Get Assembly Mass
      double mass_ = assembly->second->mass();

      // Update Mass and Center of Mass
      mass += mass_;
      center += assembly->second->center() * mass_;
   }

   // Parse Part List
   for (auto part = this->part().begin(); part != this->part().end(); ++part)
   {
      // Get Part Mass
      double mass_ = part->second->mass();

      // Update Mass and Center of Mass
      mass += mass_;
      center += part->second->center() * mass_;
   }

   // Compute and return Center of Mass
   return ((mass == 0.0) ? Vector3D() : (center / mass));
}


// Check if contains Point (Body Frame)
bool CubeSim::Assembly::_contains(const Vector3D& point) const
{
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

   // Parse Part List
   for (auto part = this->part().begin(); part != this->part().end(); ++part)
   {
      // Check if contains Point
      if (part->second->contains(point))
      {
         // Return Result
         return true;
      }
   }

   // Return Result
   return false;
}


// Compute Moment of Inertia (Body Frame) [kg*m^2]
const CubeSim::Inertia CubeSim::Assembly::_inertia(void) const
{
   // Moment of Inertia
   Inertia I;

   // Parse Assembly List
   for (auto assembly = this->assembly().begin(); assembly != this->assembly().end(); ++assembly)
   {
      // Update Moment of Inertia
      I += assembly->second->inertia();
   }

   // Parse Part List
   for (auto part = this->part().begin(); part != this->part().end(); ++part)
   {
      // Update Moment of Inertia
      I += part->second->inertia();
   }

   // Return Moment of Inertia
   return I;
}


// Compute Mass [kg]
double CubeSim::Assembly::_mass(void) const
{
   // Mass
   double mass = 0.0;

   // Parse Assembly List
   for (auto assembly = this->assembly().begin(); assembly != this->assembly().end(); ++assembly)
   {
      // Get Assembly Mass and update Mass
      mass += assembly->second->mass();
   }

   // Parse Part List
   for (auto part = this->part().begin(); part != this->part().end(); ++part)
   {
      // Get Part Mass and update Mass
      mass += part->second->mass();
   }

   // Return Mass
   return mass;
}


// Compute Momentum (Body Frame) [kg*m/s]
const CubeSim::Vector3D CubeSim::Assembly::_momentum(void) const
{
   // Momentum
   Vector3D momentum;

   // Parse Assembly List
   for (auto assembly = this->assembly().begin(); assembly != this->assembly().end(); ++assembly)
   {
      // Update Momentum
      momentum += assembly->second->momentum();
   }

   // Parse Part List
   for (auto part = this->part().begin(); part != this->part().end(); ++part)
   {
      // Update Momentum
      momentum += part->second->momentum();
   }

   // Return Momentum
   return momentum;
}


// Compute Volume [m^3]
double CubeSim::Assembly::_volume(void) const
{
   // Volume
   double volume = 0.0;

   // Parse Assembly List
   for (auto assembly = this->assembly().begin(); assembly != this->assembly().end(); ++assembly)
   {
      // Get Assembly Volume and update Volume
      volume += assembly->second->volume();
   }

   // Parse Part List
   for (auto part = this->part().begin(); part != this->part().end(); ++part)
   {
      // Get Part Volume and update Volume
      volume += part->second->volume();
   }

   // Return Volume
   return volume;
}


// Compute Wrench (Body Frame)
const CubeSim::Wrench CubeSim::Assembly::_wrench(void) const
{
   // Wrench
   Wrench wrench = Wrench(force(), torque());

   // Parse Assembly List
   for (auto assembly = this->assembly().begin(); assembly != this->assembly().end(); ++assembly)
   {
      // Update Wrench
      wrench += assembly->second->wrench();
   }

   // Parse Part List
   for (auto part = this->part().begin(); part != this->part().end(); ++part)
   {
      // Update Wrench
      wrench += part->second->wrench();
   }

   // Return Wrench
   return wrench;
}
