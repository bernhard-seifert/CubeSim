

// ADCS - MATRIX


// Includes
#include <algorithm>
#include "matrix.hpp"


// Identity Matrix
const ADCS::Matrix ADCS::Matrix::IDENTITY = _identity();


// Constructor
ADCS::Matrix::Matrix(const numeric_t& a)
{
   // Parse Rows
   for (uint8_t i = 1; i <= 3; ++i)
   {
      // Parse Columns
      for (uint8_t j = 1; j <= 3; ++j)
      {
         // Initialize
         _at(i, j) = a;
      }
   }
}


// Constructor
ADCS::Matrix::Matrix(const Vector& v)
{
   // Parse Rows
   for (uint8_t i = 1; i <= 3; ++i)
   {
      // Parse Columns
      for (uint8_t j = 1; j <= 3; ++j)
      {
         // Initialize
         _at(i, j) = (i == j) ? v(i) : NUM(0.0);
      }
   }
}


// Constructor
ADCS::Matrix::Matrix(const Vector& v1, const Vector& v2, const Vector& v3)
{
   // Initialize
   _at(1, 1) = v1(1);
   _at(2, 1) = v1(2);
   _at(3, 1) = v1(3);
   _at(1, 2) = v2(1);
   _at(2, 2) = v2(2);
   _at(3, 2) = v2(3);
   _at(1, 3) = v3(1);
   _at(2, 3) = v3(2);
   _at(3, 3) = v3(3);
}


// Minus Sign
const ADCS::Matrix ADCS::Matrix::operator -(void) const
{
   // Matrix
   Matrix A;

   // Parse Rows
   for (uint8_t i = 1; i <= 3; ++i)
   {
      // Parse Columns
      for (uint8_t j = 1; j <= 3; ++j)
      {
         // Set Element
         A._at(i, j) = -_at(i, j);
      }
   }

   // Return Result
   return A;
}


// Compare
bool ADCS::Matrix::operator ==(const Matrix& A) const
{
   // Parse Rows
   for (uint8_t i = 1; i <= 3; ++i)
   {
      // Parse Columns
      for (uint8_t j = 1; j <= 3; ++j)
      {
         // Compare Elements
         if (!_equal(_at(i, j), A._at(i, j)))
         {
            // Return Result
            return false;
         }
      }
   }

   // Return Result
   return true;
}


// Multiply
const ADCS::Matrix ADCS::Matrix::operator *(const numeric_t& a) const
{
   // Matrix
   Matrix A;

   // Parse Rows
   for (uint8_t i = 1; i <= 3; ++i)
   {
      // Parse Columns
      for (uint8_t j = 1; j <= 3; ++j)
      {
         // Set Element
         A._at(i, j) = _at(i, j) * a;
      }
   }

   // Return Result
   return A;
}


// Multiply
const ADCS::Vector ADCS::Matrix::operator *(const Vector& v) const
{
   // Vector
   Vector u;

   // Parse Rows
   for (uint8_t i = 1; i <= 3; ++i)
   {
      // Sum
      numeric_t s = NUM(0.0);

      // Parse Columns
      for (uint8_t j = 1; j <= 3; ++j)
      {
         // Update Sum
         s += _at(i, j) * v(j);
      }

      // Set Element
      u(i) = s;
   }

   // Return Result
   return u;
}


// Multiply
const ADCS::Matrix ADCS::Matrix::operator *(const Matrix& A) const
{
   // Matrix
   Matrix B;

   // Parse Rows
   for (uint8_t i = 1; i <= 3; ++i)
   {
      // Parse Columns
      for (uint8_t j = 1; j <= 3; ++j)
      {
         // Sum
         numeric_t s = NUM(0.0);

         // Parse Elements
         for (uint8_t k = 1; k <= 3; ++k)
         {
            // Update Sum
            s += _at(i, k) * A._at(k, j);
         }

         // Set Element
         B._at(i, j) = s;
      }
   }

   // Return Result
   return B;
}


// Multiplication Assignment
ADCS::Matrix& ADCS::Matrix::operator *=(const numeric_t& a)
{
   // Parse Rows
   for (uint8_t i = 1; i <= 3; ++i)
   {
      // Parse Columns
      for (uint8_t j = 1; j <= 3; ++j)
      {
         // Update Element
         _at(i, j) *= a;
      }
   }

   // Return Reference
   return *this;
}


// Add
const ADCS::Matrix ADCS::Matrix::operator +(const numeric_t& a) const
{
   // Matrix
   ADCS::Matrix A;

   // Parse Rows
   for (uint8_t i = 1; i <= 3; ++i)
   {
      // Parse Columns
      for (uint8_t j = 1; j <= 3; ++j)
      {
         // Set Element
         A._at(i, j) = _at(i, j) + a;
      }
   }

   // Return Result
   return A;
}


