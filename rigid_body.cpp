

// CUBESIM - RIGID BODY


// Includes
#include <typeinfo>
#include "rigid_body.hpp"


// Constructor
CubeSim::RigidBody::RigidBody(const Vector3D& position, const Rotation& rotation, const Vector3D& velocity,
   const Vector3D& angular_rate) : _position(position), _rotation(rotation), _velocity(velocity),
   _angular_rate(angular_rate), _rigid_body(), __area(NAN), __mass(NAN), __volume(NAN),
   __angular_momentum(NAN, 0.0, 0.0), __center(NAN, 0.0, 0.0), __momentum(NAN, 0.0, 0.0)
{
   // Initialize
   __inertia.at(1, 1) = NAN;
   __wrench.force(NAN, 0.0, 0.0);
}


// Copy Constructor (Rigid Body Reference is reset)
CubeSim::RigidBody::RigidBody(const RigidBody& rigid_body) : List<Force>(rigid_body), List<Torque>(rigid_body),
   _angular_rate(rigid_body._angular_rate), _position(rigid_body._position), _velocity(rigid_body._velocity),
   _rotation(rigid_body._rotation), _rigid_body(), __area(rigid_body.__area), __mass(rigid_body.__mass),
   __volume(rigid_body.__volume), __angular_momentum(rigid_body.__angular_momentum), __center(rigid_body.__center),
   __momentum(rigid_body.__momentum), __inertia(rigid_body.__inertia), __wrench(rigid_body.__wrench)
{
   // Parse Force List
   for (auto force_ = force().begin(); force_ != force().end(); ++force_)
   {
      // Set Rigid Body
      force_->second->_rigid_body = this;
   }

   // Parse Torque List
   for (auto torque_ = torque().begin(); torque_ != torque().end(); ++torque_)
   {
      // Set Rigid Body
      torque_->second->_rigid_body = this;
   }
}


// Assign (Rigid Body Reference is maintained)
CubeSim::RigidBody& CubeSim::RigidBody::operator =(const RigidBody& rigid_body)
{
   // Check Type to avoid Object Slicing
   if (typeid(*this) != typeid(rigid_body))
   {
      // Exception
      throw Exception::Parameter();
   }

   // Assign
   static_cast<List<Force>&>(*this) = rigid_body;
   static_cast<List<Torque>&>(*this) = rigid_body;
   _angular_rate = rigid_body._angular_rate;
   _position = rigid_body._position;
   _velocity = rigid_body._velocity;
   _rotation = rigid_body._rotation;
   __area = rigid_body.__area;
   __mass = rigid_body.__mass;
   __volume = rigid_body.__volume;
   __angular_momentum = rigid_body.__angular_momentum;
   __center = rigid_body.__center;
   __momentum = rigid_body.__momentum;
   __inertia = rigid_body.__inertia;
   __wrench = rigid_body.__wrench;

   // Return Reference
   return *this;
}


// Compute angular Momentum (local Frame) [kg*m^2/s]
const CubeSim::Vector3D CubeSim::RigidBody::angular_momentum(void) const
{
   // Check cached Value
//***   if (std::isnan(__angular_momentum.x()))
   {
      // Compute internal angular Momentum
      __angular_momentum = _angular_momentum();
   }

   // Transform internal angular Momentum
   Vector3D angular_momentum = __angular_momentum + _rotation;

   // Check angular Rate
   if (_angular_rate != Vector3D())
   {
      // Compute angular Momentum (either free or fixed Axis) and update angular Momentum
      // *** we need to check the formula for the reaction wheels, is the angular momentum really constant???
      // *** angular_momentum += _rigid_body ? (inertia()(_angular_rate) * _angular_rate) : (inertia() * _angular_rate);
      // ***                                                                                    ^ this is in local frame but through COG!
      // *** this formula might be wrong... check that
      // REMARK: when inertia() is converted to a 3D matrix, it is in local frame but through COG, so for the angular momentum computation fine!?

      angular_momentum += inertia() * _angular_rate;
   }

   // Return angular Momentum
   return angular_momentum;
}


// Compute Center of Mass (local Frame) [m]
const CubeSim::Vector3D CubeSim::RigidBody::center(void) const
{
   // Check cached Value
   if (std::isnan(__center.x()))
   {
      // Compute Center of Mass (Body Frame)
      __center = _center();
   }

   // Transform and return Center of Mass
   return (__center + _rotation + _position);
}


// Compute Moment of Inertia (local Frame) [kg*m^2]
const CubeSim::Inertia CubeSim::RigidBody::inertia(void) const
{
   // Check cached Value
   if (std::isnan(__inertia.at(1, 1)))
   {
      // Compute Moment of Inertia (Body Frame)
      __inertia = _inertia();
   }

   // Transform and return Moment of Inertia
   return (__inertia + _rotation + _position);
}


// Locate in global Frame
const std::pair<CubeSim::Vector3D, CubeSim::Rotation> CubeSim::RigidBody::locate(void) const
{
   // Get Position and Rotation
   Vector3D position = _position;
   Rotation rotation = _rotation;

   // Parse rigid Bodies
   for (const RigidBody* rigid_body = _rigid_body; rigid_body; rigid_body = rigid_body->_rigid_body)
   {
      // Update Position and Rotation
      position = position + rigid_body->_rotation + rigid_body->_position;
      rotation += rigid_body->_rotation;
   }

   // Return Position and Rotation
   return std::pair<Vector3D, Rotation>(position, rotation);
}


