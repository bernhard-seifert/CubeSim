

// CUBESIM - MATRIX


// Includes
#include <matrix.hpp>
#include "vector.hpp"


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class Matrix3D
   class Matrix3D;

   // Multiply
   const Matrix3D operator *(double a, const Matrix3D& A);

   // Add
   const Matrix3D operator +(double a, const Matrix3D& A);
}


// Class Matrix3D
class CubeSim::Matrix3D : private Matrix<double>
{
public:

   // Identity Matrix
   static const Matrix3D IDENTITY;

   // Constructor
   Matrix3D(void);
   Matrix3D(const Matrix<double>& A);
   Matrix3D(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3);

   // Sign
   const Matrix3D& operator +(void) const;
   const Matrix3D operator -(void) const;

   // Compare
   bool operator ==(const Matrix3D& A) const;
   bool operator !=(const Matrix3D& A) const;

   // Multiply
   const Matrix3D operator *(double a) const;
   const Vector3D operator *(const Vector3D& v) const;
   const Matrix3D operator *(const Matrix3D& A) const;
   Matrix3D& operator *=(double a);
   Matrix3D& operator *=(const Matrix3D& A);

   // Divide
   const Matrix3D operator /(double a) const;
   Matrix3D& operator /=(double a);

   // Add
   const Matrix3D operator +(double a) const;
   const Matrix3D operator +(const Matrix3D& A) const;
   Matrix3D& operator +=(double a);
   Matrix3D& operator +=(const Matrix3D& A);

   // Subtract
   const Matrix3D operator -(double a) const;
   const Matrix3D operator -(const Matrix3D& A) const;
   Matrix3D& operator -=(double a);
   Matrix3D& operator -=(const Matrix3D& A);

   // Check if asymmetric
   using Matrix<double>::asymmetric;

   // Get Element
   double& operator ()(size_t row, size_t col);
   double operator ()(size_t row, size_t col) const;
   double& at(size_t row, size_t col);
   double at(size_t row, size_t col) const;

   // Compute Cofactor
   double cofactor(size_t row, size_t col) const;

   // Decompose in LU Shape
   void decompose_LU(Matrix3D& L, Matrix3D& U) const;

   // Decompose in LUP Shape
   double decompose_LUP(Matrix3D& L, Matrix3D& U, Matrix3D& P) const;

   // Compute Determinant
   using Matrix<double>::det;

   // Check if diagonal
   using Matrix<double>::diagonal;

   // Compute Inverse
   const Matrix3D inverse(void) const;

   // Check if orthogonal
   using Matrix<double>::orthogonal;

   // Check if regular
   using Matrix<double>::regular;

   // Check if singular
   using Matrix<double>::singular;

   // Solve Linear Equation Set
   const Vector3D solve(const Vector3D& v) const;

   // Check if symmetric
   using Matrix<double>::symmetric;

   // Swap Columns
   void swap_cols(size_t i, size_t j);

   // Swap Rows
   void swap_rows(size_t i, size_t j);

   // Compute Trace
   using Matrix<double>::trace;

   // Transpose
   const Matrix3D transpose(void) const;

   // Check if triangular
   using Matrix<double>::triangular;
};


// Constructor
inline CubeSim::Matrix3D::Matrix3D(void) : Matrix(3)
{
   // Initialize
   epsilon(Constant::EPSILON);
}


// Constructor
inline CubeSim::Matrix3D::Matrix3D(const Matrix<double>& A) : Matrix(A)
{
   // Check Dimension
   if ((A.rows() != 3) || (A.cols() != 3))
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Initialize
   epsilon(Constant::EPSILON);
}


// Plus Sign
inline const CubeSim::Matrix3D& CubeSim::Matrix3D::operator +(void) const
{
   // Return Reference
   return *this;
}


// Minus Sign
inline const CubeSim::Matrix3D CubeSim::Matrix3D::operator -(void) const
{
   // Return Result
   return Matrix<double>::operator -();
}


// Compare
inline bool CubeSim::Matrix3D::operator ==(const Matrix3D& A) const
{
   // Return Result
   return Matrix<double>::operator ==(A);
}


// Compare
inline bool CubeSim::Matrix3D::operator !=(const Matrix3D& A) const
{
   // Return Result
   return Matrix<double>::operator !=(A);
}


// Multiply
inline const CubeSim::Matrix3D CubeSim::Matrix3D::operator *(double a) const
{
   // Return Result
   return Matrix<double>::operator *(a);
}


// Multiply
inline const CubeSim::Vector3D CubeSim::Matrix3D::operator *(const Vector3D& v) const
{
   // Return Result
   return Matrix<double>::operator *(v);
}


// Multiply
inline const CubeSim::Matrix3D CubeSim::Matrix3D::operator *(const Matrix3D& A) const
{
   // Return Result
   return Matrix<double>::operator *(A);
}


// Multiplication Assignment
inline CubeSim::Matrix3D& CubeSim::Matrix3D::operator *=(double a)
{
   // Multiplication Assignment
   Matrix<double>::operator *=(a);

   // Return Reference
   return *this;
}


// Multiplication Assignment
inline CubeSim::Matrix3D& CubeSim::Matrix3D::operator *=(const Matrix3D& A)
{
   // Multiplication Assignment
   Matrix<double>::operator *=(A);

   // Return Reference
   return *this;
}


// Divide
inline const CubeSim::Matrix3D CubeSim::Matrix3D::operator /(double a) const
{
   // Check Parameter
   if (a == 0.0)
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Return Result
   return Matrix<double>::operator /(a);
}


