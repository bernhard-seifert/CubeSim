

// CUBESIM - WRENCH


// Includes
#include "wrench.hpp"


// Constructor
CubeSim::Wrench::Wrench(const std::map<std::string, Force*>& force, const std::map<std::string, Torque*>& torque,
   double mass, const Vector3D& center)
{
   // Initialize
   this->mass(mass);
   _force.point(center);

   // Parse Force List
   for (auto force_ = force.begin(); force_ != force.end(); ++force_)
   {
      // Update Force and Torque
      _force += *force_->second;
      _torque += (force_->second->point() - center) ^ *force_->second;
   }

   // Parse Torque List
   for (auto torque_ = torque.begin(); torque_ != torque.end(); ++torque_)
   {
      // Update Torque
      _torque += *torque_->second;
   }
}


// Add and assign
CubeSim::Wrench& CubeSim::Wrench::operator +=(const Wrench& wrench)
{
   // Compute Mass
   double mass = _mass + wrench._mass;

   // Check Mass
   if (mass == 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Compute Center
   Vector3D center = (_force.point() * _mass + wrench._force.point() * wrench._mass) / mass;

   // Update Torque
   _torque += wrench._torque + ((_force.point() - center) ^ _force) +
      ((wrench._force.point() - center) ^ wrench._force);

   // Update Force
   _force += wrench._force;
   _force.point(center);

   // Update Mass
   _mass += wrench._mass;

   // Return Reference
   return *this;
}