// Compute Momentum (local Frame) [m/s]
const CubeSim::Vector3D CubeSim::RigidBody::momentum(void) const
{
   // Check cached Value
   if (std::isnan(__momentum.x()))
   {
      // Compute internal Momentum
      __momentum = _momentum();
   }

   // Transform internal Momentum
   Vector3D momentum = __momentum + _rotation;

   // Check Velocity
   if (_velocity != Vector3D())
   {
      // Compute external Momentum and update Momentum
      momentum += mass() * _velocity;
   }

   // Return Momentum
   return momentum;
}


// Compute Wrench (local Frame)
const CubeSim::Wrench CubeSim::RigidBody::wrench(void) const
{
   // Check cached Value
   if (std::isnan(__wrench.force().x()))
   {
      // Compute Wrench (Body Frame)
      __wrench = _wrench();
   }

   // Transform and return Wrench
   return (__wrench + _rotation + _position);
}


// Update Property
void CubeSim::RigidBody::_update(uint8_t update)
{
   // Check Update Property
   switch (update)
   {
      // Angular Momentum
      case _UPDATE_ANGULAR_MOMENTUM:
      {
         // Check Parent Rigid Body
         if (_rigid_body)
         {
            // Update Property
            _rigid_body->_update(_UPDATE_ANGULAR_MOMENTUM);
         }

         // Invalidate angular Momentum
         __angular_momentum.x(NAN);
         break;
      }

      // Angular Rate
      case _UPDATE_ANGULAR_RATE:
      {
         // Update Property
         _update(_UPDATE_ANGULAR_MOMENTUM);
         break;
      }

      // Surface Area
      case _UPDATE_AREA:
      {
         // Check Parent Rigid Body
         if (_rigid_body)
         {
            // Update Property
            _rigid_body->_update(_UPDATE_AREA);
         }

         // Invalidate Surface Area
         __area = NAN;
         break;
      }

      // Center of Mass
      case _UPDATE_CENTER:
      {
         // Invalidate Center of Mass
         __center.x(NAN);
         break;
      }

      // Force
      case _UPDATE_FORCE:
      {
         // Update Property
         _update(_UPDATE_WRENCH);
         break;
      }

      // Moment of Inertia
      case _UPDATE_INERTIA:
      {
         // Invalidate Moment of Inertia
         __inertia.at(1, 1) = NAN;

         // Update Property
         _update(_UPDATE_ANGULAR_MOMENTUM);
         break;
      }

      // Mass
      case _UPDATE_MASS:
      {
         // Invalidate Mass
         __mass = NAN;

         // Update Properties
         _update(_UPDATE_CENTER);
         _update(_UPDATE_INERTIA);
         _update(_UPDATE_MOMENTUM);
         break;
      }

      // Momentum
      case _UPDATE_MOMENTUM:
      {
         // Check Parent Rigid Body
         if (_rigid_body)
         {
            // Update Property
            _rigid_body->_update(_UPDATE_MOMENTUM);

            // *** this should also affect angular momentum, TBC?
            _rigid_body->_update(_UPDATE_ANGULAR_MOMENTUM);
         }

         // Invalidate Momentum
         __momentum.x(NAN);
         break;
      }

      // Position
      case _UPDATE_POSITION:
      {
         // Check Parent Rigid Body
         if (_rigid_body)
         {
            // Update Property
            _rigid_body->_update(_UPDATE_INERTIA);

            // *** this should also affect angular momentum, TBC?
            _rigid_body->_update(_UPDATE_ANGULAR_MOMENTUM);
            _rigid_body->_update(_UPDATE_CENTER);
         }

         // Break
         break;
      }

      // Rotation
      case _UPDATE_ROTATION:
      {
         // Check Parent Rigid Body
         if (_rigid_body)
         {
            // Update Property
            _rigid_body->_update(_UPDATE_INERTIA);

            // ***
            _rigid_body->_update(_UPDATE_CENTER);
         }

         // Break
         break;
      }

      // Torque
      case _UPDATE_TORQUE:
      {
         // Update Property
         _update(_UPDATE_WRENCH);
         break;
      }

      // Velocity
      case _UPDATE_VELOCITY:
      {
         // Update Property
         _update(_UPDATE_MOMENTUM);
         break;
      }

      // Volume
      case _UPDATE_VOLUME:
      {
         // Check Parent Rigid Body
         if (_rigid_body)
         {
            // Update Property
            _rigid_body->_update(_UPDATE_VOLUME);
         }

         // Update Property
         _update(_UPDATE_MASS);

         // Invalidate Volume
         __volume = NAN;
         break;
      }

      // Wrench
      case _UPDATE_WRENCH:
      {
         // Check Parent Rigid Body
         if (_rigid_body)
         {
            // Update Property
            _rigid_body->_update(_UPDATE_WRENCH);
         }

         // Invalidate Wrench
         __wrench.force(NAN, 0.0, 0.0);
         break;
      }
   }
}


// Compute angular Momentum (Body Frame) [kg*m^2/s]
const CubeSim::Vector3D CubeSim::RigidBody::_angular_momentum(void) const
{
   // Return angular Momentum
   return Vector3D();
}


// Compute Momentum (Body Frame) [kg*m/s]
const CubeSim::Vector3D CubeSim::RigidBody::_momentum(void) const
{
   // Return Momentum
   return Vector3D();
}


// Remove and destroy Force
void CubeSim::RigidBody::_remove(const Force& force)
{
   // Remove and destroy Force
   List<Force>::_remove(force);

   // Update Property
   _update(_UPDATE_FORCE);
}


// Remove and destroy Torque
void CubeSim::RigidBody::_remove(const Torque& torque)
{
   // Remove and destroy Torque
   List<Torque>::_remove(torque);

   // Update Property
   _update(_UPDATE_TORQUE);
}


// Compute Wrench (Body Frame)
const CubeSim::Wrench CubeSim::RigidBody::_wrench(void) const
{
   // Return Wrench
   return Wrench(force(), torque(), mass(), _center());
}
