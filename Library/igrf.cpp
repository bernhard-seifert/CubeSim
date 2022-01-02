

// IGRF 1.3.1


// Includes
#include <igrf.hpp>
#include <math.h>


// Constructor
IGRF::IGRF(const Time& time) : _g((3 + _N) * _N / 2), _h((3 + _N) * _N / 2), _k((1 + _N) * _N / 2)
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
         *k++ = ((n - 1.0) * (n - 1.0) - m * m) / (2.0 * n - 1.0) / (2.0 * n - 3.0);
      }
   }
}


// Compute magnetic Field
const IGRF::Field IGRF::operator ()(double x, double y, double z) const
{
   // Check Radius
   if ((x * x + y * y + z * z) < (_RADIUS * _RADIUS))
   {
      // Return magnetic Field
//      return Field();
   }

   // Compute scalar Potential
   double V = _V(x, y, z);

   // Compute and return magnetic Field
   return Field((V - _V(x + _D, y, z)) / _D, (V - _V(x, y + _D, z)) / _D, (V - _V(x, y, z + _D)) / _D);
}


// Set Time
void IGRF::time(const Time& time)
{
   // Set Time
   _time = time;

   // Compute Time Difference [Years]
   double diff = (time - _TIME) / 1000.0 / 3600.0 / 24.0 / 365.25636;

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
double IGRF::_V(double x, double y, double z) const
{
   // Compute Radius, Sine and Cosine of Theta, Phi
   double r_ = sqrt(x * x + y * y + z * z);
   double cos_t = z / r_;
   double sin_t = sqrt(1.0 - cos_t * cos_t);
   double p = atan2(y, x);

   // Compute relative Radius
   r_ /= _RADIUS;

   // Relative Radii
   std::vector<double> r(_N);
   r[0] = 1.0 / r_ / r_;

   // Parse Indices
   for (uint8_t i = 1; i < _N; ++i)
   {
      // Compute Element
      r[i] = r[i - 1] / r_;
   }

   // Initialize scalar Potential and Legendre Function
   double V = 0.0;
   double P0 = 1.0;

   // Initialize Iterators
   auto g = _g.begin();
   auto h = _h.begin();
   auto k = _k.begin();

   // Parse Indices
   for (uint8_t m = 0; m <= _N; ++m)
   {
      // Compute Sine and Cosine of Phi and Multiples
      double cos_p = cos(m * p);
      double sin_p = sin(m * p);

      // Initialize Legendre Function
      double P = P0;
      double P1 = 0.0;
      double P2;

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


// Constructor
inline IGRF::Field::Field(void) : _strength(), _x(), _y(), _z()
{
}


// Constructor
inline IGRF::Field::Field(double x, double y, double z) : _strength(sqrt(x * x + y * y + z * z)), _x(x), _y(y), _z(z)
{
}


// Earth Radius
const double IGRF::_RADIUS = 6.3712E6;

// Model Time
const Time IGRF::_TIME(2015, 1, 1);

// G Values
const double IGRF::_G[] = {-2.9442E-5, -3.6676E-6, 3.3768E-6, 3.9708E-6, -1.8317E-6, 1.0106E-6, 2.1879E-6,
   1.2166E-6, 5.1279E-7, -3.4281E-7, 1.0678E-6, -1.2544E-6, 0.0000E+0, -1.5010E-6, 5.2185E-6, -7.2024E-6, 4.5030E-6,
   3.6610E-6, 1.2797E-6, -2.6992E-6, 5.8988E-7, 1.1212E-6, -1.5327E-6, -6.9958E-7, -1.7941E-7, -1.5572E-6, 1.4521E-6,
   2.3734E-6, 4.7114E-7, 1.4786E-6, 1.0864E-6, -1.9693E-7, -9.4779E-7, 3.3682E-7, 2.1069E-8, -9.4081E-7, 3.1805E-7,
   6.1901E-7, 4.6011E-7, -7.0049E-7, -6.6311E-7, -1.2942E-6, 1.0608E-6, -1.3254E-7, -2.7384E-7, 8.2640E-8, 6.5594E-7,
   7.7906E-7, 6.4157E-7, 5.2062E-8, -3.4942E-7, -1.5770E-7, 1.8523E-7, -5.5077E-7, 3.9463E-8, -5.8435E-8, -1.9161E-7,
   -3.8953E-7, -4.9206E-7, 2.8764E-9, 3.0714E-8, 5.8040E-8, 1.9873E-7, -4.4809E-7, 1.3305E-7, 9.5054E-8, 3.0062E-7,
   6.9588E-7, -4.7623E-8, -6.7811E-9, 8.0323E-8, -1.7398E-9, -2.8924E-8, -6.5882E-8, 2.0830E-8, -9.0309E-8, 4.4014E-9,
   -3.9859E-8, 6.5542E-8, 4.2091E-8, 9.9209E-9, 5.8527E-8, 2.1371E-7, -1.2534E-9, -2.3514E-8, 1.9638E-8, 3.8692E-8,
   -1.7558E-8, -1.4279E-8, -6.3950E-9, -4.7786E-9, -1.7630E-9, -1.0217E-8, 2.0422E-8, -2.1371E-9, 1.0881E-9, 1.8865E-9,
   2.8388E-9, 2.0299E-9, -2.5033E-9, 5.0184E-9, 0.0000E+0, -1.1355E-9, -1.6702E-10};

// Change of G Values
const double IGRF::_DG[] = {1.0300E-8, -1.3050E-8, 8.5000E-9, -3.0625E-9, -1.5750E-9, -4.3312E-9,
   8.0437E-9, 1.0055E-8, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 1.8100E-8, -5.7158E-9, -1.6840E-8,
   1.1068E-9, 5.0833E-9, -1.8903E-9, -7.0939E-9, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0,
   1.8187E-9, -1.3555E-9, -3.5609E-8, -9.9908E-9, -1.0461E-8, -1.4480E-8, -3.3649E-8, 0.0000E+0, 0.0000E+0, 0.0000E+0,
   0.0000E+0, 0.0000E+0, -7.9848E-9, 8.5758E-9, -4.7062E-10, 2.0922E-8, 2.6622E-8, 2.0710E-8, 0.0000E+0, 0.0000E+0,
   0.0000E+0, 0.0000E+0, 0.0000E+0, -3.1799E-9, 3.1059E-9, -6.5482E-9, 1.2349E-9, -5.3472E-9, 0.0000E+0, 0.0000E+0,
   0.0000E+0, 0.0000E+0, 0.0000E+0, 2.7361E-9, 6.9804E-10, -3.7047E-9, 5.9322E-9, 0.0000E+0, 0.0000E+0, 0.0000E+0,
   0.0000E+0, 0.0000E+0, 1.0747E-9, -1.9375E-9, 6.8652E-10, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0,
   1.2945E-10, -1.0027E-9, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 1.8801E-10, 0.0000E+0, 0.0000E+0,
   0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0,
   0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0};

// H Values
const double IGRF::_H[] = {0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0,
   0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 4.7971E-6, -4.9287E-6, -3.5303E-7, 1.5678E-6,
   4.8088E-7, -3.9318E-7, -1.9189E-6, 6.7702E-7, -2.7519E-6, 7.7852E-7, -4.6639E-8, -9.8673E-7, -1.5572E-6, -5.5590E-7,
   4.7425E-7, -7.3841E-7, 1.5140E-6, 4.9615E-7, -5.6474E-7, -1.0263E-6, 1.1734E-6, -8.4277E-8, 8.1810E-7, 3.1805E-7,
   6.1901E-7, -4.2564E-7, 3.7838E-7, -5.6145E-7, 5.8681E-7, 1.1673E-7, 5.5088E-7, 9.7920E-7, 7.6029E-7, -2.2958E-7,
   1.2335E-6, 2.0530E-6, -2.4367E-7, 3.5496E-8, -3.6397E-7, 3.0131E-7, -3.9035E-7, -3.8336E-7, 5.1423E-7, -2.6347E-7,
   -1.0712E-6, -4.9206E-7, 7.0296E-8, 1.6986E-8, 2.0993E-8, 2.4026E-7, -2.3247E-7, -5.8393E-7, 1.2674E-7, 1.0021E-7,
   -8.3505E-7, 4.2048E-8, -6.6358E-8, 3.9132E-8, 1.3570E-7, -2.4792E-8, -1.8824E-8, 1.4581E-7, -4.5155E-8, -1.4240E-9,
   -2.2812E-8, 7.5335E-9, -8.4181E-8, -1.0913E-7, -1.1705E-8, 1.0686E-7, 1.3161E-9, -1.0336E-8, -2.2911E-8, -3.1864E-8,
   1.7558E-8, -1.4279E-8, 5.1160E-9, -3.1857E-9, -2.2037E-8, 5.1087E-9, 2.7229E-8, -5.1646E-9, -5.4407E-9, -8.4892E-9,
   1.4194E-8, -1.3920E-9, -2.7815E-10, -3.0110E-9, 3.9744E-10, -1.1355E-9, -4.4539E-10};

// Change of H Values
const double IGRF::_DH[] = {0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0,
   0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, -2.6600E-8, -4.7458E-8, 2.5107E-8,
   -7.1942E-9, 6.0999E-9, 0.0000E+0, 2.8376E-8, -2.0109E-8, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0,
   -1.2211E-8, -7.7460E-10, 2.0740E-8, 1.3065E-8, -3.1383E-8, 1.1584E-8, 1.6825E-8, 0.0000E+0, 0.0000E+0, 0.0000E+0,
   0.0000E+0, 0.0000E+0, 1.4230E-9, 6.0658E-9, -5.6475E-9, -6.9740E-9, -4.0957E-9, 4.1420E-9, 0.0000E+0, 0.0000E+0,
   0.0000E+0, 0.0000E+0, 0.0000E+0, -3.8455E-9, 7.5430E-9, 1.0914E-9, -3.7047E-9, 1.3368E-8, 0.0000E+0, 0.0000E+0,
   0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 2.0941E-9, -3.7047E-9, -2.9661E-9, 0.0000E+0, 0.0000E+0, 0.0000E+0,
   0.0000E+0, 0.0000E+0, 6.7169E-10, 2.4218E-10, -2.0596E-9, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0,
   -1.2945E-10, 7.5205E-10, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0,
   0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0,
   0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0, 0.0000E+0};

// Delta Distance
const double IGRF::_D = 100.0;
