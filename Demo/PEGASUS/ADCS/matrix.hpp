

// ADCS - MATRIX


// Includes
#include <cmath>
#include "vector.hpp"


// Preprocessor Directives
#pragma once


// Namespace ADCS
namespace ADCS
{
   // Class Matrix
   class Matrix;

   // Multiply
   const Matrix operator *(const numeric_t& a, const Matrix& A);

   // Add
   const Matrix operator +(const numeric_t& a, const Matrix& A);
}


// Class Matrix
class ADCS::Matrix
{
public:

   // Identity Matrix
   static const Matrix IDENTITY;

   // Constructor
   Matrix(const numeric_t& a = NUM(0.0));
   Matrix(const Vector& v);
   Matrix(const Vector& v1, const Vector& v2, const Vector& v3);

   // Sign
   const Matrix& operator +(void) const;
   const Matrix operator -(void) const;

   // Compare
   bool operator ==(const Matrix& A) const;
   bool operator !=(const Matrix& A) const;

   // Multiply
   const Matrix operator *(const numeric_t& a) const;
   const Vector operator *(const Vector& v) const;
   const Matrix operator *(const Matrix& A) const;
   Matrix& operator *=(const numeric_t& a);
   Matrix& operator *=(const Matrix& A);

   // Divide
   const Matrix operator /(const numeric_t& a) const;
   Matrix& operator /=(const numeric_t& a);

   // Add
   const Matrix operator +(const numeric_t& a) const;
   const Matrix operator +(const Matrix& A) const;
   Matrix& operator +=(const numeric_t& a);
   Matrix& operator +=(const Matrix& A);

   // Subtract
   const Matrix operator -(const numeric_t& a) const;
   const Matrix operator -(const Matrix& A) const;
   Matrix& operator -=(const numeric_t& a);
   Matrix& operator -=(const Matrix& A);

   // Get Element
   numeric_t& operator ()(uint8_t row, uint8_t col);
   const numeric_t& operator ()(uint8_t row, uint8_t col) const;
   numeric_t& at(uint8_t row, uint8_t col);
   const numeric_t& at(uint8_t row, uint8_t col) const;

   // Swap Columns
   void swap_cols(uint8_t i, uint8_t j);

   // Swap Rows
   void swap_rows(uint8_t i, uint8_t j);

   // Transpose
   const Matrix transpose(void) const;

private:

   // Epsilon
   static const numeric_t _EPSILON;

   // Check if equal
   static bool _equal(const numeric_t& x, const numeric_t& y);

   // Generate Identity Matrix
   static const Matrix _identity(void);

   // Get Element (Indices are not checked)
   numeric_t& _at(uint8_t row, uint8_t col);
   const numeric_t& _at(uint8_t row, uint8_t col) const;

   // Variables
   numeric_t _a[3][3];
};


// Plus Sign
inline const ADCS::Matrix& ADCS::Matrix::operator +(void) const
{
   // Return Reference
   return *this;
}


// Compare
inline bool ADCS::Matrix::operator !=(const Matrix& A) const
{
   // Return Result
   return !(*this == A);
}


// Multiplication Assignment
inline ADCS::Matrix& ADCS::Matrix::operator *=(const Matrix& A)
{
   // Multiplication Assignment and return Reference
   return (*this = *this * A);
}


// Divide
inline const ADCS::Matrix ADCS::Matrix::operator /(const numeric_t& a) const
{
   // Multiply and return Result
   return (*this * ((a == NUM(0.0)) ? NAN : (NUM(1.0) / a)));
}


// Division Assignment
inline ADCS::Matrix& ADCS::Matrix::operator /=(const numeric_t& a)
{
   // Multiplication Assignment and return Reference
   return (*this *= ((a == NUM(0.0)) ? NAN : (NUM(1.0) / a)));
}


// Subtract
inline const ADCS::Matrix ADCS::Matrix::operator -(const numeric_t& a) const
{
   // Add Scalar and return Result
   return (*this + (-a));
}


// Subtraction Assignment
inline ADCS::Matrix& ADCS::Matrix::operator -=(const numeric_t& a)
{
   // Subtraction Assignment and return Reference
   return (*this += -a);
}


// Get Element
inline ADCS::numeric_t& ADCS::Matrix::operator ()(uint8_t row, uint8_t col)
{
   // Return Element
   return at(row, col);
}


// Get Element
inline const ADCS::numeric_t& ADCS::Matrix::operator ()(uint8_t row, uint8_t col) const
{
   // Return Element
   return at(row, col);
}


// Multiply
inline const ADCS::Matrix ADCS::operator *(const numeric_t& a, const Matrix& A)
{
   // Return Result
   return (A * a);
}


// Add
inline const ADCS::Matrix ADCS::operator +(const numeric_t& a, const Matrix& A)
{
   // Return Result
   return (A + a);
}