// Add
const ADCS::Matrix ADCS::Matrix::operator +(const Matrix& A) const
{
   // Matrix
   Matrix B;

   // Parse Rows
   for (uint8_t i = 1; i <= 3; ++i)
   {
      // Parse Columns
      for (uint8_t j = 1; j <= 3; ++j)
      {
         // Set Element
         B._at(i, j) = _at(i, j) + A._at(i, j);
      }
   }

   // Return Result
   return B;
}


// Addition Assignment
ADCS::Matrix& ADCS::Matrix::operator +=(const numeric_t& a)
{
   // Parse Rows
   for (uint8_t i = 1; i <= 3; ++i)
   {
      // Parse Columns
      for (uint8_t j = 1; j <= 3; ++j)
      {
         // Update Element
         _at(i, j) += a;
      }
   }

   // Return Reference
   return *this;
}


// Addition Assignment
ADCS::Matrix& ADCS::Matrix::operator +=(const Matrix& A)
{
   // Parse Rows
   for (uint8_t i = 1; i <= 3; ++i)
   {
      // Parse Columns
      for (uint8_t j = 1; j <= 3; ++j)
      {
         // Update Element
         _at(i, j) += A._at(i, j);
      }
   }

   // Return Reference
   return *this;
}


// Subtract
const ADCS::Matrix ADCS::Matrix::operator -(const Matrix& A) const
{
   // Matrix
   Matrix B;

   // Parse Rows
   for (uint8_t i = 1; i <= 3; ++i)
   {
      // Parse Columns
      for (uint8_t j = 1; j <= 3; ++j)
      {
         // Set Element
         B._at(i, j) = _at(i, j) - A._at(i, j);
      }
   }

   // Return Result
   return B;
}


// Subtraction Assignment
ADCS::Matrix& ADCS::Matrix::operator -=(const Matrix& A)
{
   // Parse Rows
   for (uint8_t i = 1; i <= 3; ++i)
   {
      // Parse Columns
      for (uint8_t j = 1; j <= 3; ++j)
      {
         // Update Element
         _at(i, j) -= A._at(i, j);
      }
   }

   // Return Reference
   return *this;
}


// Get Element
ADCS::numeric_t& ADCS::Matrix::at(uint8_t row, uint8_t col)
{
   // Check Row and Column
   if (!row || (3 < row) || !col || (3 < col))
   {
      // Use first Element
      row = 1;
      col = 1;
   }

   // Return Element
   return _at(row, col);
}


// Get Element
const ADCS::numeric_t& ADCS::Matrix::at(uint8_t row, uint8_t col) const
{
   // Check Row and Column
   if (!row || (3 < row) || !col || (3 < col))
   {
      // Use first Element
      row = 1;
      col = 1;
   }

   // Return Element
   return _at(row, col);
}


// Swap Columns
void ADCS::Matrix::swap_cols(uint8_t i, uint8_t j)
{
   // Check Indices
   if (i && (i <= 3) && j && (j <= 3) && (i != j))
   {
      // Parse Rows
      for (uint8_t k = 1; k <= 3; ++k)
      {
         // Swap Elements
         std::swap(_at(k, i), _at(k, j));
      }
   }
}


// Swap Rows
void ADCS::Matrix::swap_rows(uint8_t i, uint8_t j)
{
   // Check Indices
   if (i && (i <= 3) && j && (j <= 3) && (i != j))
   {
      // Parse Columns
      for (uint8_t k = 1; k <= 3; ++k)
      {
         // Swap Elements
         std::swap(_at(i, k), _at(j, k));
      }
   }
}


// Transpose
const ADCS::Matrix ADCS::Matrix::transpose(void) const
{
   // Matrix
   Matrix A;

   // Parse Rows
   for (uint8_t i = 1; i <= 3; ++i)
   {
      // Parse Columns
      for (uint8_t j = 1; j <= 3; ++j)
      {
         // Set Element
         A._at(j, i) = _at(i, j);
      }
   }

   // Return Result
   return A;
}


// Epsilon
const ADCS::numeric_t ADCS::Matrix::_EPSILON = std::numeric_limits<numeric_t>::epsilon() * 100;


// Check if equal
bool ADCS::Matrix::_equal(const numeric_t& x, const numeric_t& y)
{
   // Compute Difference
   numeric_t d = x - y;

   // Return Result
   return ((-_EPSILON <= d) && (d <= _EPSILON));
}


// Generate Identity Matrix
const ADCS::Matrix ADCS::Matrix::_identity(void)
{
   // Matrix
   Matrix A;

   // Parse Elements
   for (uint8_t i = 1; i <= 3; ++i)
   {
      // Initialize
      A._at(i, i) = NUM(1.0);
   }

   // Return Result
   return A;
}


// Get Element (Indices are not checked)
inline ADCS::numeric_t& ADCS::Matrix::_at(uint8_t row, uint8_t col)
{
   // Return Element
   return _a[row - 1][col - 1];
}


// Get Element (Indices are not checked)
inline const ADCS::numeric_t& ADCS::Matrix::_at(uint8_t row, uint8_t col) const
{
   // Return Element
   return _a[row - 1][col - 1];
}
