


// ADCS - INFO


// Includes
#include <stdint.h>
#include "float16.h"


// Preprocessor Directives
#pragma once


// Namespace ADCS
namespace ADCS
{
   // Class Info
   class Info;
}


// Class Info
class ADCS::Info
{
public:

   // Rotation Modes
   // 0: direct
   // 1: Propagation
   static const uint8_t ROTATION_MODE_DIRECT = 0;
   static const uint8_t ROTATION_MODE_PROPAGATION = 1;


   // Angular Rate Modes
   // 0: from Gyro
   // 1: from Rotational Matrix
   static const uint8_t ANGULAR_RATE_MODE_GYRO = 0;
   static const uint8_t ANGULAR_RATE_MODE_MATRIX = 1;

   // Eclipse Information
   // 0: unknown
   // 1: inside
   // 2: outside
   static const uint8_t ECLIPSE_UNKNOWN = 0;
   static const uint8_t ECLIPSE_INSIDE = 1;
   static const uint8_t ECLIPSE_OUTSIDE = 2;


   // Location
   class Location
   {
   public:

      // Variables
      float16_t latitude;
      float16_t longitude;
      float16_t altitude;
   };


   // Orbit
   class Orbit
   {
   public:

      // Variables
      float16_t semimajor_axis;
      float16_t eccentricity;
      float16_t argument_periapsis;
      float16_t longitude_ascending;
      float16_t inclination;
      float16_t mean_anomaly;
      uint32_t datetime;
   };


   // Vector
   class Vector
   {
   public:

      // Variables
      float16_t x;
      float16_t y;
      float16_t z;
   };


   // Vector2
   class Vector2
   {
   public:

      // Variables
      float16_t xm;
      float16_t xp;
      float16_t ym;
      float16_t yp;
      float16_t zm;
      float16_t zp;
   };


   // Variables
   uint32_t timestamp;
   uint8_t status;
   uint8_t SAA;
   uint8_t eclipse;
   uint8_t rotation_mode;
   uint8_t angular_rate_mode;
   Orbit orbit;
   Location location;
   Vector gyro;
   Vector angular_rate;
   Vector2 photo;
   Vector sun;
   float16_t albedo;
   Vector magnetometer;

   // Pointing Error
   struct
   {
      float16_t pitch;
      float16_t yaw;
      float16_t roll;
   }
   error;

   // Magnetorquer Currents
   Vector torquer;
};
