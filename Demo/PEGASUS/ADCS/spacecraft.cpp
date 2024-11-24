

// ADCS - SPACECRAFT


// Includes
#include <vector>
#include "constant.hpp"
#include "magnetics.hpp"
#include "operation.hpp"
#include "spacecraft.hpp"
#include "sun.hpp"


// Compute angular Momentum (Body Frame)
const ADCS::Vector ADCS::Spacecraft::angular_momentum(void)
{
   // Compute and return angular Momentum
   return Vector(Constant::INERTIA.x() * _angular_rate.x(), Constant::INERTIA.y() * _angular_rate.y(),
      Constant::INERTIA.z() * _angular_rate.z());
}


// Compute Orientation (LO Frame)
const ADCS::Rotation ADCS::Spacecraft::orientation(void)
{
   // Compute and return Orientation
   return (rotation() - Frame::LO());
}


// Set Orbit
void ADCS::Spacecraft::orbit(const numeric_t& semimajor_axis, const numeric_t& eccentricity,
   const numeric_t& argument_periapsis, const numeric_t& longitude_ascending, const numeric_t& inclination,
   const numeric_t& mean_anomaly, const double& time)
{
   // Update Orbit
   _orbit = Orbit(Constant::EARTH_MASS, semimajor_axis, eccentricity, argument_periapsis, longitude_ascending,
      inclination, mean_anomaly, time);
}


// Class _Point
class ADCS::Spacecraft::_Point
{
public:

   // Constructor
   _Point(const Vector& position, const double& time);

   // Variables
   Vector position;
   double time;
};


// Update Position
void ADCS::Spacecraft::_update_position(void)
{
   // GPS Position Acquisition Time, Point List
   static double time = Interface::time() + Constant::GPS_INTERVAL;
   static std::vector<_Point> point;

   // Check GPS Position Acquisition Time
   if (time <= Interface::time())
   {
      // Get GPS Location
      Location location = Interface::location();

      // Check if valid
      if (std::isnan(location.longitude()))
      {
         // Clear Point List
         point.clear();
      }
      else
      {
         // Transform into ECI Frame and insert into List
         point.push_back(_Point(Frame::ECEF_ECI(location), location.time()));

         // Update GPS Position Acquisition Time
         time = Interface::time() + Constant::GPS_INTERVAL;

         // Check Point List
         if (point.size() == 3)
         {
            // Parse Points
            for (uint8_t i = 1; i <= 2; ++i)
            {
               // Compute Differences
               point[i].position -= point[0].position;
               point[i].time -= point[0].time;
            }

            // Compute Velocity at the first Point
            Vector velocity = (point[1].position * NUM(point[2].time) / NUM(point[1].time) - point[2].position *
               NUM(point[1].time) / NUM(point[2].time)) / NUM(point[2].time - point[1].time);

            // Compute Orbit
            _orbit = Orbit(Constant::EARTH_MASS, point[0].position, velocity, point[0].time);

            // Update Info (Date-Time currently not used)
            Operation::_info.orbit.semimajor_axis = _orbit.semimajor_axis();
            Operation::_info.orbit.eccentricity = _orbit.eccentricity();
            Operation::_info.orbit.argument_periapsis = _orbit.argument_periapsis();
            Operation::_info.orbit.longitude_ascending = _orbit.longitude_ascending();
            Operation::_info.orbit.inclination = _orbit.inclination();
            Operation::_info.orbit.mean_anomaly = _orbit.mean_anomaly();
            Operation::_info.orbit.datetime = 0;

            // Clear Point List
            point.clear();
         }
      }
   }

   // Set Orbit Time
   _orbit.time(Interface::time());
}


