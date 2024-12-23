

// ADCS - IGRF


// Includes
#include <cmath>
#include "igrf.hpp"


// Constructor
ADCS::IGRF::IGRF(const numeric_t& time) : _g((3 + _N) * _N / 2), _h((3 + _N) * _N / 2), _k((1 + _N) * _N / 2)
{
   // Initialize
   this->time(time);

   // Initialize Iterator
   auto k = _k.begin();

   // Parse Indices
   for (uint8_t m = 0; m <= _N; ++m)
   {
      // Parse Indices
      for (uint8_t n = m + 1; n <= _N; ++n)
      {
         // Compute Element
         *k++ = ((n - NUM(1.0)) * (n - NUM(1.0)) - m * m) / (NUM(2.0) * n - NUM(1.0)) / (NUM(2.0) * n - NUM(3.0));
      }
   }
}


// Compute magnetic Field
const ADCS::Vector ADCS::IGRF::operator ()(const numeric_t& x, const numeric_t& y, const numeric_t& z) const
{
   // Check Radius
   if ((x * x + y * y + z * z) < (_RADIUS * _RADIUS))
   {
      // Return magnetic Field
      return Vector();
   }

   // Compute scalar Potential
   numeric_t V = _V(x, y, z);

   // Compute and return magnetic Field
   return Vector((V - _V(x + _D, y, z)) / _D, (V - _V(x, y + _D, z)) / _D, (V - _V(x, y, z + _D)) / _D);
}


// Set Time
void ADCS::IGRF::time(const double& time)
{
   // Set Time
   _time = time;

   // Compute Time Difference [Years]
   numeric_t diff = NUM(time - _TIME) / NUM(3600.0) / NUM(24.0) / NUM(365.25636);

   // Index
   uint8_t i = 0;

   // Parse Indices
   for (uint8_t m = 0; m <= _N; ++m)
   {
      // Parse Indices
      for (uint8_t n = m ? m : 1; n <= _N; ++n, ++i)
      {
         // Compute Model Values
         _g[i] = _G[i] + diff * _DG[i];
         _h[i] = _H[i] + diff * _DH[i];
      }
   }
}


// Compute scalar Potential (Parameters are not checked)
ADCS::numeric_t ADCS::IGRF::_V(const numeric_t& x, const numeric_t& y, const numeric_t& z) const
{
   // Compute Radius, Sine and Cosine of Theta, Phi
   numeric_t r_ = std::sqrt(x * x + y * y + z * z);
   numeric_t cos_t = z / r_;
   numeric_t sin_t = std::sqrt(NUM(1.0) - cos_t * cos_t);
   numeric_t p = std::atan2(y, x);

   // Compute relative Radius
   r_ /= _RADIUS;

   // Relative Radii
   std::vector<numeric_t> r(_N);
   r[0] = NUM(1.0) / r_ / r_;

   // Parse Indices
   for (uint8_t i = 1; i < _N; ++i)
   {
      // Compute Element
      r[i] = r[i - 1] / r_;
   }

   // Initialize scalar Potential and Legendre Function
   numeric_t V = NUM(0.0);
   numeric_t P0 = NUM(1.0);

   // Initialize Iterators
   auto g = _g.begin();
   auto h = _h.begin();
   auto k = _k.begin();

   // Parse Indices
   for (uint8_t m = 0; m <= _N; ++m)
   {
      // Compute Sine and Cosine of Phi and Multiples
      numeric_t cos_p = std::cos(m * p);
      numeric_t sin_p = std::sin(m * p);

      // Initialize Legendre Function
      numeric_t P = P0;
      numeric_t P1 = NUM(0.0);
      numeric_t P2;

      // Parse Indices
      for (uint8_t n = m ? m : 1; n <= _N; ++n)
      {
         // Compare Indices
         if (m < n)
         {
            // Update Legendre Function
            P2 = P1;
            P1 = P;
            P = cos_t * P1 - P2 * *k++;
         }

         // Update scalar Potential
         V += r[n - 1] * (*g++ * cos_p + *h++ * sin_p) * P;
      }

      // Update Legendre Function
      P0 *= sin_t;
   }

   // Update scalar Potential
   V *= _RADIUS;

   // Return scalar Potential
   return V;
}


// Earth Radius
const ADCS::numeric_t ADCS::IGRF::_RADIUS = NUM(6.3712E6);

// Model Time [s] (since 2000-01-01 00:00:00)
const double ADCS::IGRF::_TIME = 4.733856E8;

