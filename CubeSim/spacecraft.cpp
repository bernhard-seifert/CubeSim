

// CUBESIM - SPACECRAFT


// Includes
#include "simulation.hpp"
#include "spacecraft.hpp"


// Copy Constructor (Simulation Reference is reset)
CubeSim::Spacecraft::Spacecraft(const Spacecraft& spacecraft) : Behavior(spacecraft), RigidBody(spacecraft),
   List<System>(spacecraft), List<Spacecraft>::Item(spacecraft), _simulation()
{
   // Parse System List
   for (auto system = this->system().begin(); system != this->system().end(); ++system)
   {
      // Set Parent rigid Body and Spacecraft
      system->second->_spacecraft = this;
      system->second->_rigid_body = this;
   }
}


// Assign (Simulation Reference is maintained)
CubeSim::Spacecraft& CubeSim::Spacecraft::operator =(const Spacecraft& spacecraft)
{
   // Check Spacecraft
   if (this != &spacecraft)
   {
      // Check Type to avoid Object Slicing
      if (typeid(*this) != typeid(spacecraft))
      {
         // Exception
         throw Exception::Parameter();
      }

      // Assign
      static_cast<Behavior&>(*this) = spacecraft;
      static_cast<RigidBody&>(*this) = spacecraft;
      static_cast<List<System>&>(*this) = spacecraft;
      static_cast<List<Spacecraft>::Item&>(*this) = spacecraft;

      // Parse System List
      for (auto system = this->system().begin(); system != this->system().end(); ++system)
      {
         // Set Parent rigid Body and Spacecraft
         system->second->_rigid_body = this;
         system->second->_spacecraft = this;
      }
   }

   // Return Reference
   return *this;
}


// Compute angular Momentum (Body Frame) [kg*m^2/s]
const CubeSim::Vector3D CubeSim::Spacecraft::_angular_momentum(void) const
{
   // Angular Momentum
   Vector3D angular_momentum;

   // Parse System List
   for (auto system = this->system().begin(); system != this->system().end(); ++system)
   {
      // Update angular Momentum
      angular_momentum += system->second->angular_momentum();
   }

   // Return Momentum
   return angular_momentum;
}


// Compute Surface Area [m^2]
double CubeSim::Spacecraft::_area(void) const
{
   // Surface Area
   double area = 0.0;

   // Parse System List
   for (auto system = this->system().begin(); system != this->system().end(); ++system)
   {
      // Get System Surface Area and update Surface Area
      area += system->second->area();
   }

   // Return Surface Area
   return area;
}


// Compute Center of Mass (Body Frame) [m]
const CubeSim::Vector3D CubeSim::Spacecraft::_center(void) const
{
   // Mass, Center of Mass
   double mass = 0.0;
   Vector3D center;

   // Parse Systems
   for (auto system = this->system().begin(); system != this->system().end(); ++system)
   {
      // Compute Mass
      double mass_ = system->second->mass();

      // Update Mass and Center of Mass
      mass += mass_;
      center += system->second->center() * mass_;
   }

   // Compute and return Center of Mass
   return ((mass == 0.0) ? Vector3D() : (center / mass));
}


// Check if Point is inside (Body Frame)
bool CubeSim::Spacecraft::_contains(const Vector3D& point) const
{
   // Parse Systems
   for (auto system = this->system().begin(); system != this->system().end(); ++system)
   {
      // Check if Point is inside
      if (system->second->contains(point))
      {
         // Return Result
         return true;
      }
   }

   // Return Result
   return false;
}


// Compute Moment of Inertia (Body Frame) [kg*m^2]
const CubeSim::Inertia CubeSim::Spacecraft::_inertia(void) const
{
   // Moment of Inertia
   Inertia I;

   // Parse Systems
   for (auto system = this->system().begin(); system != this->system().end(); ++system)
   {
      // Update Moment of Inertia
      I += system->second->inertia();
   }

   // Return Moment of Inertia
   return I;
}


// Compute Mass [kg]
double CubeSim::Spacecraft::_mass(void) const
{
   // Mass
   double mass = 0.0;

   // Parse Systems
   for (auto system = this->system().begin(); system != this->system().end(); ++system)
   {
      // Update Mass
      mass += system->second->mass();
   }

   // Return Mass
   return mass;
}


// Compute Momentum (Body Frame) [kg*m/s]
const CubeSim::Vector3D CubeSim::Spacecraft::_momentum(void) const
{
   // Momentum
   Vector3D momentum;

   // Parse System List
   for (auto system = this->system().begin(); system != this->system().end(); ++system)
   {
      // Update Momentum
      momentum += system->second->momentum();
   }

   // Return Momentum
   return momentum;
}


// Compute Volume [m^3]
double CubeSim::Spacecraft::_volume(void) const
{
   // Volume
   double volume = 0.0;

   // Parse System List
   for (auto system = this->system().begin(); system != this->system().end(); ++system)
   {
      // Update Volume
      volume += system->second->volume();
   }

   // Return Volume
   return volume;
}


// Compute Wrench (Body Frame)
const CubeSim::Wrench CubeSim::Spacecraft::_wrench(void) const
{
   // Wrench
   Wrench wrench = Wrench(force(), torque());

   // Parse System List
   for (auto system = this->system().begin(); system != this->system().end(); ++system)
   {
      // Update Wrench
      wrench += system->second->wrench();
   }

   // Return Wrench
   return wrench;
}
