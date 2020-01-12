

// CUBESIM - WRENCH


// Includes
#include "force.hpp"
#include "torque.hpp"


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class Wrench
   class Wrench;

   // Scale
   const Wrench operator *(double factor, const Wrench& wrench);
}


// Class Wrench
class CubeSim::Wrench
{
public:

   // Constructor
   Wrench(void);
   Wrench(const Force& force, const Torque& torque, double mass);
   Wrench(const std::map<std::string, Force*>& force, const std::map<std::string, Torque*>& torque, double mass = 0.0,
      const Vector3D& center = Vector3D());

   // Sign
   const Wrench& operator +(void) const;
   const Wrench operator -(void) const;

   // Scale
   const Wrench operator *(double factor) const;
   Wrench& operator *=(double factor);
   Wrench operator /(double factor) const;
   Wrench& operator /=(double factor);

   // Add
   const Wrench operator +(const Wrench& wrench) const;
   Wrench& operator +=(const Wrench& wrench);

   // Translate [m]
   const Wrench operator +(const Vector3D& distance) const;
   const Wrench operator -(const Vector3D& distance) const;
   Wrench& operator +=(const Vector3D& distance);
   Wrench& operator -=(const Vector3D& distance);

   // Rotate
   const Wrench operator +(const Rotation& rotation) const;
   const Wrench operator -(const Rotation& rotation) const;
   Wrench& operator +=(const Rotation& rotation);
   Wrench& operator -=(const Rotation& rotation);

   // Force [N]
   const Force& force(void) const;
   void force(double x, double y, double z);
   void force(const Force& force);

   // Mass [kg]
   double mass(void) const;
   void mass(double mass);

   // Torque [N*m]
   const Torque& torque(void) const;
   void torque(double x, double y, double z);
   void torque(const Torque& torque);

private:

   // Variables
   double _mass;
   Force _force;
   Torque _torque;
};


// Constructor
inline CubeSim::Wrench::Wrench(void) : _mass()
{
}


// Constructor
inline CubeSim::Wrench::Wrench(const Force& force, const Torque& torque, double mass)
{
   // Initialize
   this->force(force);
   this->torque(torque);
   this->mass(mass);
}


// Plus Sign
inline const CubeSim::Wrench& CubeSim::Wrench::operator +(void) const
{
   // Return Reference
   return *this;
}


// Minus Sign
inline const CubeSim::Wrench CubeSim::Wrench::operator -(void) const
{
   // Return Result
   return Wrench(-_force, -_torque, _mass);
}


// Scale
inline const CubeSim::Wrench CubeSim::Wrench::operator *(double factor) const
{
   // Scale, assign and return Result
   return (Wrench(*this) *= factor);
}


// Scale
inline CubeSim::Wrench CubeSim::Wrench::operator /(double factor) const
{
   // Scale, assign and return Result
   return (Wrench(*this) /= factor);
}


// Scale and assign
inline CubeSim::Wrench& CubeSim::Wrench::operator *=(double factor)
{
   // Scale and assign
   _force *= factor;
   _torque *= factor;

   // Return Reference
   return *this;
}


// Scale and assign
inline CubeSim::Wrench& CubeSim::Wrench::operator /=(double factor)
{
   // Scale and assign
   _force /= factor;
   _torque /= factor;

   // Return Reference
   return *this;
}


// Add
inline const CubeSim::Wrench CubeSim::Wrench::operator +(const Wrench& wrench) const
{
   // Add, assign and return Result
   return (Wrench(*this) += wrench);
}


// Translate [m]
inline const CubeSim::Wrench CubeSim::Wrench::operator +(const Vector3D& distance) const
{
   // Translate, assign and return Result
   return (Wrench(*this) += distance);
}


// Translate [m]
inline const CubeSim::Wrench CubeSim::Wrench::operator -(const Vector3D& distance) const
{
   // Translate, assign and return Result
   return (Wrench(*this) -= distance);
}


// Translate and assign [m]
inline CubeSim::Wrench& CubeSim::Wrench::operator +=(const Vector3D& distance)
{
   // Update Force
   _force += distance;

   // Return Reference
   return *this;
}


// Translate and assign [m]
inline CubeSim::Wrench& CubeSim::Wrench::operator -=(const Vector3D& distance)
{
   // Update Force
   _force -= distance;

   // Return Reference
   return *this;
}


// Rotate
inline const CubeSim::Wrench CubeSim::Wrench::operator +(const Rotation& rotation) const
{
   // Rotate, assign and return Result
   return (Wrench(*this) += rotation);
}


// Rotate
inline const CubeSim::Wrench CubeSim::Wrench::operator -(const Rotation& rotation) const
{
   // Rotate, assign and return Result
   return (Wrench(*this) -= rotation);
}


// Rotate and assign
inline CubeSim::Wrench& CubeSim::Wrench::operator +=(const Rotation& rotation)
{
   // Rotate and assign
   _force += rotation;
   _torque += rotation;

   // Return Reference
   return *this;
}


// Rotate and assign
inline CubeSim::Wrench& CubeSim::Wrench::operator -=(const Rotation& rotation)
{
   // Rotate and assign
   _force -= rotation;
   _torque -= rotation;

   // Return Reference
   return *this;
}


// Get Force [N]
inline const CubeSim::Force& CubeSim::Wrench::force(void) const
{
   // Return Force
   return _force;
}


// Set Force [N]
inline void CubeSim::Wrench::force(double x, double y, double z)
{
   // Set Force
   force(Force(x, y, z));
}


// Set Force [N]
inline void CubeSim::Wrench::force(const Force& force)
{
   // Set Force
   _force = force;
}


// Get Torque [N*m]
inline const CubeSim::Torque& CubeSim::Wrench::torque(void) const
{
   // Return Torque
   return _torque;
}


// Set Torque [N*m]
inline void CubeSim::Wrench::torque(double x, double y, double z)
{
   // Set Torque
   torque(Torque(x, y, z));
}


// Set Torque [N*m]
inline void CubeSim::Wrench::torque(const Torque& torque)
{
   // Set Torque
   _torque = torque;
}


// Get Mass [kg]
inline double CubeSim::Wrench::mass(void) const
{
   // Return Mass
   return _mass;
}


// Set Mass [kg]
inline void CubeSim::Wrench::mass(double mass)
{
   // Check Mass
   if (mass < 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Mass
   _mass = mass;
}


// Scale
inline const CubeSim::Wrench CubeSim::operator *(double factor, const Wrench& wrench)
{
   // Scale and return Result
   return (wrench * factor);
}