// G Values
const ADCS::numeric_t ADCS::IGRF::_G[] = {NUM(-2.9442E-5), NUM(-3.6676E-6), NUM(3.3768E-6), NUM(3.9708E-6),
   NUM(-1.8317E-6), NUM(1.0106E-6), NUM(2.1879E-6), NUM(1.2166E-6), NUM(5.1279E-7), NUM(-3.4281E-7), NUM(1.0678E-6),
   NUM(-1.2544E-6), NUM(0.0000E+0), NUM(-1.5010E-6), NUM(5.2185E-6), NUM(-7.2024E-6), NUM(4.5030E-6), NUM(3.6610E-6),
   NUM(1.2797E-6), NUM(-2.6992E-6), NUM(5.8988E-7), NUM(1.1212E-6), NUM(-1.5327E-6), NUM(-6.9958E-7), NUM(-1.7941E-7),
   NUM(-1.5572E-6), NUM(1.4521E-6), NUM(2.3734E-6), NUM(4.7114E-7), NUM(1.4786E-6), NUM(1.0864E-6), NUM(-1.9693E-7),
   NUM(-9.4779E-7), NUM(3.3682E-7), NUM(2.1069E-8), NUM(-9.4081E-7), NUM(3.1805E-7), NUM(6.1901E-7), NUM(4.6011E-7),
   NUM(-7.0049E-7), NUM(-6.6311E-7), NUM(-1.2942E-6), NUM(1.0608E-6), NUM(-1.3254E-7), NUM(-2.7384E-7), NUM(8.2640E-8),
   NUM(6.5594E-7), NUM(7.7906E-7), NUM(6.4157E-7), NUM(5.2062E-8), NUM(-3.4942E-7), NUM(-1.5770E-7), NUM(1.8523E-7),
   NUM(-5.5077E-7), NUM(3.9463E-8), NUM(-5.8435E-8), NUM(-1.9161E-7), NUM(-3.8953E-7), NUM(-4.9206E-7), NUM(2.8764E-9),
   NUM(3.0714E-8), NUM(5.8040E-8), NUM(1.9873E-7), NUM(-4.4809E-7), NUM(1.3305E-7), NUM(9.5054E-8), NUM(3.0062E-7),
   NUM(6.9588E-7), NUM(-4.7623E-8), NUM(-6.7811E-9), NUM(8.0323E-8), NUM(-1.7398E-9), NUM(-2.8924E-8), NUM(-6.5882E-8),
   NUM(2.0830E-8), NUM(-9.0309E-8), NUM(4.4014E-9), NUM(-3.9859E-8), NUM(6.5542E-8), NUM(4.2091E-8), NUM(9.9209E-9),
   NUM(5.8527E-8), NUM(2.1371E-7), NUM(-1.2534E-9), NUM(-2.3514E-8), NUM(1.9638E-8), NUM(3.8692E-8), NUM(-1.7558E-8),
   NUM(-1.4279E-8), NUM(-6.3950E-9), NUM(-4.7786E-9), NUM(-1.7630E-9), NUM(-1.0217E-8), NUM(2.0422E-8), NUM(-2.1371E-9),
   NUM(1.0881E-9), NUM(1.8865E-9), NUM(2.8388E-9), NUM(2.0299E-9), NUM(-2.5033E-9), NUM(5.0184E-9), NUM(0.0000E+0),
   NUM(-1.1355E-9), NUM(-1.6702E-10)};

// Change of G Values
const ADCS::numeric_t ADCS::IGRF::_DG[] = { NUM(1.0300E-8), NUM(-1.3050E-8), NUM(8.5000E-9), NUM(-3.0625E-9),
   NUM(-1.5750E-9), NUM(-4.3312E-9), NUM(8.0437E-9), NUM(1.0055E-8), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0),
   NUM(0.0000E+0), NUM(0.0000E+0), NUM(1.8100E-8), NUM(-5.7158E-9), NUM(-1.6840E-8), NUM(1.1068E-9), NUM(5.0833E-9),
   NUM(-1.8903E-9), NUM(-7.0939E-9), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0),
   NUM(0.0000E+0), NUM(1.8187E-9), NUM(-1.3555E-9), NUM(-3.5609E-8), NUM(-9.9908E-9), NUM(-1.0461E-8), NUM(-1.4480E-8),
   NUM(-3.3649E-8), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(-7.9848E-9),
   NUM(8.5758E-9), NUM(-4.7062E-10), NUM(2.0922E-8), NUM(2.6622E-8), NUM(2.0710E-8), NUM(0.0000E+0), NUM(0.0000E+0),
   NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(-3.1799E-9), NUM(3.1059E-9), NUM(-6.5482E-9), NUM(1.2349E-9),
   NUM(-5.3472E-9), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(2.7361E-9),
   NUM(6.9804E-10), NUM(-3.7047E-9), NUM(5.9322E-9), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0),
   NUM(0.0000E+0), NUM(1.0747E-9), NUM(-1.9375E-9), NUM(6.8652E-10), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0),
   NUM(0.0000E+0), NUM(0.0000E+0), NUM(1.2945E-10), NUM(-1.0027E-9), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0),
   NUM(0.0000E+0), NUM(0.0000E+0), NUM(1.8801E-10), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0),
   NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0),
   NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0),
   NUM(0.0000E+0), NUM(0.0000E+0)};

