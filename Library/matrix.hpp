

// MATRIX 2.3.0


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
#include <vector.hpp>


// Preprocessor Directives
#pragma once


// Class Matrix
template <typename T> class Matrix
{
public:

   // Class Exception
   class Exception;

   // Identity Matrix
   static const Matrix<T> identity(size_t dim);

   // Constructor
   Matrix(size_t dim);
   Matrix(size_t rows, size_t cols, const T& a = T());
   Matrix(const Vector<T>& v);
   Matrix(const std::initializer_list<T>& list);

   // Convert to Vector
   operator const Vector<T>(void) const;

   // Sign
   const Matrix<T>& operator +(void) const;
   const Matrix<T> operator -(void) const;

   // Compare
   bool operator ==(const Matrix<T>& A) const;
   bool operator !=(const Matrix<T>& A) const;

   // Assign
   Matrix<T>& operator =(const Vector<T>& v);
   Matrix<T>& operator =(const std::initializer_list<T>& list);

   // Multiply
   const Matrix<T> operator *(const T& a) const;
   const Vector<T> operator *(const Vector<T>& v) const;
   const Matrix<T> operator *(const Matrix<T>& A) const;
   Matrix<T>& operator *=(const T& a);
   Matrix<T>& operator *=(const Vector<T>& v);
   Matrix<T>& operator *=(const Matrix<T>& A);

   // Divide by Scalar
   const Matrix<T> operator /(const T& a) const;
   Matrix<T>& operator /=(const T& a);

   // Add
   const Matrix<T> operator +(const T& a) const;
   const Matrix<T> operator +(const Matrix<T>& A) const;
   Matrix<T>& operator +=(const T& a);
   Matrix<T>& operator +=(const Matrix<T>& A);

   // Subtract
   const Matrix<T> operator -(const T& a) const;
   const Matrix<T> operator -(const Matrix<T>& A) const;
   Matrix<T>& operator -=(const T& a);
   Matrix<T>& operator -=(const Matrix<T>& A);

   // Check if asymmetric
   bool asymmetric(void) const;

   // Get Element
   T& operator ()(size_t row, size_t col);
   const T& operator ()(size_t row, size_t col) const;
   T& at(size_t row, size_t col);
   const T& at(size_t row, size_t col) const;

   // Compute Cofactor
   const T cofactor(size_t row, size_t col) const;

   // Number of Columns
   size_t cols(void) const;
   void cols(size_t cols, const T& a = T());

   // Decompose in LU Shape
   void decompose_LU(Matrix<T>& L, Matrix<T>& U) const;

   // Decompose in LUP Shape
   const T decompose_LUP(Matrix<T>& L, Matrix<T>& U, Matrix<T>& P) const;

   // Compute Determinant
   const T det(void) const;

   // Check if diagonal
   bool diagonal(void) const;

   // Epsilon
   const T epsilon(void) const;
   void epsilon(const T& epsilon);

   // Compute Inverse
   const Matrix<T> inverse(void) const;

   // Find greatest Element
   T& max(void);
   const T& max(void) const;

   // Compute Mean Value
   const T mean(void) const;

   // Find smallest Element
   T& min(void);
   const T& min(void) const;

   // Check if orthogonal
   bool orthogonal(void) const;

   // Check if regular
   bool regular(void) const;

   // Resize
   void resize(size_t rows, size_t cols, const T& a = T());

   // Number of Rows
   size_t rows(void) const;
   void rows(size_t rows, const T& a = T());

   // Check if singular
   bool singular(void) const;

   // Solve Linear Equation Set
   const Vector<T> solve(const Vector<T>& v) const;

   // Check if square
   bool square(void) const;

   // Compute Sum
   const T sum(void) const;

   // Check if symmetric
   bool symmetric(void) const;

   // Swap Columns
   void swap_cols(size_t i, size_t j);

   // Swap Rows
   void swap_rows(size_t i, size_t j);

   // Compute Trace
   const T trace(void) const;

   // Transpose
   const Matrix<T> transpose(void) const;

   // Check if triangular
   bool triangular(void) const;

protected:

   // Get Element (Indices are not checked)
   T& _at(size_t row, size_t col);
   const T& _at(size_t row, size_t col) const;

private:

   // Check if equal
   bool _equal(const T& x, const T& y) const;

   // Variables
   size_t _cols;
   size_t _rows;
   T _epsilon;
   std::vector<T> _a;

   // Friends
   template <typename U> friend const Matrix<U> operator |(const Vector<U>& u, const Vector<U>& v);
};


// Class Exception
template <typename T> class Matrix<T>::Exception
{
public:

   // Class Dimension
   class Dimension;

   // Class Failed
   class Failed;

   // Class Parameter
   class Parameter;

private:

   // Virtual Function for RTTI
   virtual void _func() {}
};