// Division Assignment
inline CubeSim::Matrix3D& CubeSim::Matrix3D::operator /=(double a)
{
   // Check Parameter
   if (a == 0.0)
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Division Assignment
   Matrix<double>::operator /=(a);

   // Return Reference
   return *this;
}


// Add
inline const CubeSim::Matrix3D CubeSim::Matrix3D::operator +(double a) const
{
   // Return Result
   return Matrix<double>::operator +(a);
}


// Add
inline const CubeSim::Matrix3D CubeSim::Matrix3D::operator +(const Matrix3D& A) const
{
   // Return Result
   return Matrix<double>::operator +(A);
}


// Addition Assignment
inline CubeSim::Matrix3D& CubeSim::Matrix3D::operator +=(double a)
{
   // Add and assign
   Matrix<double>::operator +=(a);

   // Return Reference
   return *this;
}


// Addition Assignment
inline CubeSim::Matrix3D& CubeSim::Matrix3D::operator +=(const Matrix3D& A)
{
   // Add and assign
   Matrix<double>::operator +=(A);

   // Return Reference
   return *this;
}


// Subtract
inline const CubeSim::Matrix3D CubeSim::Matrix3D::operator -(double a) const
{
   // Return Result
   return Matrix<double>::operator -(a);
}


// Subtract
inline const CubeSim::Matrix3D CubeSim::Matrix3D::operator -(const Matrix3D& A) const
{
   // Return Result
   return Matrix<double>::operator -(A);
}


// Subtraction Assignment
inline CubeSim::Matrix3D& CubeSim::Matrix3D::operator -=(double a)
{
   // Subtract and assign
   Matrix<double>::operator -=(a);

   // Return Reference
   return *this;
}


// Subtraction Assignment
inline CubeSim::Matrix3D& CubeSim::Matrix3D::operator -=(const Matrix3D& A)
{
   // Subtract and assign
   Matrix<double>::operator -=(A);

   // Return Reference
   return *this;
}


// Get Element
inline double& CubeSim::Matrix3D::operator ()(size_t row, size_t col)
{
   // Return Element
   return at(row, col);
}


// Get Element
inline double CubeSim::Matrix3D::operator ()(size_t row, size_t col) const
{
   // Return Element
   return at(row, col);
}


// Get Element
inline double& CubeSim::Matrix3D::at(size_t row, size_t col)
{
   // Check Row and Column
   if (!row || (3 < row) || !col || (3 < col))
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Return Element
   return Matrix<double>::_at(row, col);
}


// Get Element
inline double CubeSim::Matrix3D::at(size_t row, size_t col) const
{
   // Check Row and Column
   if (!row || (3 < row) || !col || (3 < col))
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Return Element
   return Matrix<double>::_at(row, col);
}


// Compute Cofactor
inline double CubeSim::Matrix3D::cofactor(size_t row, size_t col) const
{
   // Check Row and Column
   if (!row || (3 < row) || !col || (3 < col))
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Return Result
   return Matrix<double>::cofactor(row, col);
}


// Decompose in LU Shape
inline void CubeSim::Matrix3D::decompose_LU(Matrix3D& L, Matrix3D& U) const
{
   try
   {
      // Decompose in LU Shape
      Matrix<double>::decompose_LU(L, U);
   }
   catch (const Exception&)
   {
      // Exception
      throw CubeSim::Exception::Failed();
   }
}


// Decompose in LUP Shape
inline double CubeSim::Matrix3D::decompose_LUP(Matrix3D& L, Matrix3D& U, Matrix3D& P) const
{
   try
   {
      // Decompose in LUP Shape
      Matrix<double>::decompose_LUP(L, U, P);
   }
   catch (const Exception&)
   {
      // Exception
      throw CubeSim::Exception::Failed();
   }
}


// Compute Inverse
inline const CubeSim::Matrix3D CubeSim::Matrix3D::inverse(void) const
{
   // Matrix
   Matrix3D I;

   try
   {
      // Compute Inverse
      I = Matrix<double>::inverse();
   }
   catch (const Exception&)
   {
      // Exception
      throw CubeSim::Exception::Failed();
   }

   // Return Result
   return I;
}


// Solve Linear Equation Set
inline const CubeSim::Vector3D CubeSim::Matrix3D::solve(const Vector3D& v) const
{
   try
   {
      // Solve Linear Equation Set
      return Matrix<double>::solve(v);
   }
   catch (const Exception&)
   {
      // Exception
      throw CubeSim::Exception::Failed();
   }
}


// Swap Columns
inline void CubeSim::Matrix3D::swap_cols(size_t i, size_t j)
{
   // Check Indices
   if (!i || (3 < i) || !j || (3 < j))
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Swap Columns
   Matrix<double>::swap_cols(i, j);
}


// Swap Rows
inline void CubeSim::Matrix3D::swap_rows(size_t i, size_t j)
{
   // Check Indices
   if (!i || (3 < i) || !j || (3 < j))
   {
      // Exception
      throw CubeSim::Exception::Parameter();
   }

   // Swap Rows
   Matrix<double>::swap_rows(i, j);
}


// Transpose
inline const CubeSim::Matrix3D CubeSim::Matrix3D::transpose(void) const
{
   // Return Result
   return Matrix<double>::transpose();
}


// Multiply
inline const CubeSim::Matrix3D CubeSim::operator *(double a, const Matrix3D& A)
{
   // Return Result
   return (A * a);
}


// Add
inline const CubeSim::Matrix3D CubeSim::operator +(double a, const Matrix3D& A)
{
   // Return Result
   return (A + a);
}
