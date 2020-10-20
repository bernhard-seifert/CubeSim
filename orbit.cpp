

// CUBESIM - ORBIT


// Includes
#include "orbit.hpp"
#include "simulation.hpp"


// Reference Frames
const CubeSim::Rotation CubeSim::Orbit::REFERENCE_ECLIPTIC;
const CubeSim::Rotation CubeSim::Orbit::REFERENCE_ECI = Rotation(Vector3D(1.0, 0.0, 0.0),
   -23.4392811 * Constant::PI / 180.0);


// Constructor
CubeSim::Orbit::Orbit(double semimajor_axis, double eccentricity, double argument_periapsis, double longitude_ascending,
   double inclination, double mean_anomaly, double period, const Time& time, const Rotation& reference)
{
   // Check semi-major Axis and Period
   if ((semimajor_axis <= 0.0) || (period <= 0.0))
   {
      // Exception
      throw Exception::Parameter();
   }

   // Compute standard gravitational Parameter
   double gravitational_parameter = pow(semimajor_axis, 3.0) / pow(period / 2.0 / Constant::PI, 2.0);

   // Initialize
   _init(gravitational_parameter, semimajor_axis, eccentricity, argument_periapsis, longitude_ascending, inclination,
      mean_anomaly, period, time, reference);
}


