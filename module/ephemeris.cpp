

// CUBESIM - MODULE - EPHEMERIS


// Includes
#include "ephemeris.hpp"
#include "../simulation.hpp"
#include "../celestial_body/earth.hpp"
#include "../celestial_body/jupiter.hpp"
#include "../celestial_body/mars.hpp"
#include "../celestial_body/mercury.hpp"
#include "../celestial_body/moon.hpp"
#include "../celestial_body/neptune.hpp"
#include "../celestial_body/pluto.hpp"
#include "../celestial_body/saturn.hpp"
#include "../celestial_body/uranus.hpp"
#include "../celestial_body/venus.hpp"
#include "../spacecraft/hubble.hpp"
#include "../spacecraft/iss.hpp"


// Behavior
void CubeSim::Module::Ephemeris::_behavior(void)
{
   // Check Simulation
   if (!simulation())
   {
      // Exception
      throw Exception::Failed();
   }

   // Earth, Epoch
   CelestialBody* earth = NULL;
   Time epoch(2000, 1, 1);

   // Parse Celestial Body List
   for (auto celestial_body = simulation()->celestial_body().begin();
      celestial_body != simulation()->celestial_body().end(); ++celestial_body)
   {
      // Orbital Elements and Rate
      std::vector<double> element;
      std::vector<double> rate;

      // Check Celestial Body
      if (dynamic_cast<CelestialBody::Earth*>(celestial_body->second))
      {
         // Set Earth
         earth = celestial_body->second;

         // Set Earth Orbit around Earth-Moon Barycenter
         element = {4.658498505E+06, 5.553913677E-02, 7.668218294E-01, 4.664353837E+00, 8.999685009E-02, 2.241665360E+00,
            2.348206323E+06};
         rate = {-9.257321428E-02, -3.371475821E-08, 1.211927378E+02, -1.948930709E+01, -8.610071545E-08};

         // Earth Axis Tilt
         Rotation tilt(Vector3D::X, -23.4392811 * Constant::PI / 180.0);

         // Earth Angular Rate [rad/s]
         double angular_rate = 7.292115E-05;

         // Compute Earth Rotation and angular Rate (Offset is chosen that Noon is in the Mean at 12:00 in Year 2000)
         earth->rotation(Rotation(Vector3D::Z, 1.768959 + (simulation()->time() - epoch) / 1000.0 * angular_rate) +
            tilt);
         earth->angular_rate((Vector3D::Z + tilt) * angular_rate);
      }
      else if (dynamic_cast<CelestialBody::Jupiter*>(celestial_body->second))
      {
         // Set Jupiter Orbit around Solar System Barycenter
         element = {7.783408167E+11, 4.838624000E-02, 4.786645248E+00, 1.753600526E+00, 2.276602153E-02, 3.432706710E-01,
            3.743816182E+08};
         rate = {-1.736382485E+05, -1.325300000E-06, 1.367573679E-06, 3.572532946E-05, -3.206414182E-07};
      }
      else if (dynamic_cast<CelestialBody::Mars*>(celestial_body->second))
      {
         // Set Mars Orbit around Solar System Barycenter
         element = {2.279438224E+11, 9.339410000E-02, 5.000313006E+00, 8.649771297E-01, 3.228320542E-02, 3.384227897E-01,
            5.935642698E+07};
         rate = {2.763072672E+04, 7.882000000E-07, 1.286280275E-04, -5.106369657E-05, -1.419181320E-06};
      }
      else if (dynamic_cast<CelestialBody::Mercury*>(celestial_body->second))
      {
         // Set Mercury Orbit around Solar System Barycenter
         element = {5.790922654E+10, 2.056359300E-01, 5.083625809E-01, 8.435309955E-01, 1.222599479E-01, 3.050705108E+00,
            7.600551917E+06};
         rate = {5.535121216E+02, 1.906000000E-07, 4.988459925E-05, -2.187609822E-05, -1.038032827E-06};
      }
      else if (dynamic_cast<CelestialBody::Moon*>(celestial_body->second))
      {
         // Set Moon Orbit around Earth-Moon Barycenter
         element = {3.787385795E+08, 5.553913677E-02, 3.908411829E+00, 4.664353837E+00, 8.999685009E-02, 2.241665360E+00,
            2.348206323E+06};
         rate = {-7.526255024E+00, -3.371475820E-08, 1.211927378E+02, -1.948930709E+01, -8.610071545E-08};
      }
      else if (dynamic_cast<CelestialBody::Neptune*>(celestial_body->second))
      {
         // Set Neptune Orbit around Solar System Barycenter
         element = {4.498396417E+12, 8.590480000E-03, 4.767899815E+00, 2.300068641E+00, 3.089308645E-02, 4.536376156E+00,
            5.192722829E+09};
         rate = {3.933077619E+05, 5.105000000E-07, -5.538418409E-05, -8.877861586E-07, 6.173578630E-08};
      }
      else if (dynamic_cast<CelestialBody::Pluto*>(celestial_body->second))
      {
         // Set Pluto Orbit around Solar System Barycenter
         element = {5.906440597E+12, 2.488273000E-01, 1.985573465E+00, 1.925166876E+00, 2.991496443E-01, 2.593580568E-01,
            7.821589288E+09};
         rate = {-4.726694323E+05, 5.170000000E-07, -5.025605768E-06, -2.065565754E-06, 8.408996336E-09};
      }
      else if (dynamic_cast<CelestialBody::Saturn*>(celestial_body->second))
      {
         // Set Saturn Orbit around Solar System Barycenter
         element = {1.426666414E+12, 5.386179000E-02, 5.915557074E+00, 1.983783543E+00, 4.338874331E-02, 5.538896034E+00,
            9.289900238E+08};
         rate = {-1.870870971E+06, -5.099100000E-06, -2.274063135E-05, -5.038380531E-05, 3.379114511E-07};
      }
      else if (dynamic_cast<CelestialBody::Uranus*>(celestial_body->second))
      {
         // Set Uranus Orbit around Solar System Barycenter
         element = {2.870658171E+12, 4.725744000E-02, 1.691875948E+00, 1.291839044E+00, 1.348507406E-02, 2.483321275E+00,
            2.653918870E+09};
         rate = {-2.934751188E+06, -4.397000000E-07, 6.381742654E-05, 7.401224027E-06, -4.240085432E-07};
      }
      else if (dynamic_cast<CelestialBody::Venus*>(celestial_body->second))
      {
         // Set Venus Orbit around Solar System Barycenter
         element = {1.082094745E+11, 6.776720000E-03, 9.585806336E-01, 1.338315722E+00, 5.924827411E-02, 8.792381001E-01,
            1.941415011E+07};
         rate = {5.834316957E+03, -4.107000000E-07, 4.893510000E-05, -4.846677755E-05, -1.376890247E-07};
      }

      // Check orbital Elements
      if (element.size())
      {
         // Compute elapsed Years since Epoch
         double dt = (simulation()->time() - epoch) / 1000.0 / 3600 / 24 / 365.25;

         // Parse oribital Element Rates
         for (uint8_t i = 0; i < rate.size(); ++i)
         {
            // Update orbital Elements
            element[i] += rate[i] * dt;
         }

         // Create Orbit (mean Anomaly still defined at Epoch)
         Orbit orbit_(element[0], element[1], _wrap(element[2]), _wrap(element[3]), element[4], element[5], element[6],
            epoch);
         orbit_.time(simulation()->time());

         // Check Celestial Body
         if (dynamic_cast<CelestialBody::Earth*>(celestial_body->second) ||
            dynamic_cast<CelestialBody::Moon*>(celestial_body->second))
         {
            // Set Earth-Moon Barycenter Orbit around Solar System Barycenter
            element = {1.495982612E+11, 1.671123000E-02, 1.796601474E+00, 3.141592654E+00, 2.672099084E-07,
               3.098428737E+00, 3.155843351E+07};
            rate = {8.407400333E+03, -4.392000000E-07, 5.642189403E-05, 0.000000000E+00, 2.259621932E-06};

            // Parse oribital Element Rates
            for (uint8_t i = 0; i < rate.size(); ++i)
            {
               // Update orbital Elements
               element[i] += rate[i] * dt;
            }

            // Create Earth-Moon Barycenter Orbit (mean Anomaly still defined at Epoch)
            Orbit barycenter(element[0], element[1], _wrap(element[2]), _wrap(element[3]), element[4], element[5],
               element[6], epoch);
            barycenter.time(simulation()->time());

            // Compute Celestial Body Position and Velocity
            celestial_body->second->position(orbit_.position() + barycenter.position());
            celestial_body->second->velocity(orbit_.velocity() + barycenter.velocity());
         }
         else
         {
            // Compute Celestial Body Position and Velocity
            celestial_body->second->position(orbit_.position());
            celestial_body->second->velocity(orbit_.velocity());
         }
      }
   }

   // Parse Spacecraft List
   for (auto spacecraft = simulation()->spacecraft().begin(); spacecraft != simulation()->spacecraft().end();
      ++spacecraft)
   {
      // Orbital Elements
      std::vector<double> element;

      // Check Spacecraft
      if (dynamic_cast<Spacecraft::Hubble*>(spacecraft->second))
      {
         // Set Hubble Telescope Orbit around Earth
         element = {6.984447463E+06, 1.958558163E-03, 8.137903143E+00, 3.661528333E+00, 8.185426590E-01, 1.135650041E+01,
            5.809102859E+03};
      }
      else if (dynamic_cast<Spacecraft::ISS*>(spacecraft->second))
      {
         // Set International Space Station Orbit around Earth
         element = {6.759645261E+06, 2.048033237E-03, 7.786127834E+00, 4.525324174E+00, 9.106251262E-01, 1.202919227E+01,
            5.530913186E+03};
      }

      // Check orbital Elements
      if (element.size())
      {
         // Check Earth
         if (!earth)
         {
            // Exception
            throw Exception::Failed();
         }

         // Create Orbit
         Orbit orbit_(element[0], element[1], _wrap(element[2]), _wrap(element[3]), element[4], element[5], element[6],
            epoch, Orbit::REFERENCE_ECI);
         orbit_.time(simulation()->time());

         // Compute Spacecraft Position and Velocity
         spacecraft->second->position(earth->position() + orbit_.position());
         spacecraft->second->velocity(earth->velocity() + orbit_.velocity());
      }
   }
}


// Wrap to [0; 2 * PI) Range
double CubeSim::Module::Ephemeris::_wrap(double x)
{
   // Increase Number when < 0
   for (; x < 0.0; x += 2.0 * Constant::PI);

   // Decrease Number when >= 2 * PI
   for (; (2 * Constant::PI) <= x; x -= 2.0 * Constant::PI);

   // Return Number
   return x;
}
