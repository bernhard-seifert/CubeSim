

// CUBESIM - RIGID BODY


// Includes
#include "inertia.hpp"
#include "wrench.hpp"


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class RigidBody
   class RigidBody;
}


// Class RigidBody
class CubeSim::RigidBody : private List<Force>, private List<Torque>
{
public:

   // Constructor
   RigidBody(void);
   RigidBody(const Vector3D& position, const Rotation& rotation);
   RigidBody(const Vector3D& position, const Rotation& rotation, const Vector3D& velocity,
      const Vector3D& angular_rate);

   // Copy Constructor (Rigid Body Reference is reset)
   RigidBody(const RigidBody& rigid_body);

   // Assign (Rigid Body Reference is maintained)
   RigidBody& operator =(const RigidBody& rigid_body);

   // Compute angular Momentum (local Frame) [kg*m^2/s]
   const Vector3D angular_momentum(void) const;

   // Angular Rate (local Frame) [rad/s]
   const Vector3D& angular_rate(void) const;
   void angular_rate(double x, double y, double z);
   void angular_rate(const Vector3D& angular_rate);

   // Compute Surface Area [m^2]
   double area(void) const;

   // Compute Center of Mass (local Frame) [m]
   const Vector3D center(void) const;

   // Check if contains Point (local Frame)
   bool contains(double x, double y, double z) const;
   bool contains(const Vector3D& point) const;

   // Get Force (Body Frame) [N]
   const std::map<std::string, Force*>& force(void) const;
   Force* force(const std::string& name) const;

   // Compute Moment of Inertia (local Frame) [kg*m^2] *** if no parent -> return inertia in body frame?
   const Inertia inertia(void) const;

   // Insert Force (Body Frame) and Torque (Body Frame)
   void insert(const std::string& name, const Force& force);
   void insert(const std::string& name, const Torque& torque);

   // Locate in global Frame
   const std::pair<Vector3D, Rotation> locate(void) const;

   // Compute Mass [kg]
   double mass(void) const;

   // Compute Momentum (local Frame) [kg*m/s]
   const Vector3D momentum(void) const;

   // Move (local Frame) [m]
   void move(double x, double y, double z);
   void move(const Vector3D& distance);

   // Position (local Frame) [m]
   const Vector3D& position(void) const;
   void position(double x, double y, double z);
   void position(const Vector3D& position);

   // Rotate (local Frame)
   void rotate(const Rotation& rotation);
   void rotate(const Vector3D& axis, double angle);

   // Rotation (local Frame)
   const Rotation& rotation(void) const;
   void rotation(const Rotation& rotation);
   void rotation(const Vector3D& axis, double angle);

   // Get Torque (Body Frame) [N*m]
   const std::map<std::string, Torque*>& torque(void) const;
   Torque* torque(const std::string& name) const;

   // Velocity (local Frame) [m/s]
   const Vector3D& velocity(void) const;
   void velocity(double x, double y, double z);
   void velocity(const Vector3D& velocity);

   // Compute Volume [m^3]
   double volume(void) const;

   // Compute Wrench (local Frame)
   const Wrench wrench(void) const;

protected:

   // Cache
   static const uint8_t _CACHE_ANGULAR_MOMENTUM = 0x01;
   static const uint8_t _CACHE_AREA = 0x02;
   static const uint8_t _CACHE_CENTER = 0x04;
   static const uint8_t _CACHE_INERTIA = 0x08;
   static const uint8_t _CACHE_MASS = 0x10;
   static const uint8_t _CACHE_MOMENTUM = 0x20;
   static const uint8_t _CACHE_VOLUME = 0x40;
   static const uint8_t _CACHE_WRENCH = 0x80;

   // Update Properties
   static const uint8_t _UPDATE_ANGULAR_MOMENTUM = 1;
   static const uint8_t _UPDATE_ANGULAR_RATE = 2;
   static const uint8_t _UPDATE_AREA = 3;
   static const uint8_t _UPDATE_CENTER = 4;
   static const uint8_t _UPDATE_FORCE = 5;
   static const uint8_t _UPDATE_INERTIA = 6;
   static const uint8_t _UPDATE_MASS = 7;
   static const uint8_t _UPDATE_MOMENTUM = 8;
   static const uint8_t _UPDATE_POSITION = 9;
   static const uint8_t _UPDATE_ROTATION = 10;
   static const uint8_t _UPDATE_TORQUE = 11;
   static const uint8_t _UPDATE_VELOCITY = 12;
   static const uint8_t _UPDATE_VOLUME = 13;
   static const uint8_t _UPDATE_WRENCH = 14;

