

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
#include "../celestial_body/saturn.hpp"
#include "../celestial_body/sun.hpp"
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

   // Earth, default Time
   CelestialBody* earth = NULL;
   Time time(2015, 1, 1);

   // Parse Celestial Body List
   for (auto celestial_body = simulation()->celestial_body().begin();
      celestial_body != simulation()->celestial_body().end(); ++celestial_body)
   {
      // Orbital Elements
      std::vector<double> orbit;

      // Check Celestial Body
      if (dynamic_cast<CelestialBody::Earth*>(celestial_body->second))
      {
         // Set Earth
         earth = celestial_body->second;

         // Set Earth Orbit around Earth-Moon Barycenter
         orbit = {4.652679725E+6, 3.849005238E-2, 5.245913309E+0, 3.407239897E+0, 8.773217456E-2, 1.576133700E+0,
            2.343771949E+6};

         // Earth Axis Tilt
         Rotation tilt(Vector3D::X, -23.43928 * Constant::PI / 180.0);

         // Earth Angular Rate [rad/s]
         double angular_rate = 7.292115E-5;

         // Compute Earth Rotation and angular Rate
         earth->rotation(Rotation(Vector3D::Z, 1.750679930 + (simulation()->time() - time) / 1000.0 * angular_rate) +
            tilt);
         earth->angular_rate((Vector3D::Z + tilt) * angular_rate);
      }
      else if (dynamic_cast<CelestialBody::Mercury*>(celestial_body->second))
      {
         // Set Mercury Orbit around Solar System Barycenter
         orbit = {5.868254919E+10, 2.031085798E-1, 4.820103106E-1, 8.417219571E-1, 1.217887647E-1, 4.820820403E+0,
            7.748121727E+6};
      }
      else if (dynamic_cast<CelestialBody::Moon*>(celestial_body->second))
      {
         // Set Moon Orbit around Earth-Moon Barycenter
         orbit = {3.782655094E+8, 3.849005238E-2, 2.104320655E+0, 3.407239897E+0, 8.773217456E-2, 1.576133700E+0,
            2.343771949E+6};
      }
      else if (dynamic_cast<CelestialBody::Jupiter*>(celestial_body->second))
      {
         // Set Jupiter Orbit around Solar System Barycenter
         orbit = {7.779386661E+11, 4.881582774E-2, 4.779224530E+0, 1.754980707E+0, 2.275156566E-2, 2.010444516E+0,
            3.745176004E+8};
      }
      else if (dynamic_cast<CelestialBody::Mars*>(celestial_body->second))
      {
         // Set Mars Orbit around Solar System Barycenter
         orbit = {2.288617405E+11, 9.519285062E-2, 5.004129063E+0, 8.648825038E-1, 3.228850052E-2, 1.759586744E-1,
            5.967506140E+7};
      }
      else if (dynamic_cast<CelestialBody::Neptune*>(celestial_body->second))
      {
         // Set Neptune Orbit around Solar System Barycenter
         orbit = {4.498827406E+12, 8.844143231E-3, 4.768228950E+0, 2.298453991E+0, 3.079118664E-2, 5.109965625E+0,
            5.201341577E+9};
      }
      else if (dynamic_cast<CelestialBody::Saturn*>(celestial_body->second))
      {
         // Set Saturn Orbit around Solar System Barycenter
         orbit = {1.428013189E+12, 5.382749445E-2, 5.917080462E+0, 1.983944213E+0, 4.336770123E-2, 2.454783510E+0,
            9.305016908E+8};
      }
      else if (dynamic_cast<CelestialBody::Sun*>(celestial_body->second))
      {
         // Set Sun Orbit around Solar System Barycenter
         orbit = {2.441456828E+8, 8.439804636E-1, 1.671586482E+0, 1.247548406E+0, 4.623863575E-2, 2.702027222E+0,
            4.238666167E+7};
      }
      else if (dynamic_cast<CelestialBody::Uranus*>(celestial_body->second))
      {
         // Set Uranus Orbit around Solar System Barycenter
         orbit = {2.870290696E+12, 4.738811504E-2, 1.692928690E+0, 1.293400541E+0, 1.346172181E-2, 3.602350940E+0,
            2.650636035E+9};
      }
      else if (dynamic_cast<CelestialBody::Venus*>(celestial_body->second))
      {
         // Set Venus Orbit around Solar System Barycenter
         orbit = {1.089392142E+11, 3.729540062E-3, 1.281668562E+0, 1.337986300E+0, 5.919680524E-2, 2.950720970E+0,
            1.959795788E+7};
      }

      // Check orbital Elements
      if (orbit.size())
      {
         // Create Orbit
         Orbit orbit_(orbit[0], orbit[1], orbit[2], orbit[3], orbit[4], orbit[5], orbit[6], time);
         orbit_.time(simulation()->time());

         // Check Celestial Body
         if (dynamic_cast<CelestialBody::Earth*>(celestial_body->second) ||
            dynamic_cast<CelestialBody::Moon*>(celestial_body->second))
         {
            // Create Earth-Moon Barycenter Orbit around Solar System Barycenter
            Orbit barycenter(1.488969653E+11, 1.378388280E-2, 4.971615490E+0, 3.300938853E+0, 1.716643248E-4,
               6.043508101E+0, 3.131580770E+7, time);
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
      std::vector<double> orbit;

      // Check Spacecraft
      if (dynamic_cast<Spacecraft::Hubble*>(spacecraft->second))
      {
         // Set Hubble Telescope Orbit around Earth
         orbit = {6.928215562E+6, 5.089375304E-4, 5.178991525E+0, 3.094281862E+0, 9.051785599E-1, 7.613037526E-2,
            5.739090477E+3};
      }
      else if (dynamic_cast<Spacecraft::ISS*>(spacecraft->second))
      {
         // Set International Space Station Orbit around Earth
         orbit = {6.783712195E+6, 6.586537290E-4, 2.259750046E+0, 3.398197826E+0, 1.293696705E+0, 6.228476746E+0,
            5.560477726E+3};
      }

      // Check orbital Elements
      if (orbit.size())
      {
         // Check Earth
         if (!earth)
         {
            // Exception
            throw Exception::Failed();
         }

         // Create Orbit
         Orbit orbit_(orbit[0], orbit[1], orbit[2], orbit[3], orbit[4], orbit[5], orbit[6], time, Orbit::REFERENCE_ECI);
         orbit_.time(simulation()->time());

         // Compute Spacecraft Position and Velocity
         spacecraft->second->position(earth->position() + orbit_.position());
         spacecraft->second->velocity(earth->velocity() + orbit_.velocity());
      }
   }
}