// Class Dimension
template <typename T> class Matrix<T>::Exception::Dimension : public Matrix<T>::Exception
{
};


// Class Failed
template <typename T> class Matrix<T>::Exception::Failed : public Matrix<T>::Exception
{
};


// Class Parameter
template <typename T> class Matrix<T>::Exception::Parameter : public Matrix<T>::Exception
{
};


// Multiply with Scalar
template <typename T> const Matrix<T> operator *(const T& a, const Matrix<T>& A);

// Add Scalar
template <typename T> const Matrix<T> operator +(const T& a, const Matrix<T>& A);

// Outer Product
template <typename T> const Matrix<T> operator |(const Vector<T>& u, const Vector<T>& v);


// Identity Matrix
template <typename T> const Matrix<T> Matrix<T>::identity(size_t dim)
{
   // Matrix
   Matrix<T> I(dim);

   // Parse Rows
   for (size_t i = 1; i <= dim; ++i)
   {
      // Set Element
      I._at(i, i) = 1;
   }

   // Return Identity Matrix
   return I;
}


// Constructor
template <typename T> inline Matrix<T>::Matrix(size_t dim) : Matrix(dim, dim)
{
}


// Constructor
template <typename T> Matrix<T>::Matrix(size_t rows, size_t cols, const T& a) : _epsilon()
{
   // Check Parameters
   if ((rows < 1) || (cols < 1))
   {
      // Exception
      throw Exception::Parameter();
   }

   // Initialize
   _cols = cols;
   _rows = rows;
   _a.resize(rows * cols, a);
}


// Constructor
template <typename T> inline Matrix<T>::Matrix(const Vector<T>& v) : _epsilon()
{
   // Initialize
   *this = v;
}


// Constructor
template <typename T> inline Matrix<T>::Matrix(const std::initializer_list<T>& list) : _epsilon()
{
   // Initialize
   *this = list;
}


// Convert to Vector
template <typename T> Matrix<T>::operator const Vector<T>(void) const
{
   // Create Vector
   Vector<T> v(rows() * cols());

   // Index
   size_t n = 1;

   // Parse Rows
   for (size_t i = 1; i <= rows(); ++i)
   {
      // Parse Columns
      for (size_t j = 1; j <= cols(); ++j)
      {
         // Set Element
         v(n++) = _at(i, j);
      }
   }

   // Return Result
   return v;
}


// Plus Sign
template <typename T> inline const Matrix<T>& Matrix<T>::operator +(void) const
{
   // Return Reference
   return *this;
}


// Minus Sign
template <typename T> const Matrix<T> Matrix<T>::operator -(void) const
{
   // Matrix
   Matrix<T> A(rows(), cols());

   // Parse Rows
   for (size_t i = 1; i <= rows(); ++i)
   {
      // Parse Columns
      for (size_t j = 1; j <= cols(); ++j)
      {
         // Set Element
         A._at(i, j) = -_at(i, j);
      }
   }

   // Return Result
   return A;
}


