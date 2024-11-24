

// CUBESIM - SYSTEM - GNSS


// Copyright (c) 2022 Bernhard Seifert
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sub-license, and / or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
// Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
// OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


// Includes
#include <random>
#include "../system.hpp"
#include "../celestial_body/earth.hpp"


// Preprocessor Directives
#pragma once


// Class GNSS
class CubeSim::System::GNSS : public System
{
public:

   // Clone
   virtual System* clone(void) const;

   // Get Location
   const Location location(void) const;

protected:

   // Constructor
   GNSS(double spatial_accuracy = _SPATIAL_ACCURACY, double temporal_accuracy = _TEMPORAL_ACCURACY);

   // Copy Constructor
   GNSS(const GNSS& gnss);

   // Spatial Accuracy [m]
   double _spatial_accuracy(void) const;
   void _spatial_accuracy(double spatial_accuracy);

   // Temporal Accuracy [s]
   double _temporal_accuracy(void) const;
   void _temporal_accuracy(double temporal_accuracy);

private:

   // Default spatial Accuracy [m]
   static const double _SPATIAL_ACCURACY;

   // Default temporal Accuracy [s]
   static const double _TEMPORAL_ACCURACY;

   // Variables
   double _spatial_accuracy_;
   double _temporal_accuracy_;
   mutable const CelestialBody* _earth;
   mutable std::default_random_engine _generator;
   mutable std::normal_distribution<double> _distribution;
};


// Clone
inline CubeSim::System* CubeSim::System::GNSS::clone(void) const
{
   // Return Copy
   return new GNSS(*this);
}


// Constructor
inline CubeSim::System::GNSS::GNSS(double spatial_accuracy, double temporal_accuracy) : _earth(),
   _distribution(0.0, 1.0)
{
   // Initialize
   _spatial_accuracy(spatial_accuracy);
   _temporal_accuracy(temporal_accuracy);
}


// Copy Constructor
inline CubeSim::System::GNSS::GNSS(const GNSS& gnss) : System(gnss), _spatial_accuracy_(gnss._spatial_accuracy_),
   _temporal_accuracy_(gnss._temporal_accuracy_), _earth(), _distribution(gnss._distribution)
{
}


// Get spatial Accuracy [m]
inline double CubeSim::System::GNSS::_spatial_accuracy(void) const
{
   // Return spatial Accuracy
   return _spatial_accuracy_;
}


// Set spatial Accuracy [m]
inline void CubeSim::System::GNSS::_spatial_accuracy(double spatial_accuracy)
{
   // Check spatial Accuracy
   if (spatial_accuracy < 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set spatial Accuracy
   _spatial_accuracy_ = spatial_accuracy;
}


// Get temporal Accuracy [s]
inline double CubeSim::System::GNSS::_temporal_accuracy(void) const
{
   // Return temporal Accuracy
   return _temporal_accuracy_;
}


// Set temporal Accuracy [s]
inline void CubeSim::System::GNSS::_temporal_accuracy(double temporal_accuracy)
{
   // Check temporal Accuracy
   if (temporal_accuracy < 0.0)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set temporal Accuracy
   _temporal_accuracy_ = temporal_accuracy;
}
