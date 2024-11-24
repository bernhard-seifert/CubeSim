

// ADCS - ORBIT


// Includes
#include <limits>
#include "constant.hpp"
#include "orbit.hpp"


// Constructor
ADCS::Orbit::Orbit(const numeric_t& central_mass, const Vector& position, const Vector& velocity, const double& time) :
   _central_mass(central_mass), _position(position), _velocity(velocity)
{
   // Compute orbital Momentum Vector
   Vector h = position ^ velocity;

   // Check central Body Mass and orbital Momentum Vector
   if ((central_mass <= NUM(0.0)) || (h == Vector()))
   {
      // Invalidate
      _invalidate();

      // Return
      return;
   }

   // Compute Inclination
   _inclination = std::acos(h.unit().z());

   // Compute Eccentricity Vector
   Vector e = (velocity ^ h) / central_mass / Constant::G - position.unit();

   // Compute Eccentricity
   _eccentricity = e.norm();

   // Check Eccentricity
   if (NUM(1.0) <= _eccentricity)
   {
      // Invalidate
      _invalidate();

      // Return
      return;
   }
   else if (NUM(0.0) < _eccentricity)
   {
      // Compute true Anomaly
      _true_anomaly = ((position * velocity) >= 0.0) ? std::acos(e.unit() * position.unit()) :
         (NUM(2.0) * Constant::PI - std::acos(e.unit() * position.unit()));
   }

   // Define Vector pointing towards ascending Node
   Vector n(-h.y(), h.x(), NUM(0.0));

   // Check Vector pointing towards ascending Node
   if (n == Vector())
   {
      // Longitude of the ascending Node is undefined
      _longitude_ascending = NAN;

      // Check Eccentricity
      if (_eccentricity == NUM(0.0))
      {
         // Compute true Longitude
         _true_anomaly = (NUM(0.0) < velocity.x()) ? (NUM(2.0) * Constant::PI - std::acos(position.unit().x())) :
            std::acos(position.unit().x());
      }
   }
   else
   {
      // Compute Longitude of the ascending Node
      _longitude_ascending = (NUM(0.0) <= n.y()) ? std::acos(n.unit().x()) :
         (NUM(2.0) * Constant::PI - std::acos(n.unit().x()));

      // Check Eccentricity
      if (_eccentricity == NUM(0.0))
      {
         // Argument of Periapsis is undefined
         _argument_periapsis = NAN;

         // Compute Argument of Latitude
         _true_anomaly = (NUM(0.0) < (n * velocity)) ? (NUM(2.0) * Constant::PI - std::acos(n.unit() *
            position.unit())) : std::acos(n.unit() * position.unit());
      }
      else
      {
         // Compute Argument of Periapsis
         _argument_periapsis = (NUM(0.0) <= e.z()) ? std::acos(n.unit() * e.unit()) :
            (NUM(2.0) * Constant::PI - std::acos(n.unit() * e.unit()));
      }
   }

   // Compute eccentric Anomaly
   _eccentric_anomaly = std::fmod(NUM(2.0) * std::atan(std::tan(_true_anomaly / NUM(2.0)) * std::sqrt((NUM(1.0) -
      _eccentricity) / (NUM(1.0) + _eccentricity))) + NUM(2.0) * Constant::PI, NUM(2.0) * Constant::PI);

   // Compute Semi-major Axis
   _semimajor_axis = NUM(1.0) / (NUM(2.0) / position.norm() - velocity * velocity / Constant::G / central_mass);

   // Compute Apoapsis
   _apoapsis = _semimajor_axis * (NUM(1.0) + _eccentricity);

   // Compute Periapsis
   _periapsis = _semimajor_axis * (NUM(1.0) - _eccentricity);

   // Compute Period
   _period = NUM(2.0) * Constant::PI * std::sqrt(_semimajor_axis * _semimajor_axis * _semimajor_axis / Constant::G /
      central_mass);

   // Compute mean Anomaly
   _mean_anomaly = _eccentric_anomaly - _eccentricity * std::sin(_eccentric_anomaly);

   // Compute Epoch
   _epoch = time - _mean_anomaly / NUM(2.0) / Constant::PI * _period;

   // Compute Rotation
   _rotation = Rotation(Vector::Z, _argument_periapsis) + Rotation(Vector::X, _inclination) +
      Rotation(Vector::Z, _longitude_ascending);

   // Set Time
   _time = time;
}


