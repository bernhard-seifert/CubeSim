

// ADCS - VECTOR


// Includes
#include <cmath>
#include <limits>
#include "vector.hpp"


// Unit Vectors
const ADCS::Vector ADCS::Vector::X(1.0, 0.0, 0.0);
const ADCS::Vector ADCS::Vector::Y(0.0, 1.0, 0.0);
const ADCS::Vector ADCS::Vector::Z(0.0, 0.0, 1.0);


// Minus Sign
const ADCS::Vector ADCS::Vector::operator -(void) const
{
   // Return Result
   return Vector(-x(), -y(), -z());
}


// Compare
bool ADCS::Vector::operator ==(const Vector& v) const
{
   // Return Result
   return (_equal(x(), v.x()) && _equal(y(), v.y()) && _equal(z(), v.z()));
}


// Multiply
const ADCS::Vector ADCS::Vector::operator *(const numeric_t& a) const
{
   // Return Result
   return Vector(x() * a, y() * a, z() * a);
}


// Multiply
ADCS::numeric_t ADCS::Vector::operator *(const Vector& v) const
{
   // Return Result
   return (x() * v.x() + y() * v.y() + z() * v.z());
}


// Multiplication Assignment
ADCS::Vector& ADCS::Vector::operator *=(const numeric_t& a)
{
   // Multiply and assign
   x(x() * a);
   y(y() * a);
   z(z() * a);

   // Return Reference
   return *this;
}


// Divide
const ADCS::Vector ADCS::Vector::operator /(const numeric_t& a) const
{
   // Check Parameter
   if (a == 0.0)
   {
      // Return invalid Vector
      return Vector(NAN, NAN, NAN);
   }

   // Return Result
   return Vector(x() / a, y() / a, z() / a);
}


// Division Assignment
ADCS::Vector& ADCS::Vector::operator /=(const numeric_t& a)
{
   // Check Parameter
   if (a == 0.0)
   {
      // Assign invalid Vector
      x(NAN);
      y(NAN);
      z(NAN);
   }
   else
   {
      // Divide and assign
      x(x() / a);
      y(y() / a);
      z(z() / a);
   }

   // Return Reference
   return *this;
}


// Add
const ADCS::Vector ADCS::Vector::operator +(const Vector& v) const
{
   // Return Result
   return Vector(x() + v.x(), y() + v.y(), z() + v.z());
}


// Addition Assignment
ADCS::Vector& ADCS::Vector::operator +=(const Vector& v)
{
   // Add and assign
   x(x() + v.x());
   y(y() + v.y());
   z(z() + v.z());

   // Return Reference
   return *this;
}



// Subtract
const ADCS::Vector ADCS::Vector::operator -(const Vector& v) const
{
   // Return Result
   return Vector(x() - v.x(), y() - v.y(), z() - v.z());
}


// Subtraction Assignment
ADCS::Vector& ADCS::Vector::operator -=(const Vector& v)
{
   // Subtract and assign
   x(x() - v.x());
   y(y() - v.y());
   z(z() - v.z());

   // Return Reference
   return *this;
}


// Compute Cross Product
const ADCS::Vector ADCS::Vector::operator ^(const Vector& v) const
{
   // Return Result
   return Vector(y() * v.z() - z() * v.y(), z() * v.x() - x() * v.z(), x() * v.y() - y() * v.x());
}


// Compute Angle
ADCS::numeric_t ADCS::Vector::operator %(const Vector& v) const
{
   // Compute Norm
   numeric_t norm_ = norm() * v.norm();

   // Compute and return Angle
   return ((norm_ == 0.0) ? NAN : std::acos(*this * v / norm_));
}


// Compute Norm
ADCS::numeric_t ADCS::Vector::norm(void) const
{
   // Return Result
   return sqrt(x() * x() + y() * y() + z() * z());
}


// Compute Unit Vector
const ADCS::Vector ADCS::Vector::unit(void) const
{
   // Compute Norm
   numeric_t norm_ = norm();

   // Check Norm
   if (norm_ == 0.0)
   {
      // Return invalid Vector
      return Vector(NAN, NAN, NAN);
   }

   // Return Result
   return Vector(x() / norm_, y() / norm_, z() / norm_);
}


// Epsilon
const ADCS::numeric_t ADCS::Vector::_EPSILON = std::numeric_limits<numeric_t>::epsilon() * 100;


// Check if equal
bool ADCS::Vector::_equal(const numeric_t& x, const numeric_t& y)
{
   // Compute Difference
   numeric_t d = x - y;

   // Return Result
   return ((-_EPSILON <= d) && (d <= _EPSILON));
}
