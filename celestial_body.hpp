

// CUBESIM - CELESTIAL BODY


// Includes
#include "location.hpp"
#include "orbit.hpp"
#include "rigid_body.hpp"


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class CelestialBody
   class CelestialBody;

   // Class Simulation
   class Simulation;
}


// Class CelestialBody
class CubeSim::CelestialBody : public RigidBody, public List<CelestialBody>::Item
{
public:

   // Class Earth
   class Earth;

   // Class Jupiter
   class Jupiter;

   // Class Mars
   class Mars;

   // Class Mercury
   class Mercury;

   // Class Moon
   class Moon;

   // Class Neptune
   class Neptune;

   // Class Saturn
   class Saturn;

   // Class Sun
   class Sun;

   // Class Uranus
   class Uranus;

   // Class Venus
   class Venus;

   // Constructor
   CelestialBody(void);

   // Copy Constructor (Simulation Reference is reset)
   CelestialBody(const CelestialBody& celestial_body);

   // Assign (Simulation Reference is maintained)
   CelestialBody& operator =(const CelestialBody& celestial_body);

   // Compute Circumference [m]
   double circumference(void) const;

   // Clone
   virtual CelestialBody* clone(void) const = 0;
   
   // Density [kg/m^3]
   double density(void) const;
   void density(double density);

   // Relative Flattening
   double flattening(void) const;
   void flattening(double flattening);

   // Compute gravitational Field (Body Frame) [m/s^2]
   const Vector3D gravitational_field(double x, double y, double z) const;
   const Vector3D gravitational_field(const Location& location) const;
   virtual const Vector3D gravitational_field(const Vector3D& point) const;

   // Locate Point
   const Location locate(double x, double y, double z) const;
   const Location locate(const Vector3D& point) const;

   // Compute magnetic Field (Body Frame) [T]
   const Vector3D magnetic_field(double x, double y, double z) const;
   const Vector3D magnetic_field(const Location& location) const;
   virtual const Vector3D magnetic_field(const Vector3D& point) const;

   // Compute Orbit
   const Orbit orbit(const CelestialBody& central, const Rotation& reference = Orbit::REFERENCE_ECLIPTIC) const;

   // Compute relative Reflectivity
   virtual double reflectivity(double longitude, double latitude) const;

   // Mean Radius [m]
   double radius(void) const;
   void radius(double radius);

   // Get Simulation
   Simulation* simulation(void) const;

   // Surface Temperature [K]
   double temperature(void) const;
   void temperature(double temperature);

protected:

   // Constructor
   CelestialBody(double radius, double flattening, double density, double temperature, const Vector3D& position,
      const Vector3D& velocity, const Vector3D& angular_rate = Vector3D(), const Rotation& rotation =
     Rotation(Vector3D(0.0, 0.0, 1.0), 0.0));

private:

   // Compute Surface Area [m^2]
   virtual double _area(void) const;

   // Compute Center of Mass (Body Frame) [m]
   virtual const Vector3D _center(void) const;

   // Check if Point is inside (Body Frame)
   virtual bool _contains(const Vector3D& point) const;

   // Compute Moment of Inertia (Body Frame, Origin) [kg*m^2]
   virtual const Inertia _inertia(void) const;

   // Compute Mass [kg]
   virtual double _mass(void) const;

   // Compute Volume [m^3]
   virtual double _volume(void) const;

   // Variables
   double _density;
   double _flattening;
   double _radius;
   double _temperature;
   Simulation* _simulation;

   // Friends
   friend class Simulation;
};


// Constructor
inline CubeSim::CelestialBody::CelestialBody(void) : _radius(), _flattening(), _density(), _temperature(), _simulation()
{
}


// Constructor
inline CubeSim::CelestialBody::CelestialBody(double radius, double flattening, double density, double temperature,
   const Vector3D& position, const Vector3D& velocity, const Vector3D& angular_rate, const Rotation& rotation) :
   RigidBody(position, rotation, velocity, angular_rate), _radius(radius), _flattening(flattening), _density(density),
   _temperature(temperature), _simulation()
{
}


// Copy Constructor (Simulation Reference is reset)
inline CubeSim::CelestialBody::CelestialBody(const CelestialBody& celestial_body) : RigidBody(celestial_body),
   List<CelestialBody>::Item(celestial_body), _density(celestial_body._density),
   _flattening(celestial_body._flattening), _radius(celestial_body._radius), _temperature(celestial_body._temperature),
   _simulation()
{
}


// Compute Circumference [m]
inline double CubeSim::CelestialBody::circumference(void) const
{
   // Compute and return Circumference
   return (2 * Constant::PI * _radius);
}


// Get Density [kg/m^3]
inline double CubeSim::CelestialBody::density(void) const
{
   // Return Density
   return _density;
}