// Compare
template <typename T> bool Matrix<T>::operator ==(const Matrix<T>& A) const
{
   // Check Dimension
   if ((rows() != A.rows()) || (cols() != A.cols()))
   {
      // Return Result
      return false;
   }

   // Parse Rows
   for (size_t i = 1; i <= rows(); ++i)
   {
      // Parse Columns
      for (size_t j = 1; j <= cols(); ++j)
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


// Compare
template <typename T> inline bool Matrix<T>::operator !=(const Matrix<T>& A) const
{
   // Return Result
   return !(*this == A);
}


// Assign Vector
template <typename T> Matrix<T>& Matrix<T>::operator =(const Vector<T>& v)
{
   // Set Columns, Rows, Elements
   _cols = 1;
   _rows = v.dim();
   _a = v;
}


// Assign List
template <typename T> Matrix<T>& Matrix<T>::operator =(const std::initializer_list<T>& list)
{
   // Check Dimension
   if (!list.size())
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Columns, Rows, Elements
   _cols = 1;
   _rows = list.size();
   _a.assign(list.begin(), list.end());
}


// Multiply with Scalar
template <typename T> const Matrix<T> Matrix<T>::operator *(const T& a) const
{
   // Multiply, assign and return Vector
   return (Matrix<T>(*this) *= a);
}


// Multiply with Vector
template <typename T> const Vector<T> Matrix<T>::operator *(const Vector<T>& v) const
{
   // Check Dimension
   if (cols() != v.dim())
   {
      // Exception
      throw Exception::Dimension();
   }

   // Vector
   Vector<T> u(rows());

   // Parse Rows
   for (size_t i = 1; i <= rows(); ++i)
   {
      // Sum
      T s = T();

      // Parse Columns
      for (size_t j = 1; j <= cols(); ++j)
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


// Multiply with Matrix
template <typename T> const Matrix<T> Matrix<T>::operator *(const Matrix<T>& A) const
{
   // Check Dimension
   if (cols() != A.rows())
   {
      // Exception
      throw Exception::Dimension();
   }

   // Matrix
   Matrix<T> B(rows(), A.cols());

   // Parse Rows
   for (size_t i = 1; i <= rows(); ++i)
   {
      // Parse Columns
      for (size_t j = 1; j <= A.cols(); ++j)
      {
         // Sum
         T s = T();

         // Parse Elements
         for (size_t k = 1; k <= cols(); ++k)
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


// Multiply with Scalar and assign
template <typename T> Matrix<T>& Matrix<T>::operator *=(const T& a)
{
   // Parse Rows
   for (size_t i = 1; i <= rows(); ++i)
   {
      // Parse Columns
      for (size_t j = 1; j <= cols(); ++j)
      {
         // Update Element
         _at(i, j) *= a;
      }
   }

   // Return Reference
   return *this;
}


// Multiply with Vector and assign
template <typename T> inline Matrix<T>& Matrix<T>::operator *=(const Vector<T>& v)
{
   // Multiply with Vector, assign and return Reference
   return (*this = *this * v);
}


// Multiply with Matrix and assign
template <typename T> inline Matrix<T>& Matrix<T>::operator *=(const Matrix<T>& A)
{
   // Multiply with Matrix, assign and return Reference
   return (*this = *this * A);
}


// Divide by Scalar
template <typename T> const Matrix<T> Matrix<T>::operator /(const T& a) const
{
   // Check Value
   if (a == T())
   {
      // Exception
      throw Exception::Parameter();
   }

   // Multiply and return Result
   return (*this * (1 / a));
}


// Divide by Scalar and assign
template <typename T> Matrix<T>& Matrix<T>::operator /=(const T& a)
{
   // Check Value
   if (a == T())
   {
      // Exception
      throw Exception::Parameter();
   }

   // Multiplication Assignment and return Reference
   return (*this *= (1 / a));
}


// Add Scalar
template <typename T> inline const Matrix<T> Matrix<T>::operator +(const T& a) const
{
   // Add Scalar, assign and return Matrix
   return (Matrix<T>(*this) += a);
}


// Add Matrix
template <typename T> inline const Matrix<T> Matrix<T>::operator +(const Matrix<T>& A) const
{
   // Add Matrix and return Result
   return (Matrix<T>(*this) += A);
}


// Add Scalar and assign
template <typename T> Matrix<T>& Matrix<T>::operator +=(const T& a)
{
   // Parse Rows
   for (size_t i = 1; i <= rows(); ++i)
   {
      // Parse Columns
      for (size_t j = 1; j <= cols(); ++j)
      {
         // Update Element
         _at(i, j) += a;
      }
   }

   // Return Reference
   return *this;
}


// Add Matrix and assign
template <typename T> Matrix<T>& Matrix<T>::operator +=(const Matrix<T>& A)
{
   // Check Dimension
   if ((rows() != A.rows()) || (cols() != A.cols()))
   {
      // Exception
      throw Exception::Dimension();
   }

   // Parse Rows
   for (size_t i = 1; i <= rows(); ++i)
   {
      // Parse Columns
      for (size_t j = 1; j <= cols(); ++j)
      {
         // Update Element
         _at(i, j) += A._at(i, j);
      }
   }

   // Return Reference
   return *this;
}


// Subtract Scalar
template <typename T> inline const Matrix<T> Matrix<T>::operator -(const T& a) const
{
   // Subtract Scalar, assign and return Matrix
   return (Matrix<T>(*this) -= a);
}


// Subtract Matrix
template <typename T> inline const Matrix<T> Matrix<T>::operator -(const Matrix<T>& A) const
{
   // Subtract Matrix and return Result
   return (Matrix<T>(*this) -= A);
}


// Subtract Scalar and assign
template <typename T> inline Matrix<T>& Matrix<T>::operator -=(const T& a)
{
   // Parse Rows
   for (size_t i = 1; i <= rows(); ++i)
   {
      // Parse Columns
      for (size_t j = 1; j <= cols(); ++j)
      {
         // Update Element
         _at(i, j) -= a;
      }
   }

   // Return Reference
   return *this;
}


// Subtract Matrix and assign
template <typename T> Matrix<T>& Matrix<T>::operator -=(const Matrix<T>& A)
{
   // Check Dimension
   if ((rows() != A.rows()) || (cols() != A.cols()))
   {
      // Exception
      throw Exception::Dimension();
   }

   // Parse Rows
   for (size_t i = 1; i <= rows(); ++i)
   {
      // Parse Columns
      for (size_t j = 1; j <= cols(); ++j)
      {
         // Update Element
         _at(i, j) -= A._at(i, j);
      }
   }

   // Return Reference
   return *this;
}


// Check if asymmetric
template <typename T> bool Matrix<T>::asymmetric(void) const
{
   // Check Dimension
   if (!square())
   {
      // Exception
      throw Exception::Dimension();
   }

   // Parse Rows
   for (size_t i = 1; i <= rows(); ++i)
   {
      // Parse Columns
      for (size_t j = i; j <= rows(); ++j)
      {
         // Compare Elements
         if (!_equal(_at(i, j), -_at(j, i)))
         {
            // Return Result
            return false;
         }
      }
   }

   // Return Result
   return true;
}


// Get Element (Indices are not checked)
template <typename T> inline T& Matrix<T>::operator ()(size_t row, size_t col)
{
   // Return Element Reference
   return _at(row, col);
}


// Get Element (Indices are not checked)
template <typename T> inline const T& Matrix<T>::operator ()(size_t row, size_t col) const
{
   // Return Element Reference
   return _at(row, col);
}


// Get Element
template <typename T> T& Matrix<T>::at(size_t row, size_t col)
{
   // Return Element Reference
   return const_cast<T&>(const_cast<const Matrix<T>&>(*this).at(row, col));
}


// Get Element
template <typename T> const T& Matrix<T>::at(size_t row, size_t col) const
{
   // Check Indices
   if ((row < 1) || (rows() < row) || (col < 1) || (cols() < col))
   {
      // Exception
      throw Exception::Parameter();
   }

   // Return Element Reference
   return _at(row, col);
}


// Compute Cofactor
template <typename T> const T Matrix<T>::cofactor(size_t row, size_t col) const
{
   // Check Dimension and Indices
   if (!square() || (rows() < 2))
   {
      // Exception
      throw Exception::Dimension();
   }
   else if ((row < 1) || (rows() < row) || (col < 1) || (rows() < col))
   {
      // Exception
      throw Exception::Parameter();
   }

   // Matrix
   Matrix<T> A(rows() - 1);

   // Parse Rows
   for (size_t i = 1; i <= A.rows(); ++i)
   {
      // Compute Row
      size_t row_ = (i < row) ? i : (i + 1);

      // Parse Columns
      for (size_t j = 1; j <= A.rows(); ++j)
      {
         // Compute Column
         size_t col_ = (j < col) ? j : (j + 1);

         // Set Element
         A._at(i, j) = _at(row_, col_);
      }
   }

   // Compute and return Result
   return ((((row + col) % 2) ? -1 : 1) * A.det());
}


// Get Number of Columns
template <typename T> inline size_t Matrix<T>::cols(void) const
{
   // Return Number of Columns
   return _cols;
}


// Set Number of Columns
template <typename T> inline void Matrix<T>::cols(size_t cols, const T& a)
{
   // Resize
   resize(rows(), cols, a);
}


// Decompose in LU Shape
template <typename T> void Matrix<T>::decompose_LU(Matrix<T>& L, Matrix<T>& U) const
{
   // Check Dimension
   if (!square() || (rows() < 2))
   {
      // Exception
      throw Exception::Dimension();
   }

   // Resize Matrices
   L = Matrix<T>(rows());
   U = Matrix<T>(rows());

   // Parse Columns
   for (size_t i = 1; i <= rows(); ++i)
   {
      // Parse non-empty Rows of upper Matrix
      for (size_t j = 1; j <= i; ++j)
      {
         // Sum
         T s = T();

         // Parse known Summands
         for (size_t k = 1; k < j; ++k)
         {
            // Update Sum
            s += L._at(j, k) * U._at(k, i);
         }

         // Set Element
         U._at(j, i) = _at(j, i) - s;

         // Clear Element
         L._at(j, i) = T();
      }

      // Set diagonal Element of lower Matrix
      L._at(i, i) = 1;

      // Parse non-empty Rows of lower Matrix
      for (size_t j = (i + 1); j <= rows(); ++j)
      {
         // Sum
         T s = T();

         // Parse known Summands
         for (size_t k = 1; k < i; ++k)
         {
            // Update Sum
            s += L._at(j, k) * U._at(k, i);
         }

         // Check Element
         if (_equal(U._at(i, i), T()))
         {
            // Exception
            throw Exception::Failed();
         }

         // Set Element
         L._at(j, i) = (_at(j, i) - s) / U._at(i, i);

         // Clear Element
         U._at(j, i) = T();
      }
   }
}


// Decompose in LUP Shape
template <typename T> const T Matrix<T>::decompose_LUP(Matrix<T>& L, Matrix<T>& U, Matrix<T>& P) const
{
   // Check Dimension
   if (!square() || (rows() < 2))
   {
      // Exception
      throw Exception::Dimension();
   }

   // Copy Matrix
   Matrix<T> A(*this);

   // Reset Permutation Matrix
   P = identity(rows());

   // Determinant of Permutation Matrix
   T d = 1;

   // Parse Rows
   for (size_t i = 1; i <= rows(); ++i)
   {
      // Element and Row
      T a = T();
      size_t k = i;

      // Parse Columns
      for (size_t j = i; j <= rows(); ++j)
      {
         // Get Element
         T b = A._at(i, j);

         // Check Element
         if (b < T())
         {
            // Make absolute Value
            b = -b;
         }

         // Compare Elements
         if (a < b)
         {
            // Update Element and Row
            a = b;
            k = j;
         }
      }

      // Check Column
      if (k != i)
      {
         // Swap Columns of A and Rows of P
         A.swap_cols(i, k);
         P.swap_rows(i, k);

         // Update Determinant of Permutation Matrix
         d *= -1;
      }
   }

   // Decompose in LU Shape
   A.decompose_LU(L, U);

   // Return Determinant of Permutation Matrix
   return d;
}


// Compute Determinant
template <typename T> const T Matrix<T>::det(void) const
{
   // Check Dimension
   if (!square())
   {
      // Exception
      throw Exception::Dimension();
   }

   // Determinant
   T d = T();

   // Check Dimension
   if (rows() == 1)
   {
      // Set Determinant
      d = _at(1, 1);
   }
   else if (rows() == 2)
   {
      // Set Determinant
      d = _at(1, 1) * _at(2, 2) - _at(2, 1) * _at(1, 2);
   }
   else
   {
      try
      {
         // Matrices for LUP Decomposition
         Matrix<T> L(rows());
         Matrix<T> U(rows());
         Matrix<T> P(rows());

         // Decompose Matrix in LUP Shape
         d = decompose_LUP(L, U, P);

         // Parse Rows
         for (size_t i = 1; i <= rows(); ++i)
         {
            // Update Determinant
            d *= L._at(i, i) * U._at(i, i);
         }
      }
      catch (const Exception&)
      {
         // Null Element Occurrence List
         Vector<size_t> n(2 * rows());

         // Parse Rows
         for (size_t i = 1; i <= rows(); ++i)
         {
            // Parse Columns
            for (size_t j = 1; j <= rows(); ++j)
            {
               // Check Element
               if (_equal(_at(i, j), T()))
               {
                  // Update Null Element Occurrence List
                  ++n(i);
                  ++n(rows() + j);
               }
            }
         }

         // Maximum and Index
         size_t m = 0;
         size_t k = 1;

         // Parse Null Element Occurrence List
         for (size_t i = 1; i <= (2 * rows()); ++i)
         {
            // Check Item
            if (m < n(i))
            {
               // Update Maximum and Index
               m = n(i);
               k = i;
            }
         }

         // Check Index
         if (k < rows())
         {
            // Parse Columns
            for (size_t i = 1; i <= rows(); ++i)
            {
               // Check Element
               if (!_equal(_at(k, i), T()))
               {
                  // Update Determinant
                  d += _at(k, i) * cofactor(k, i);
               }
            }
         }
         else
         {
            // Update Index
            k -= rows();

            // Parse Rows
            for (size_t i = 1; i <= rows(); ++i)
            {
               // Check Element
               if (!_equal(_at(i, k), T()))
               {
                  // Update Determinant
                  d += _at(i, k) * cofactor(i, k);
               }
            }
         }
      }
   }

   // Return Result
   return d;
}


// Check if diagonal
template <typename T> bool Matrix<T>::diagonal(void) const
{
   // Check Dimension
   if (!square() || (rows() < 2))
   {
      // Exception
      throw Exception::Dimension();
   }

   // Parse Rows
   for (size_t i = 1; i <= rows(); ++i)
   {
      // Parse Columns
      for (size_t j = 1; j <= rows(); ++j)
      {
         // Check Element
         if ((i != j) && !_equal(_at(i, j), T()))
         {
            // Return Result
            return false;
         }
      }
   }

   // Return Result
   return true;
}


// Get Epsilon
template <typename T> inline const T Matrix<T>::epsilon(void) const
{
   // Return Epsilon
   return _epsilon;
}


// Set Epsilon
template <typename T> inline void Matrix<T>::epsilon(const T& epsilon)
{
   // Check Epsilon
   if (epsilon < T())
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Epsilon
   _epsilon = epsilon;
}


// Compute Inverse
template <typename T> const Matrix<T> Matrix<T>::inverse(void) const
{
   // Check Dimension
   if (!square())
   {
      // Exception
      throw Exception::Dimension();
   }

   // Matrix
   Matrix<T> A(rows());

   // Check Dimension
   if (rows() == 1)
   {
      // Check Element
      if (_equal(_at(1, 1), T()))
      {
         // Exception
         throw Exception::Failed();
      }

      // Set Element
      A._at(1, 1) = 1 / _at(1, 1);
   }
   else if (rows() == 2)
   {
      // Compute Determinant
      T d = det();

      // Check Determinant
      if (_equal(d, T()))
      {
         // Exception
         throw Exception::Failed();
      }

      // Set Elements
      A._at(1, 1) = _at(2, 2) / d;
      A._at(1, 2) = -_at(1, 2) / d;
      A._at(2, 1) = -_at(2, 1) / d;
      A._at(2, 2) = _at(1, 1) / d;
   }
   else
   {
      try
      {
         // Matrices for LUP Decomposition
         Matrix<T> L(rows());
         Matrix<T> U(rows());
         Matrix<T> P(rows());
         Matrix<T> L_(rows());
         Matrix<T> U_(rows());

         // Decompose Matrix in LUP Shape
         decompose_LUP(L, U, P);

         // Parse Rows
         for (size_t i = 1; i <= rows(); ++i)
         {
            // Parse Columns
            for (size_t j = i; 0 < j; j--)
            {
               // Sum
               T s = T();

               // Parse known Summands
               for (size_t k = (j + 1); k <= i; ++k)
               {
                  // Update Sum
                  s += L_._at(i, k) * L._at(k, j);
               }

               // Check Element
               if (_equal(L._at(j, j), T()))
               {
                  // Exception
                  throw Exception::Failed();
               }

               // Set Element
               L_._at(i, j) = (((i == j) ? 1 : T()) - s) / L._at(j, j);
            }

            // Parse Columns
            for (size_t j = i; j <= rows(); ++j)
            {
               // Sum
               T s = T();

               // Parse known Summands
               for (size_t k = i; k < j; ++k)
               {
                  // Update Sum
                  s += U_._at(i, k) * U._at(k, j);
               }

               // Check Element
               if (_equal(U._at(j, j), T()))
               {
                  // Exception
                  throw Exception::Failed();
               }

               // Set Element
               U_._at(i, j) = (((i == j) ? 1 : T()) - s) / U._at(j, j);
            }
         }

         // Multiply Inverses
         A = P.transpose() * U_ * L_;
      }
      catch (const Exception&)
      {
         // Compute Determinant
         T d = det();

         // Check Determinant
         if (_equal(d, T()))
         {
            // Exception
            throw Exception::Failed();
         }

         // Parse Rows
         for (size_t i = 1; i <= rows(); ++i)
         {
            // Parse Columns
            for (size_t j = 1; j <= rows(); ++j)
            {
               // Set Element
               A._at(j, i) = cofactor(i, j) / d;
            }
         }
      }
   }

   // Return Result
   return A;
}


// Find greatest Element
template <typename T> inline T& Matrix<T>::max(void)
{
   // Find and return greatest Element Reference
   return const_cast<T&>(const_cast<const Matrix<T>*>(this)->max());
}


// Find greatest Element
template <typename T> const T& Matrix<T>::max(void) const
{
   // Indices, Value
   size_t i = 1;
   size_t j = 1;
   T a = _at(1, 1);

   // Parse Rows
   for (size_t k = 1; k <= rows(); ++k)
   {
      // Parse Columns
      for (size_t l = 1; l <= rows(); ++l)
      {
         // Compare Elements
         if (_at(i, j) < _at(k, l))
         {
            // Update Indices
            i = k;
            j = l;
         }
      }
   }

   // Return greatest Element Reference
   return _at(i, j);
}


// Compute Mean Value
template <typename T> inline const T Matrix<T>::mean(void) const
{
   // Compute and return Mean Value
   return (sum() / rows() / cols());
}


// Find smallest Element
template <typename T> inline T& Matrix<T>::min(void)
{
   // Find and return smallest Element Reference
   return const_cast<T&>(const_cast<const Matrix<T>*>(this)->min());
}


// Find smallest Element
template <typename T> const T& Matrix<T>::min(void) const
{
   // Indices, Value
   size_t i = 1;
   size_t j = 1;
   T a = _at(1, 1);

   // Parse Rows
   for (size_t k = 1; k <= rows(); ++k)
   {
      // Parse Columns
      for (size_t l = 1; l <= rows(); ++l)
      {
         // Compare Elements
         if (_at(k, l) < _at(i, j))
         {
            // Update Indices
            i = k;
            j = l;
         }
      }
   }

   // Return smallest Element Reference
   return _at(i, j);
}


// Check if orthogonal
template <typename T> bool Matrix<T>::orthogonal(void) const
{
   // Check Dimension
   if (!square() || (rows() < 2))
   {
      // Exception
      throw Exception::Dimension();
   }

   // Parse Rows
   for (size_t i = 1; i <= rows(); ++i)
   {
      // Parse Columns
      for (size_t j = 1; j <= rows(); ++j)
      {
         // Sum
         T s = T();

         // Parse Elements
         for (size_t k = 1; k <= rows(); ++k)
         {
            // Update Sum
            s += _at(i, k) * _at(j, k);
         }

         // Check Indices and Sum
         if (((i == j) && (s != 1)) || ((i != j) && (s != T())))
         {
            // Return Result
            return false;
         }
      }
   }

   // Return Result
   return true;
}


// Check if regular
template <typename T> inline bool Matrix<T>::regular(void) const
{
   // Return Result
   return (det() != T());
}


// Resize
template <typename T> void Matrix<T>::resize(size_t rows, size_t cols, const T& a)
{
   // Check Parameters
   if ((rows < 1) || (cols < 1))
   {
      // Exception
      throw Exception::Parameter();
   }

   // Check Dimension
   if ((this->rows() != rows) || (this->cols() != cols))
   {
      // Matrix
      Matrix<T> A(rows, cols, a);

      // Parse Rows
      for (size_t i = 1; i <= std::min(this->rows(), rows); ++i)
      {
         // Parse Columns
         for (size_t j = 1; j <= std::min(this->cols(), cols); ++j)
         {
            // Set Element
            A._at(i, j) = _at(i, j);
         }
      }

      // Set Matrix
      *this = A;
   }
}


// Get Number of Rows
template <typename T> inline size_t Matrix<T>::rows(void) const
{
   // Return Number of Rows
   return _rows;
}


// Set Number of Rows
template <typename T> inline void Matrix<T>::rows(size_t rows, const T& a)
{
   // Resize
   resize(rows, cols(), a);
}


// Check if singular
template <typename T> inline bool Matrix<T>::singular(void) const
{
   // Return Result
   return !regular();
}


// Solve Linear Equation Set
template <typename T> const Vector<T> Matrix<T>::solve(const Vector<T>& v) const
{
   // Check Dimension and Parameter
   if (!square())
   {
      // Exception
      throw Exception::Dimension();
   }
   else if (v.dim() != rows())
   {
      // Exception
      throw Exception::Parameter();
   }

   // Solution Vector
   Vector<T> x(rows());

   // Check Dimension
   if (rows() == 1)
   {
      // Check Element
      if (_equal(_at(1, 1), T()))
      {
         // Exception
         throw Exception::Failed();
      }

      // Set Element
      x(1) = v(1) / _at(1, 1);
   }
   else if (rows() == 2)
   {
      // Compute Determinant
      T d = det();

      // Check Determinant
      if (_equal(d, T()))
      {
         // Exception
         throw Exception::Failed();
      }

      // Set Solution Vector
      x(1) = (_at(2, 2) * v(1) - _at(1, 2) * v(2)) / d;
      x(2) = (_at(1, 1) * v(2) - _at(2, 1) * v(1)) / d;
   }
   else
   {
      try
      {
         // Matrices for LUP Decomposition
         Matrix<T> L(rows());
         Matrix<T> U(rows());
         Matrix<T> P(rows());
         Vector<T> x_(rows());

         // Decompose Matrix in LUP Shape
         decompose_LUP(L, U, P);

         // Parse Rows
         for (size_t i = 1; i <= rows(); ++i)
         {
            // Sum
            T s = T();

            // Parse Columns
            for (size_t j = 1; j < i; ++j)
            {
               // Update Sum
               s += L._at(i, j) * x_(j);
            }

            // Check Element
            if (_equal(L._at(i, i), T()))
            {
               // Exception
               throw Exception::Failed();
            }

            // Set Element
            x_(i) = (v(i) - s) / L._at(i, i);
         }

         // Parse Rows
         for (size_t i = rows(); 0 < i; i--)
         {
            // Sum
            T s = T();

            // Parse Columns
            for (size_t j = 1; j <= (rows() - i); ++j)
            {
               // Update Sum
               s += U._at(i, rows() - j + 1) * x(rows() - j + 1);
            }

            // Check Element
            if (_equal(U._at(i, i), T()))
            {
               // Exception
               throw Exception::Failed();
            }

            // Set Element
            x(i) = (x_(i) - s) / U._at(i, i);
         }

         // Compute Solution Vector
         x = P.transpose() * x;
      }
      catch (const Exception&)
      {
         // Invert Matrix
         x = inverse() * v;
      }
   }

   // Return Result
   return x;
}


// Check if square
template <typename T> inline bool Matrix<T>::square(void) const
{
   // Return Result
   return (rows() == cols());
}


// Compute Sum
template <typename T> const T Matrix<T>::sum(void) const
{
   // Sum
   T s = T();

   // Parse Rows
   for (size_t i = 1; i <= rows(); ++i)
   {
      // Parse Columns
      for (size_t j = 1; j <= cols(); ++j)
      {
         // Update Sum
         s += _at(i, j);
      }
   }

   // Return Result
   return s;
}


// Check if symmetric
template <typename T> bool Matrix<T>::symmetric(void) const
{
   // Check Dimension
   if (!square())
   {
      // Exception
      throw Exception::Dimension();
   }

   // Parse Rows
   for (size_t i = 1; i <= rows(); ++i)
   {
      // Parse Columns
      for (size_t j = i; j <= cols(); ++j)
      {
         // Compare Elements
         if (!_equal(_at(i, j), _at(j, i)))
         {
            // Return Result
            return false;
         }
      }
   }

   // Return Result
   return true;
}


// Swap Columns
template <typename T> void Matrix<T>::swap_cols(size_t i, size_t j)
{
   // Check Columns
   if ((i < 1) || (cols() < i) || (j < 1) || (cols() < j))
   {
      // Exception
      throw Exception::Parameter();
   }
   else if (i != j)
   {
      // Parse Rows
      for (size_t k = 1; k <= rows(); ++k)
      {
         // Swap Elements
         std::swap(_at(k, i), _at(k, j));
      }
   }
}


// Swap Rows
template <typename T> void Matrix<T>::swap_rows(size_t i, size_t j)
{
   // Check Rows
   if ((i < 1) || (rows() < i) || (j < 1) || (rows() < j))
   {
      // Exception
      throw Exception::Parameter();
   }
   else if (i != j)
   {
      // Parse Columns
      for (size_t k = 1; k <= cols(); ++k)
      {
         // Swap Elements
         std::swap(_at(i, k), _at(j, k));
      }
   }
}


// Compute Trace
template <typename T> const T Matrix<T>::trace(void) const
{
   // Check Dimension
   if (!square())
   {
      // Exception
      throw Exception::Dimension();
   }

   // Sum
   T s = T();

   // Parse Rows
   for (size_t i = 1; i <= rows(); ++i)
   {
      // Update Sum
      s += _at(i, i);
   }

   // Return Result
   return s;
}


// Transpose
template <typename T> const Matrix<T> Matrix<T>::transpose(void) const
{
   // Matrix
   Matrix A(cols(), rows());

   // Parse Rows
   for (size_t i = 1; i <= rows(); ++i)
   {
      // Parse Columns
      for (size_t j = 1; j <= cols(); ++j)
      {
         // Set Element
         A._at(j, i) = _at(i, j);
      }
   }

   // Return Result
   return A;
}


// Check if triangular
template <typename T> bool Matrix<T>::triangular(void) const
{
   // Variables
   bool upper = true;
   bool lower = true;

   // Check Dimension
   if (!square() || (rows() < 2))
   {
      // Exception
      throw Exception::Dimension();
   }

   // Parse Rows
   for (size_t i = 1; i <= rows(); ++i)
   {
      // Parse Columns
      for (size_t j = 1; j <= rows(); ++j)
      {
         // Check Indices and Element
         if ((i != j) && !_equal(_at(i, j), T()))
         {
            // Check Indices
            if (i < j)
            {
               // Check upper Flag
               if (!upper)
               {
                  // Return Result
                  return false;
               }

               // Clear lower Flag
               lower = false;
            }
            else
            {
               // Check lower Flag
               if (!lower)
               {
                  // Return Result
                  return false;
               }

               // Clear Flag
               upper = false;
            }
         }
      }
   }

   // Return Result
   return true;
}


// Get Element (Indices are not checked)
template <typename T> inline T& Matrix<T>::_at(size_t row, size_t col)
{
   // Return Element Reference
   return const_cast<T&>(const_cast<const Matrix<T>&>(*this)._at(row, col));
}


// Get Element (Indices are not checked)
template <typename T> inline const T& Matrix<T>::_at(size_t row, size_t col) const
{
   // Return Element Reference
   return _a[cols() * (row - 1) + col - 1];
}


// Check if equal
template <typename T> inline bool Matrix<T>::_equal(const T& x, const T& y) const
{
   // Compute Difference
   T d = x - y;

   // Return Result
   return ((-_epsilon <= d) && (d <= _epsilon));
}


// Multiply with Scalar
template <typename T> inline const Matrix<T> operator *(const T& a, const Matrix<T>& A)
{
   // Multiply with Scalar and return Result
   return (A * a);
}


// Add Scalar
template <typename T> inline const Matrix<T> operator +(const T& a, const Matrix<T>& A)
{
   // Add Scalar and return Result
   return (A + a);
}


// Outer Product
template <typename T> const Matrix<T> operator |(const Vector<T>& u, const Vector<T>& v)
{
   // Matrix
   Matrix<T> A(u.dim(), v.dim());

   // Parse Rows
   for (size_t i = 1; i <= A.rows(); ++i)
   {
      // Parse Columns
      for (size_t j = 1; j <= A.cols(); ++j)
      {
         // Set Element
         A._at(i, j) = u(i) * v(j);
      }
   }

   // Return Matrix
   return A;
}
