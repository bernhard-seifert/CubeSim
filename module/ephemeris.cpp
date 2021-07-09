

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

   // Earth, J2000.0 Epoch
   CelestialBody* earth = NULL;
   Time epoch(2000, 1, 1, 11, 58, 55, 816);

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
         element = {4.658498587E+6, 5.553836620E-2, 8.999684967E-2, 1.128749988E+0, 4.600191282E+0, 2.180545012E+0,
            2.348206387E+6};
         rate = {-8.229550089E-2, -4.098924943E-8, -8.626228689E-8, 8.399684851E+1, 7.099355303E-1, -3.378157191E-1,
            -6.240603093E-2};

         // Earth Axis Tilt
         Rotation tilt(Vector3D::X, -23.4392811 * Constant::PI / 180.0);

         // Earth Angular Rate [rad/s]
         double angular_rate = 7.292115E-05;

         // Compute Earth Rotation and angular Rate (Offset is chosen that Noon is in the Mean at 12:00 in Year 2000)
         earth->rotation(Rotation(Vector3D::Z, 4.895149134 + (simulation()->time() - epoch) / 1000.0 * angular_rate) +
            tilt);
         earth->angular_rate((Vector3D::Z + tilt) * angular_rate);
      }
      else if (dynamic_cast<CelestialBody::Jupiter*>(celestial_body->second))
      {
         // Set Jupiter Orbit around Solar System Barycenter
         element = {7.783408167E+11, 4.838624000E-02, 2.276602153E-02, 6.003311379E-01, 2.570604668E-01,
            1.753600526E+00, 3.745175671E+08};
         rate = {-1.736382485E+05, -1.325300000E-06, -3.206414182E-07, 5.296631189E-01, 3.709290314E-05,
            3.572532946E-05, -1.253253838E+02};
      }
      else if (dynamic_cast<CelestialBody::Mars*>(celestial_body->second))
      {
         // Set Mars Orbit around Solar System Barycenter
         element = {2.279438224E+11, 9.339410000E-02, 3.228320542E-02, -7.947238154E-02, -4.178951712E-01,
            8.649771297E-01, 5.935526183E+07};
         rate = {2.763072672E+04, 7.882000000E-07, -1.419181320E-06, 3.340613017E+00, 7.756433088E-05,
            -5.106369657E-05, 1.079232375E+01};
      }
      else if (dynamic_cast<CelestialBody::Mercury*>(celestial_body->second))
      {
         // Set Mercury Orbit around Solar System Barycenter
         element = {5.790922654E+10, 2.056359300E-01, 1.222599479E-01, 4.402598684E+00, 1.351893576E+00,
            8.435309955E-01, 7.600446940E+06};
         rate = {5.535121216E+02, 1.906000000E-07, -1.038032827E-06, 2.608790305E+01, 2.800850104E-05,
            -2.187609822E-05, 1.089707054E-01};
      }
      else if (dynamic_cast<CelestialBody::Moon*>(celestial_body->second))
      {
         // Set Moon Orbit around Earth-Moon Barycenter
         element = {3.787385861E+8, 5.553836620E-2, 8.999684967E-2, 4.270342642E+0, 1.458598628E+0, 2.180545012E+0,
            2.348206387E+6};
         rate = {-6.690671110E+0, -4.098924944E-8, -8.626228689E-8, 8.399684851E+1, 7.099355303E-1, -3.378157191E-1,
            -6.240603101E-2};
      }
      else if (dynamic_cast<CelestialBody::Neptune*>(celestial_body->second))
      {
         // Set Neptune Orbit around Solar System Barycenter
         element = {4.498396417E+12, 8.590480000E-03, 3.089308645E-02, -9.620260019E-01, 7.847831490E-01,
            2.300068641E+00, 5.203601999E+09};
         rate = {3.933077619E+05, 5.105000000E-07, 6.173578630E-08, 3.812836741E-02, -5.627197025E-05,
            -8.877861586E-07, 6.824488771E+02};
      }
      else if (dynamic_cast<CelestialBody::Pluto*>(celestial_body->second))
      {
         // Set Pluto Orbit around Solar System Barycenter
         element = {5.906440597E+12, 2.488273000E-01, 2.991496443E-01, 4.170098397E+00, 3.910740341E+00,
            1.925166876E+00, 7.828999144E+09};
         rate = {-4.726694323E+05, 5.170000000E-07, 8.408996336E-09, 2.534354299E-02, -7.091171522E-06,
            -2.065565754E-06, -9.397864552E+02};
      }
      else if (dynamic_cast<CelestialBody::Saturn*>(celestial_body->second))
      {
         // Set Saturn Orbit around Solar System Barycenter
         element = {1.426666414E+12, 5.386179000E-02, 4.338874331E-02, 8.718660372E-01, 1.616155310E+00,
            1.983783543E+00, 9.293967321E+08};
         rate = {-1.870870971E+06, -5.099100000E-06, 3.379114511E-07, 2.133653879E-01, -7.312443666E-05,
            -5.038380531E-05, -1.828158302E+03};
      }
      else if (dynamic_cast<CelestialBody::Uranus*>(celestial_body->second))
      {
         // Set Uranus Orbit around Solar System Barycenter
         element = {2.870658171E+12, 4.725744000E-02, 1.348507406E-02, 5.467036266E+00, 2.983714992E+00,
            1.291839044E+00, 2.652709585E+09};
         rate = {-2.934751188E+06, -4.397000000E-07, -4.240085432E-07, 7.478422172E-02, 7.121865057E-05,
            7.401224027E-06, -4.067904715E+03};
      }
      else if (dynamic_cast<CelestialBody::Venus*>(celestial_body->second))
      {
         // Set Venus Orbit around Solar System Barycenter
         element = {1.082094745E+11, 6.776720000E-03, 5.924827411E-02, 3.176134456E+00, 2.296896356E+00,
            1.338315722E+00, 1.941401752E+07};
         rate = {5.834316957E+03, -4.107000000E-07, -1.376890247E-07, 1.021328550E+01, 4.683224529E-07,
            -4.846677755E-05, 1.570114799E+00};
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

         // Create Orbit (Mean Anomaly does not need to be updated)
         Orbit orbit_(element[0], element[1], _wrap(element[4] - element[5]), _wrap(element[5]), element[2],
            _wrap(element[3] - element[4]), element[6], epoch);

         // Check Celestial Body
         if (dynamic_cast<CelestialBody::Earth*>(celestial_body->second) ||
            dynamic_cast<CelestialBody::Moon*>(celestial_body->second))
         {
            // Set Earth-Moon Barycenter Orbit around Solar System Barycenter
            element = {1.495982612E+11, 1.671123000E-02, 2.672099085E-07, 1.753437557E+00, 1.796601474E+00,
               3.141592654E+00, 3.155784242E+07};
            rate = {8.407400333E+03, -4.392000000E-07, 2.259621932E-06, 6.283075779E+00, 5.642189403E-05,
               0.000000000E+00, 2.660319173E+00};

            // Parse oribital Element Rates
            for (uint8_t i = 0; i < rate.size(); ++i)
            {
               // Update orbital Elements
               element[i] += rate[i] * dt;
            }

            // Create Earth-Moon Barycenter Orbit (Mean Anomaly does not need to be updated)
            Orbit barycenter(element[0], element[1], _wrap(element[4] - element[5]), _wrap(element[5]), element[2],
               _wrap(element[3] - element[4]), element[6], epoch);

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
         element = {6.984639415E+6, 2.659630888E-3, 2.844978396E+0, 3.628100297E+0, 8.293403478E-1, 5.979586919E-1,
            5.809342336E+3};
      }
      else if (dynamic_cast<Spacecraft::ISS*>(spacecraft->second))
      {
         // Set International Space Station Orbit around Earth
         element = {6.756323843E+6, 1.123814944E-3, 1.496062122E+0, 4.486773278E+0, 9.279504874E-1, 4.563976240E+0,
            5.526837184E+3};
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
   for (; (2.0 * Constant::PI) <= x; x -= 2.0 * Constant::PI);

   // Return Number
   return x;
}