   // Update Property
   void _update(uint8_t update);

private:

   // Compute angular Momentum (Body Frame) [kg*m^2/s]
   virtual const Vector3D _angular_momentum(void) const;

   // Compute Surface Area [m^2]
   virtual double _area(void) const = 0;

   // Compute Center of Mass (Body Frame) [m]
   virtual const Vector3D _center(void) const = 0;

   // Check if contains Point (Body Frame)
   virtual bool _contains(const Vector3D& point) const = 0;

   // Compute Moment of Inertia (Body Frame) [kg*m^2]
   virtual const Inertia _inertia(void) const = 0;

   // Compute Mass [kg]
   virtual double _mass(void) const = 0;

   // Compute Momentum (Body Frame) [kg*m/s]
   virtual const Vector3D _momentum(void) const;

   // Remove and destroy Item
   virtual void _remove(const Force& force);
   virtual void _remove(const Torque& torque);

   // Compute Volume [m^3]
   virtual double _volume(void) const = 0;

   // Compute Wrench (Body Frame)
   virtual const Wrench _wrench(void) const;

   // Variables
   Vector3D _angular_rate;
   Vector3D _position;
   Vector3D _velocity;
   Rotation _rotation;
   RigidBody* _rigid_body;
   mutable uint8_t _cache;
   mutable double __area;
   mutable double __mass;
   mutable double __volume;
   mutable Vector3D __angular_momentum;
   mutable Vector3D __center;
   mutable Vector3D __momentum;
   mutable Inertia __inertia;
   mutable Wrench __wrench;

   // Friends
   friend class Assembly;
   friend class Force;
   friend class Module;
   friend class Spacecraft;
   friend class System;
   friend class Torque;
};


// Constructor
inline CubeSim::RigidBody::RigidBody(void) : RigidBody(Vector3D(), Rotation())
{
}


// Constructor
inline CubeSim::RigidBody::RigidBody(const Vector3D& position, const Rotation& rotation) : RigidBody(position, rotation,
   Vector3D(), Vector3D())
{
}


// Get angular Rate (local Frame) [rad/s]
inline const CubeSim::Vector3D& CubeSim::RigidBody::angular_rate(void) const
{
   // Return angular Rate
   return _angular_rate;
}


// Set angular Rate (local Frame) [rad/s]
inline void CubeSim::RigidBody::angular_rate(double x, double y, double z)
{
   // Set angular Rate
   angular_rate(Vector3D(x, y, z));
}


// Set angular Rate (local Frame) [rad/s]
inline void CubeSim::RigidBody::angular_rate(const Vector3D& angular_rate)
{
   // Set angular Rate
   _angular_rate = angular_rate;

   // Update Property
   _update(_UPDATE_ANGULAR_RATE);
}


// Compute Surface Area [m^2]
inline double CubeSim::RigidBody::area(void) const
{
   // Check Cache
   if (!(_cache & _CACHE_AREA))
   {
      // Compute Surface Area
      __area = _area();

      // Set Cache
      _cache |= _CACHE_AREA;
   }

   // Return Surface Area
   return __area;
}


// Check if contains Point (local Frame)
inline bool CubeSim::RigidBody::contains(double x, double y, double z) const
{
   // Check if contains Point
   return contains(Vector3D(x, y, z));
}


// Check if contains Point (local Frame)
inline bool CubeSim::RigidBody::contains(const Vector3D& point) const
{
   // Check if contains Point (Body Frame) and return Result
   return _contains(point - _position - _rotation);
}


// Get Force List (Body Frame) [N]
inline const std::map<std::string, CubeSim::Force*>& CubeSim::RigidBody::force(void) const
{
   // Return Force List
   return List<Force>::item();
}


// Get Force (Body Frame) [N]
inline CubeSim::Force* CubeSim::RigidBody::force(const std::string& name) const
{
   // Return Force
   return List<Force>::item(name);
}