// Constructor
ADCS::Orbit::Orbit(const numeric_t& central_mass, const numeric_t& semimajor_axis, const numeric_t& eccentricity,
   const numeric_t& argument_periapsis, const numeric_t& longitude_ascending, const numeric_t& inclination,
   const numeric_t& mean_anomaly, const double& time)
{
   // Check Parameters
   if ((central_mass <= NUM(0.0)) || (semimajor_axis <= NUM(0.0)) || (eccentricity < NUM(0.0)) ||
      (NUM(1.0) <= eccentricity) || (argument_periapsis < NUM(0.0)) || ((NUM(2.0) * Constant::PI) <=
      argument_periapsis) || (longitude_ascending < NUM(0.0)) || ((NUM(2.0) * Constant::PI) <= longitude_ascending) ||
      (inclination < NUM(0.0)) || (Constant::PI < inclination) || (mean_anomaly < NUM(0.0)) ||
      ((NUM(2.0) * Constant::PI) <= mean_anomaly))
   {
      // Invalidate
      _invalidate();

      // Return
      return;
   }

   // Initialize
   _central_mass = central_mass;
   _semimajor_axis = semimajor_axis;
   _eccentricity = eccentricity;
   _argument_periapsis = argument_periapsis;
   _longitude_ascending = longitude_ascending;
   _inclination = inclination;

   // Compute Apoapsis
   _apoapsis = semimajor_axis * (NUM(1.0) + eccentricity);

   // Compute Periapsis
   _periapsis = semimajor_axis * (NUM(1.0) - eccentricity);

   // Compute Period
   _period = NUM(2.0) * Constant::PI * std::sqrt(semimajor_axis * semimajor_axis * semimajor_axis / Constant::G /
      central_mass);

   // Compute Epoch
   _epoch = time - mean_anomaly / NUM(2.0) / Constant::PI * _period;

   // Compute Rotation
   _rotation = Rotation(Vector::Z, argument_periapsis) + Rotation(Vector::X, inclination) +
      Rotation(Vector::Z, longitude_ascending);

   // Set Time
   this->time(time);
}


// Set Time [s]
void ADCS::Orbit::time(const double& time)
{
   // Check Time
   if (_time != time)
   {
      // Set Time
      _time = time;

      // Compute Mean Anomaly
      _mean_anomaly = NUM(std::fmod((time - _epoch) / _period, 1.0)) * NUM(2.0) * Constant::PI;

      // Initialize eccentric Anomaly
      _eccentric_anomaly = _mean_anomaly;

      // Solve Equation (Newton-Raphson Method)
      for (uint8_t i = 0; i < 10; ++i)
      {
         // Save previous Value
         numeric_t eccentric_anomaly = _eccentric_anomaly;

         // Iterate
         _eccentric_anomaly += (_eccentric_anomaly - _eccentricity * std::sin(_eccentric_anomaly) - _mean_anomaly) /
            (_eccentricity * std::cos(_eccentric_anomaly) - NUM(1.0));

         // Check Convergence
         if (std::fabs(_eccentric_anomaly - eccentric_anomaly) <
            (NUM(10.0) * std::numeric_limits<numeric_t>::epsilon()))
         {
            // Stop Iteration
            break;
         }
      }

      // Compute true Anomaly
      _true_anomaly = NUM(2.0) * std::atan2(std::sqrt(NUM(1.0) + _eccentricity) * std::sin(_eccentric_anomaly /
         NUM(2.0)), std::sqrt(NUM(1.0) - _eccentricity) * std::cos(_eccentric_anomaly / NUM(2.0)));

      // Compute Distance to central Body
      numeric_t r = _semimajor_axis * (NUM(1.0) - _eccentricity * std::cos(_eccentric_anomaly));

      // Compute Position
      _position = Vector(r * std::cos(_true_anomaly), r * std::sin(_true_anomaly), NUM(0.0)) + _rotation;

      // Compute Velocity
      _velocity = std::sqrt(Constant::G * _central_mass * _semimajor_axis) / r * Vector(-std::sin(_eccentric_anomaly),
         std::sqrt(NUM(1.0) - _eccentricity * _eccentricity) * std::cos(_eccentric_anomaly), NUM(0.0)) + _rotation;
   }
}


// Invalidate
void ADCS::Orbit::_invalidate(void)
{
   // Invalidate Members
   _epoch = NAN;
   _time = NAN;
   _apoapsis = NAN;
   _argument_periapsis = NAN;
   _central_mass = NAN;
   _eccentric_anomaly = NAN;
   _eccentricity = NAN;
   _inclination = NAN;
   _longitude_ascending = NAN;
   _mean_anomaly = NAN;
   _periapsis = NAN;
   _period = NAN;
   _semimajor_axis = NAN;
   _true_anomaly = NAN;
   _position = Vector(NAN, NAN, NAN);
   _velocity = Vector(NAN, NAN, NAN);
}