// H Values
const ADCS::numeric_t ADCS::IGRF::_H[] = {NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0),
   NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0),
   NUM(0.0000E+0), NUM(0.0000E+0), NUM(4.7971E-6), NUM(-4.9287E-6), NUM(-3.5303E-7), NUM(1.5678E-6), NUM(4.8088E-7),
   NUM(-3.9318E-7), NUM(-1.9189E-6), NUM(6.7702E-7), NUM(-2.7519E-6), NUM(7.7852E-7), NUM(-4.6639E-8), NUM(-9.8673E-7),
   NUM(-1.5572E-6), NUM(-5.5590E-7), NUM(4.7425E-7), NUM(-7.3841E-7), NUM(1.5140E-6), NUM(4.9615E-7), NUM(-5.6474E-7),
   NUM(-1.0263E-6), NUM(1.1734E-6), NUM(-8.4277E-8), NUM(8.1810E-7), NUM(3.1805E-7), NUM(6.1901E-7), NUM(-4.2564E-7),
   NUM(3.7838E-7), NUM(-5.6145E-7), NUM(5.8681E-7), NUM(1.1673E-7), NUM(5.5088E-7), NUM(9.7920E-7), NUM(7.6029E-7),
   NUM(-2.2958E-7), NUM(1.2335E-6), NUM(2.0530E-6), NUM(-2.4367E-7), NUM(3.5496E-8), NUM(-3.6397E-7), NUM(3.0131E-7),
   NUM(-3.9035E-7), NUM(-3.8336E-7), NUM(5.1423E-7), NUM(-2.6347E-7), NUM(-1.0712E-6), NUM(-4.9206E-7), NUM(7.0296E-8),
   NUM(1.6986E-8), NUM(2.0993E-8), NUM(2.4026E-7), NUM(-2.3247E-7), NUM(-5.8393E-7), NUM(1.2674E-7), NUM(1.0021E-7),
   NUM(-8.3505E-7), NUM(4.2048E-8), NUM(-6.6358E-8), NUM(3.9132E-8), NUM(1.3570E-7), NUM(-2.4792E-8), NUM(-1.8824E-8),
   NUM(1.4581E-7), NUM(-4.5155E-8), NUM(-1.4240E-9), NUM(-2.2812E-8), NUM(7.5335E-9), NUM(-8.4181E-8), NUM(-1.0913E-7),
   NUM(-1.1705E-8), NUM(1.0686E-7), NUM(1.3161E-9), NUM(-1.0336E-8), NUM(-2.2911E-8), NUM(-3.1864E-8), NUM(1.7558E-8),
   NUM(-1.4279E-8), NUM(5.1160E-9), NUM(-3.1857E-9), NUM(-2.2037E-8), NUM(5.1087E-9), NUM(2.7229E-8), NUM(-5.1646E-9),
   NUM(-5.4407E-9), NUM(-8.4892E-9), NUM(1.4194E-8), NUM(-1.3920E-9), NUM(-2.7815E-10), NUM(-3.0110E-9),
   NUM(3.9744E-10), NUM(-1.1355E-9), NUM(-4.4539E-10)};

// Change of H Values
const ADCS::numeric_t ADCS::IGRF::_DH[] = {NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0),
   NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0),
   NUM(0.0000E+0), NUM(0.0000E+0), NUM(-2.6600E-8), NUM(-4.7458E-8), NUM(2.5107E-8), NUM(-7.1942E-9), NUM(6.0999E-9),
   NUM(0.0000E+0), NUM(2.8376E-8), NUM(-2.0109E-8), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0),
   NUM(0.0000E+0), NUM(-1.2211E-8), NUM(-7.7460E-10), NUM(2.0740E-8), NUM(1.3065E-8), NUM(-3.1383E-8), NUM(1.1584E-8),
   NUM(1.6825E-8), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(1.4230E-9),
   NUM(6.0658E-9), NUM(-5.6475E-9), NUM(-6.9740E-9), NUM(-4.0957E-9), NUM(4.1420E-9), NUM(0.0000E+0), NUM(0.0000E+0),
   NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(-3.8455E-9), NUM(7.5430E-9), NUM(1.0914E-9), NUM(-3.7047E-9),
   NUM(1.3368E-8), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0),
   NUM(2.0941E-9), NUM(-3.7047E-9), NUM(-2.9661E-9), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0),
   NUM(0.0000E+0), NUM(6.7169E-10), NUM(2.4218E-10), NUM(-2.0596E-9), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0),
   NUM(0.0000E+0), NUM(0.0000E+0), NUM(-1.2945E-10), NUM(7.5205E-10), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0),
   NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0),
   NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0),
   NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0), NUM(0.0000E+0),
   NUM(0.0000E+0), NUM(0.0000E+0)};

// Delta Distance [m]
const ADCS::numeric_t ADCS::IGRF::_D = NUM(100.0);