// Insert Force (Body Frame) [N]
inline void CubeSim::RigidBody::insert(const std::string& name, const Force& force)
{
   // Insert Force (Body Frame)
   Force& force_ = List<Force>::insert(name, force);

   // Set rigid Body
   force_._rigid_body = this;

   // Update Property
   _update(_UPDATE_FORCE);
}


// Insert Torque (Body Frame) [N*m]
inline void CubeSim::RigidBody::insert(const std::string& name, const Torque& torque)
{
   // Insert Torque (Body Frame)
   Torque& torque_ = List<Torque>::insert(name, torque);

   // Set rigid Body
   torque_._rigid_body = this;

   // Update Property
   _update(_UPDATE_TORQUE);
}


// Compute Mass [kg]
inline double CubeSim::RigidBody::mass(void) const
{
   // Check Cache
   if (!(_cache & _CACHE_MASS))
   {
      // Compute Mass
      __mass = _mass();

      // Set Cache
      _cache |= _CACHE_MASS;
   }

   // Return Mass
   return __mass;
}


// Move (local Frame) [m]
inline void CubeSim::RigidBody::move(double x, double y, double z)
{
   // Move
   move(Vector3D(x, y, z));
}


// Move (local Frame) [m]
inline void CubeSim::RigidBody::move(const Vector3D& distance)
{
   // Update Position
   position(_position + distance);
}


// Get Position (local Frame) [m]
inline const CubeSim::Vector3D& CubeSim::RigidBody::position(void) const
{
   // Return Position
   return _position;
}


// Set Position (local Frame) [m]
inline void CubeSim::RigidBody::position(double x, double y, double z)
{
   // Set Position
   position(Vector3D(x, y, z));
}


// Set Position (local Frame) [m]
inline void CubeSim::RigidBody::position(const Vector3D& position)
{
   // Set Position
   _position = position;

   // Update Property
   _update(_UPDATE_POSITION);
}


// Rotate (local Frame)
inline void CubeSim::RigidBody::rotate(const Rotation& rotation)
{
   // Rotate
   this->rotation(_rotation + rotation);
}


// Rotate (local Frame) [m, rad]
inline void CubeSim::RigidBody::rotate(const Vector3D& axis, double angle)
{
   // Rotate
   rotate(Rotation(axis, angle));
}


// Get Rotation (local Frame)
inline const CubeSim::Rotation& CubeSim::RigidBody::rotation(void) const
{
   // Return Rotation
   return _rotation;
}


// Set Rotation (local Frame)
inline void CubeSim::RigidBody::rotation(const Rotation& rotation)
{
   // Set Rotation
   _rotation = rotation;

   // Update Property
   _update(_UPDATE_ROTATION);
}


// Set Rotation (local Frame) [m, rad]
inline void CubeSim::RigidBody::rotation(const Vector3D& axis, double angle)
{
   // Set Rotation
   rotation(Rotation(axis, angle));
}


// Get Torque List (Body Frame) [N*m]
inline const std::map<std::string, CubeSim::Torque*>& CubeSim::RigidBody::torque(void) const
{
   // Return Torque List
   return List<Torque>::item();
}


// Get Torque (Body Frame) [N*m]
inline CubeSim::Torque* CubeSim::RigidBody::torque(const std::string& name) const
{
   // Return Torque
   return List<Torque>::item(name);
}


// Get Velocity (local Frame) [m/s]
inline const CubeSim::Vector3D& CubeSim::RigidBody::velocity(void) const
{
   // Return Velocity
   return _velocity;
}


// Set Velocity (local Frame) [m/s]
inline void CubeSim::RigidBody::velocity(double x, double y, double z)
{
   // Set Velocity
   velocity(Vector3D(x, y, z));
}


// Set Velocity (local Frame) [m/s]
inline void CubeSim::RigidBody::velocity(const Vector3D& velocity)
{
   // Set Velocity
   _velocity = velocity;

   // Update Property
   _update(_UPDATE_VELOCITY);
}


// Compute Volume [m^3]
inline double CubeSim::RigidBody::volume(void) const
{
   // Check Cache
   if (!(_cache & _CACHE_VOLUME))
   {
      // Compute Volume
      __volume = _volume();

      // Set Cache
      _cache |= _CACHE_VOLUME;
   }

   // Return Volume
   return __volume;
}