// Update Rotation
void ADCS::Spacecraft::_update_rotation(void)
{
   // Time, Inverse Moment of Inertia
   static double time;
   static Matrix inertia_inv(Vector(NUM(1.0) / Constant::INERTIA.x(), NUM(1.0) / Constant::INERTIA.y(), NUM(1.0) /
      Constant::INERTIA.z()));

   // Save previous Rotation
   Rotation rotation = _rotation;

   // Compute Time since last Round
   numeric_t dt = (0.0 < time) ? NUM(Interface::time() - time) : NUM(0.0);

   // Propagate Rotation
   bool propagate = true;

   // Reset Albedo
   Sun::_albedo = NUM(0.0);

   // Check Sun Direction
   if (std::isnan(Sun::direction().x()))
   {
      // Update Info
      Operation::_info.eclipse = Info::ECLIPSE_INSIDE;
   }
   else
   {
      // Update Info
      Operation::_info.eclipse = Info::ECLIPSE_OUTSIDE;

      // Predict magnetic Field (ECI Frame)
      Vector magnetic_field_model = Magnetics::predict_field();

      // Predict Sun Direction (ECI Frame)
      Vector sun_direction_model = Sun::predict_direction();

      // Compute Sensor Angle (between predicted magnetic Field and predicted Sun Direction)
      numeric_t sensor_angle = magnetic_field_model % sun_direction_model;

      // Check Sensor Angle (should be between 20° and 160°)
      if ((DEG_RAD(20.0) <= sensor_angle) && (sensor_angle <= DEG_RAD(160.0)))
      {
         // Measure magnetic Field (Body Frame)
         Vector magnetic_field = Magnetics::field();

         // Iterate
         for (uint8_t i = 0; (i < 3) && !std::isnan(Sun::_albedo); ++i)
         {
            // Measure Sun Direction (Body Frame)
            Vector sun_direction = Sun::direction(_rotation, Sun::_albedo);

            // Compute Base Vectors
            Vector v_model = (magnetic_field_model ^ sun_direction_model).unit();
            Vector v = (magnetic_field ^ sun_direction).unit();

            // Compute Rotation
            _rotation = Matrix(magnetic_field_model.unit(), v_model, (magnetic_field_model ^ v_model).unit()) *
               Matrix(magnetic_field.unit(), v, (magnetic_field ^ v).unit()).transpose();

            // Compute and update Albedo
            Sun::_albedo = Sun::albedo(_rotation);
         }

         // Clear Propagate Flag
         propagate = false;
      }
   }

   // Check Propagate Flag
   if (propagate)
   {
      // Update Info
      Operation::_info.rotation_mode = Info::ROTATION_MODE_PROPAGATION;

      // Compute angular Rate Norm
      numeric_t angular_rate = _angular_rate.norm();

      // Check angular Rate
      if (NUM(0.0) < angular_rate)
      {
         // Update Rotation
         _rotation += Rotation(_angular_rate + _rotation, angular_rate * dt);
      }
   }
   else
   {
      // Update Info
      Operation::_info.rotation_mode = Info::ROTATION_MODE_DIRECT;
   }

   // Check angular Rate and Time
   if ((Interface::angular_rate().norm() < Constant::GYRO_LIMIT) && (NUM(0.0) < time))
   {
      // Update Info
      Operation::_info.angular_rate_mode = Info::ANGULAR_RATE_MODE_MATRIX;

      // Check Propagate Flag
      if (propagate)
      {
         // Compute mean magnetic Field in the last Round (Body Frame)
         Vector magnetic_field = Magnetics::field() + _angular_rate ^ Magnetics::field() * (dt -
            Constant::MAGNETORQUER_SHUTDOWN_TIME) / NUM(2.0);

         // Compute mean Torque in the last Round (Body Frame)
         Vector torque = Magnetics::moment() ^ magnetic_field;

         // Compute mean angular Acceleration in the last Round (Body Frame)
         Vector angular_acceleration = inertia_inv * (torque - (_angular_rate ^ angular_momentum()));

         // Update angular Rate
         _angular_rate += angular_acceleration * (dt - Constant::MAGNETORQUER_SHUTDOWN_TIME);
      }
      else
      {
         // Compute Rotation Difference (ECI Frame)
         Rotation dR = -rotation + _rotation;

         // Compute angular Rate (Body Frame)
         Vector angular_rate = (dt == NUM(0.0)) ? Vector(NAN, NAN, NAN) : (dR.axis() * dR.angle() / dt - _rotation);

         // Check angular Rate
         if (std::isnan(_angular_rate.x()))
         {
            // Update angular Rate
            _angular_rate = angular_rate;
         }
         else
         {
            // Filter and update angular Rate
            _angular_rate = (NUM(1.0) - Constant::RATE_FILTER) * _angular_rate + Constant::RATE_FILTER * angular_rate;
         }
      }
   }
   else
   {
      // Update Info
      Operation::_info.angular_rate_mode = Info::ANGULAR_RATE_MODE_GYRO;

      // Set angular Rate
      _angular_rate = Interface::angular_rate();
   }

   // Update Time
   time = Interface::time();
}


// Variables
ADCS::Orbit ADCS::Spacecraft::_orbit;
ADCS::Vector ADCS::Spacecraft::_angular_rate;
ADCS::Rotation ADCS::Spacecraft::_rotation;
ADCS::Rotation ADCS::Spacecraft::_target;


// Constructor
inline ADCS::Spacecraft::_Point::_Point(const Vector& position, const double& time) : position(position), time(time)
{
}