// Constructor
CubeSim::Orbit::Orbit(const std::set<const CelestialBody*>& central, double semimajor_axis, double eccentricity,
   double argument_periapsis, double longitude_ascending, double inclination, double mean_anomaly, const Time& time,
   const Rotation& reference)
{
   // Check semi-major Axis
   if (semimajor_axis <= 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Central Bodies Mass
   double mass = 0.0;

   // Parse Central Celestial Body List
   for (std::set<const CelestialBody*>::const_iterator central_ = central.begin(); central_ != central.end();
      ++central_)
   {
      // Update Central Bodies Mass
      mass += (*central_)->mass();
   }

   // Compute standard gravitational Parameter and Period
   double gravitational_parameter = Constant::G * mass;
   double period = 2.0 * Constant::PI * sqrt(pow(semimajor_axis, 3.0) / gravitational_parameter);

   // Initialize
   _init(gravitational_parameter, semimajor_axis, eccentricity, argument_periapsis, longitude_ascending, inclination,
      mean_anomaly, period, time, reference);
}


// Constructor
CubeSim::Orbit::Orbit(const std::set<const CelestialBody*>& central, const RigidBody& rigid_body,
   const Rotation& reference)
{
   // Check Central Body List and Simulation
   if (central.empty() || !(*central.begin())->simulation())
   {
      // Exception
      throw Exception::Failed();
   }

   // Set Time and Reference Frame
   _time_ = (*central.begin())->simulation()->time();
   _reference = reference;

   // Initialize Central Bodies Mass, Barycenter Position, Barycenter Velocity
   double mass = rigid_body.mass();
   Vector3D position = rigid_body.mass() * rigid_body.position();
   Vector3D velocity = rigid_body.mass() * rigid_body.velocity();

   // Gravitational Force
   Vector3D force;

   // Parse Central Celestial Body List
   for (std::set<const CelestialBody*>::const_iterator central_ = central.begin(); central_ != central.end();
      ++central_)
   {
      // Update Mass, Barycenter Position, Barycenter Velocity
      mass += (*central_)->mass();
      position += (*central_)->mass() * (*central_)->position();
      velocity += (*central_)->mass() * (*central_)->velocity();

      // Compute Distance between rigid Body and Central Celestial Body
      Vector3D r = (*central_)->position() - rigid_body.position();

      // Update gravitational Force
      force += Constant::G * (*central_)->mass() * rigid_body.mass() * r / pow(r.norm(), 3.0);
   }

   // Compute relative Position and Velocity to Barycenter in Reference Frame
   position = rigid_body.position() - position / mass - reference;
   velocity = rigid_body.velocity() - velocity / mass - reference;

   // Compute standard gravitational Parameter
   _gravitational_parameter = force.norm() * pow(position.norm(), 2.0) / rigid_body.mass();

   // Compute orbital Momentum Vector
   Vector3D h = position ^ velocity;

   // Check orbital Momentum Vector
   if (h == Vector3D())
   {
      // Exception
      throw Exception::Parameter();
   }

   // Compute Eccentricity Vector
   Vector3D e = (velocity ^ h) / _gravitational_parameter - position.unit();

   // Define Vector pointing towards ascending Node
   Vector3D n(-h.y(), h.x(), 0.0);

   // Compute Inclination
   _inclination = acos(h.unit().z());

   // Compute Eccentricity
   _eccentricity = e.norm();

   // Check Eccentricity
   if (_eccentricity == 0.0)
   {
      // Argument of Periapsis is undefined
      _argument_periapsis = NAN;

      // Compute Argument of Latitude (Circular Orbit)
      _true_anomaly = (0.0 <= position.z()) ? acos(n.unit() * position.unit()) :
         (2.0 * Constant::PI - acos(n.unit() * position.unit()));
   }
   else if (_eccentricity < 1.0)
   {
      // Compute Argument of Periapsis
      _argument_periapsis = (0.0 <= e.z()) ? acos(n.unit() * e.unit()) :
         (2.0 * Constant::PI - acos(n.unit() * e.unit()));

      // Compute true Anomaly
      _true_anomaly = (0.0 <= (position * velocity)) ? acos(e.unit() * position.unit()) :
         (2.0 * Constant::PI - acos(e.unit() * position.unit()));
   }
   else
   {
      // Exception
      throw Exception::Parameter();
   }

   // Compute eccentric Anomaly
   _eccentric_anomaly = _wrap(2.0 * atan2(tan(_true_anomaly / 2.0), sqrt((1.0 + _eccentricity) /
      (1.0 - _eccentricity))));

   // Compute mean Anomaly
   _mean_anomaly = _eccentric_anomaly - _eccentricity * sin(_eccentric_anomaly);

   // Compute Longitude of the ascending Node
   _longitude_ascending = (0.0 <= n.y()) ? acos(n.unit().x()) : (2.0 * Constant::PI - acos(n.unit().x()));

   // Compute Semi-major Axis
   _semimajor_axis = 1.0 / (2.0 / position.norm() - velocity * velocity / _gravitational_parameter);

   // Compute Apoapsis
   _apoapsis = _semimajor_axis * (1.0 + _eccentricity);

   // Compute Periapsis
   _periapsis = _semimajor_axis * (1.0 - _eccentricity);

   // Compute Period
   _period = 2.0 * Constant::PI * sqrt(pow(_semimajor_axis, 3.0) / _gravitational_parameter);

   // Compute Epoch
   _epoch = _time_ - static_cast<int64_t>(_mean_anomaly / 2.0 / Constant::PI * _period * 1000.0);

   // Compute Rotation
   _rotation = Rotation(Vector3D::Z, _argument_periapsis) + Rotation(Vector3D::X, _inclination) +
      Rotation(Vector3D::Z, _longitude_ascending);
}


// Compute Perimeter (Travel Distance for one Revolution) [m]
double CubeSim::Orbit::perimeter(void) const
{
   // Compute semi-minor Axis
   double semiminor_axis = _semimajor_axis * sqrt(1.0 - _eccentricity * _eccentricity);

   // Compute auxiliary Variables
   double m = (_semimajor_axis - semiminor_axis) / (_semimajor_axis + semiminor_axis);
   double x = pow(m, 4.0) / 64.0;
   double s = 1.0 + m * m / 4.0 + x;

   // Loop Series (for Eccentricity of 1 the Error is less than 1 ppm)
   for (size_t i = 0; i < 350; i += 2)
   {
      // Update auxiliary Variables
      x *= pow(m * (3.0 + i) / (6.0 + i), 2.0);
      s += x;
   }

   // Compute and return Perimeter
   return (2.0 * Constant::PI * _semimajor_axis / (1.0 + m) * s);
}


// Get Position relative to Barycenter [m]
const CubeSim::Vector3D CubeSim::Orbit::position(void) const
{
   // Compute relative Distance
   double r = _semimajor_axis * (1.0 - _eccentricity * cos(_eccentric_anomaly));

   // Compute relative Position
   Vector3D position = Vector3D(r * cos(_true_anomaly), r * sin(_true_anomaly), 0.0) + _rotation + _reference;

   // Return relative Position
   return position;
}


// Set Time
void CubeSim::Orbit::time(const Time& time)
{
   // Check Time
   if (time != _time_)
   {
      // Set Time
      _time_ = time;

      // Compute mean Anomaly
      _mean_anomaly = _wrap((time - _epoch) / 1000.0 / _period * 2.0 * Constant::PI);

      // Initialize eccentric Anomaly
      _eccentric_anomaly = _mean_anomaly;

      // Solve Equation (Newton-Raphson Method)
      for (uint8_t i = 0; ; ++i)
      {
         // Save previous Value
         double eccentric_anomaly = _eccentric_anomaly;

         // Iterate
         _eccentric_anomaly += (_eccentric_anomaly - _eccentricity * sin(_eccentric_anomaly) - _mean_anomaly) /
            (_eccentricity * cos(_eccentric_anomaly) - 1.0);

         // Check Convergence
         if (fabs(_eccentric_anomaly - eccentric_anomaly) < std::numeric_limits<float>::epsilon())
         {
            // Stop Iterations
            break;
         }
         else if (i == 100)
         {
            // Exception
            throw Exception::Failed();
         }
      }

      // Compute true Anomaly
      _true_anomaly = _wrap(2.0 * atan2(sqrt(1.0 + _eccentricity) * sin(_eccentric_anomaly / 2.0),
         sqrt(1.0 - _eccentricity) * cos(_eccentric_anomaly / 2.0)));
   }
}


// Get Velocity relative to Barycenter [m/s]
const CubeSim::Vector3D CubeSim::Orbit::velocity(void) const
{
   // Compute relative Distance
   double r = _semimajor_axis * (1.0 - _eccentricity * cos(_eccentric_anomaly));

   // Compute relative Velocity
   Vector3D velocity = sqrt(_gravitational_parameter * _semimajor_axis) / r * Vector3D(-sin(_eccentric_anomaly),
      sqrt(1.0 - pow(_eccentricity, 2.0)) * cos(_eccentric_anomaly), 0.0) + _rotation + _reference;

   // Return relative Velocity
   return velocity;
}


// Wrap Angle into [0; 2*pi) Interval
double CubeSim::Orbit::_wrap(double angle)
{
   // Wrap Angle into (-2*pi; 2*pi) Interval
   angle = fmod(angle, 2.0 * Constant::PI);

   // Compute and return Angle
   return ((angle < 0.0) ? (angle + 2.0 * Constant::PI) : angle);
}


// Initialize
void CubeSim::Orbit::_init(double gravitational_parameter, double semimajor_axis, double eccentricity,
   double argument_periapsis, double longitude_ascending, double inclination, double mean_anomaly, double period,
   const Time& time, const Rotation& reference)
{
   // Check Parameters
   if ((semimajor_axis <= 0.0) || (eccentricity < 0.0) || (1.0 <= eccentricity) || (argument_periapsis < 0.0) ||
      ((2.0 * Constant::PI) <= argument_periapsis) || (longitude_ascending < 0.0) ||
      ((2.0 * Constant::PI) <= longitude_ascending) || (inclination < -Constant::PI) || (Constant::PI < inclination) ||
      (mean_anomaly < 0.0) || ((2.0 * Constant::PI) <= mean_anomaly) || (period <= 0.0))
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Parameters
   _gravitational_parameter = gravitational_parameter;
   _semimajor_axis = semimajor_axis;
   _eccentricity = eccentricity;
   _argument_periapsis = argument_periapsis;
   _longitude_ascending = longitude_ascending;
   _inclination = inclination;
   _mean_anomaly = mean_anomaly;
   _period = period;
   _reference = reference;

   // Compute Apoapsis
   _apoapsis = semimajor_axis * (1.0 + eccentricity);

   // Compute Periapsis
   _periapsis = semimajor_axis * (1.0 - eccentricity);

   // Compute Epoch
   _epoch = time - static_cast<int64_t>(mean_anomaly / 2.0 / Constant::PI * _period * 1000.0);

   // Compute Rotation
   _rotation = Rotation(Vector3D::Z, argument_periapsis) + Rotation(Vector3D::X, inclination) +
      Rotation(Vector3D::Z, longitude_ascending);

   // Set Time
   this->time(time);
}