// Set Density [kg/m^3]
inline void CubeSim::CelestialBody::density(double density)
{
   // Check Density
   if (density < 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Density
   _density = density;
}


// Get relative Flattening
inline double CubeSim::CelestialBody::flattening(void) const
{
   // Return Flattening
   return _flattening;
}


// Set relative Flattening
inline void CubeSim::CelestialBody::flattening(double flattening)
{
   // Check Flattening
   if (flattening < 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Flattening
   _flattening = flattening;
}


// Compute gravitational Field (Body Frame) [m/s^2]
inline const CubeSim::Vector3D CubeSim::CelestialBody::gravitational_field(double x, double y, double z) const
{
   // Compute gravitational Field (Body Frame)
   return gravitational_field(Vector3D(x, y, z));
}


// Compute gravitational Field (Body Frame) [m/s^2]
inline const CubeSim::Vector3D CubeSim::CelestialBody::gravitational_field(const Location& location) const
{
   // Compute gravitational Field (Body Frame)
   return gravitational_field(static_cast<const Vector3D>(location));
}


// Locate Point
inline const CubeSim::Location CubeSim::CelestialBody::locate(double x, double y, double z) const
{
   // Locate Point
   return locate(Vector3D(x, y, z));
}


// Locate Point
inline const CubeSim::Location CubeSim::CelestialBody::locate(const Vector3D& point) const
{
   // Locate Point
   return Location(*this, point - position() - rotation());
}


// Compute magnetic Field (Body Frame) [T]
inline const CubeSim::Vector3D CubeSim::CelestialBody::magnetic_field(double x, double y, double z) const
{
   // Compute magnetic Field (Body Frame)
   return magnetic_field(Vector3D(x, y, z));
}


// Compute magnetic Field (Body Frame) [T]
inline const CubeSim::Vector3D CubeSim::CelestialBody::magnetic_field(const Location& location) const
{
   // Compute magnetic Field (Body Frame)
   return magnetic_field(static_cast<const Vector3D>(location));
}


// Compute magnetic Field (Body Frame) [T]
inline const CubeSim::Vector3D CubeSim::CelestialBody::magnetic_field(const Vector3D& point) const
{
   // Return default magnetic Field
   return Vector3D();
}


// Compute Orbit
inline const CubeSim::Orbit CubeSim::CelestialBody::orbit(const CelestialBody& central, const Rotation& reference) const
{
   // Compute and return Orbit
   return Orbit(central, *this, reference);
}


// Get mean Radius [m]
inline double CubeSim::CelestialBody::radius(void) const
{
   // Return mean Radius
   return _radius;
}


// Set mean Radius [m]
inline void CubeSim::CelestialBody::radius(double radius)
{
   // Check mean Radius
   if (radius < 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set mean Radius
   _radius = radius;
}


// Compute relative Reflectivity
inline double CubeSim::CelestialBody::reflectivity(double longitude, double latitude) const
{
   // Return default Reflectivity
   return 0.0;
}


// Get Simulation
inline CubeSim::Simulation* CubeSim::CelestialBody::simulation(void) const
{
   // Return Simulation
   return _simulation;
}


// Get Surface Temperature [K]
inline double CubeSim::CelestialBody::temperature(void) const
{
   // Return Surface Temperature
   return _temperature;
}


// Set Surface Temperature [K]
inline void CubeSim::CelestialBody::temperature(double temperature)
{
   // Check Surface Temperature
   if (temperature < 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Surface Temperature
   _temperature = temperature;
}


// Compute Surface Area [m^2]
inline double CubeSim::CelestialBody::_area(void) const
{
   // Compute and return Surface Area
   return (4 * Constant::PI * _radius * _radius);
}


// Compute Center of Mass (Body Frame) [m]
inline const CubeSim::Vector3D CubeSim::CelestialBody::_center(void) const
{
   // Return Origin
   return Vector3D();
}


// Check if Point is inside (Body Frame)
inline bool CubeSim::CelestialBody::_contains(const Vector3D& point) const
{
   // Return Result
   return ((point.x() * point.x() + point.y() * point.y() + point.z() * point.z()) <= (_radius * _radius));
}


// Compute Moment of Inertia Tensor (Body Frame) [kg*m^2]
inline const CubeSim::Inertia CubeSim::CelestialBody::_inertia(void) const
{
   // Compute Mass
   double mass = this->mass();

   // Compute and return Tensor
   return Inertia(2.0 * mass * radius() * radius() / 5.0 * Matrix3D::IDENTITY, mass);
}


// Compute Mass [kg]
inline double CubeSim::CelestialBody::_mass(void) const
{
   // Compute and return Mass
   return (volume() * _density);
}


// Compute Volume [m^3]
inline double CubeSim::CelestialBody::_volume(void) const
{
   // Compute and return Volume
   return (4.0 / 3.0 * Constant::PI * _radius * _radius * _radius * (1.0 - _flattening));
}
