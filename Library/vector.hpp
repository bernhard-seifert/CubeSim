

// VECTOR 1.7.0


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
#include <vector>


// Preprocessor Directives
#pragma once


// Class Vector
template <typename T> class Vector
{
public:

   // Class Exception
   class Exception;

   // Constructor
   Vector(size_t dim, const T& a = T());
   Vector(const std::vector<T>& v);
   Vector(const std::initializer_list<T>& list);

   // Convert to std::vector
   operator const std::vector<T>&(void) const;

   // Sign
   const Vector<T>& operator +(void) const;
   const Vector<T> operator -(void) const;

   // Compare
   bool operator ==(const Vector<T>& v) const;
   bool operator !=(const Vector<T>& v) const;

   // Assign
   Vector<T>& operator =(const std::vector<T>& v);
   Vector<T>& operator =(const std::initializer_list<T>& list);

   // Multiply
   const Vector<T> operator *(const T& a) const;
   const T operator *(const Vector<T>& v) const;
   Vector<T>& operator *=(const T& a);

   // Divide by Scalar
   const Vector<T> operator /(const T& a) const;
   Vector<T>& operator /=(const T& a);

   // Add
   const Vector<T> operator +(const T& a) const;
   const Vector<T> operator +(const Vector<T>& v) const;
   Vector<T>& operator +=(const T& a);
   Vector<T>& operator +=(const Vector<T>& v);

   // Subtract
   const Vector<T> operator -(const T& a) const;
   const Vector<T> operator -(const Vector<T>& v) const;
   Vector<T>& operator -=(const T& a);
   Vector<T>& operator -=(const Vector<T>& v);

   // Compute Cross Product
   const Vector<T> operator ^(const Vector<T>& v) const;
   Vector<T>& operator ^=(const Vector<T>& v);

   // Compute Angle
   const T operator %(const Vector<T>& v) const;

   // Get Element
   T& operator ()(size_t i);
   const T& operator ()(size_t i) const;
   T& at(size_t i);
   const T& at(size_t i) const;

   // Get Dimension
   size_t dim(void) const;

   // Epsilon
   const T epsilon(void) const;
   void epsilon(const T& epsilon);

   // Find greatest Element
   T& max(void);
   const T& max(void) const;

   // Compute Mean Value
   const T mean(void) const;

   // Find smallest Element
   T& min(void);
   const T& min(void) const;

   // Compute Norm
   const T norm(void) const;

   // Resize
   void resize(size_t dim, const T& a = T());

   // Compute Sum
   const T sum(void) const;

   // Swap Elements
   void swap(size_t i, size_t j);

   // Compute Unit Vector
   const Vector<T> unit(void) const;

protected:

   // Get Element (Index is not checked)
   T& _at(size_t i);
   const T& _at(size_t i) const;

private:

   // Check if equal
   bool _equal(const T& x, const T& y) const;

   // Variables
   T _epsilon;
   std::vector<T> _a;
};


// Class Exception
template <typename T> class Vector<T>::Exception
{
public:

   // Class Dimension
   class Dimension;

   // Class Parameter
   class Parameter;

private:

   // Virtual Function for RTTI
   virtual void _func() {}
};


// Class Dimension
template <typename T> class Vector<T>::Exception::Dimension : public Vector<T>::Exception
{
};


// Class Parameter
template <typename T> class Vector<T>::Exception::Parameter : public Vector<T>::Exception
{
};


// Multiply with Scalar
template <typename T> const Vector<T> operator *(const T& a, const Vector<T>& v);

// Add Scalar
template <typename T> const Vector<T> operator +(const T& a, const Vector<T>& v);


// Constructor
template <typename T> Vector<T>::Vector(size_t dim, const T& a) : _epsilon()
{
   // Check Dimension
   if (dim < 1)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Initialize
   _a.resize(dim, a);
}


// Constructor
template <typename T> Vector<T>::Vector(const std::vector<T>& v) : _epsilon()
{
   // Initialize
   *this = v;
}


// Constructor
template <typename T> Vector<T>::Vector(const std::initializer_list<T>& list) : _epsilon()
{
   // Initialize
   *this = list;
}


// Convert to std::vector
template <typename T> inline Vector<T>::operator const std::vector<T>&(void) const
{
   // Return std::vector
   return _a;
}


// Plus Sign
template <typename T> inline const Vector<T>& Vector<T>::operator +(void) const
{
   // Return Reference
   return *this;
}


// Minus Sign
template <typename T> const Vector<T> Vector<T>::operator -(void) const
{
   // Vector
   Vector<T> v(*this);

   // Parse Elements
   for (size_t i = 1; i <= dim(); ++i)
   {
      // Negate Element
      v._at(i) = -_at(i);
   }

   // Return Vector
   return v;
}


// Compare
template <typename T> inline bool Vector<T>::operator ==(const Vector<T>& v) const
{
   // Check Dimension
   if (dim() != v.dim())
   {
      // Return Result
      return false;
   }

   // Parse Elements
   for (size_t i = 1; i <= dim(); ++i)
   {
      // Compare Elements
      if (!_equal(_at(i), v._at(i)))
      {
         // Return Result
         return false;
      }
   }

   // Return Result
   return true;
}


// Compare
template <typename T> inline bool Vector<T>::operator !=(const Vector<T>& v) const
{
   // Return Result
   return !(*this == v);
}


// Assign std::vector
template <typename T> inline Vector<T>& Vector<T>::operator =(const std::vector<T>& v)
{
   // Check Dimension
   if (v.empty())
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Vector
   _a = v;

   // Return Reference
   return *this;
}


// Assign List
template <typename T> inline Vector<T>& Vector<T>::operator =(const std::initializer_list<T>& list)
{
   // Check Dimension
   if (!list.size())
   {
      // Exception
      throw Exception::Parameter();
   }

   // Set Vector
   _a = list;

   // Return Reference
   return *this;
}


// Multiply with Scalar
template <typename T> inline const Vector<T> Vector<T>::operator *(const T& a) const
{
   // Multiply, assign and return Vector
   return (Vector<T>(*this) *= a);
}


// Multiply (Dot Product)
template <typename T> const T Vector<T>::operator *(const Vector<T>& v) const
{
   // Check Dimension
   if (dim() != v.dim())
   {
      // Exception
      throw Exception::Dimension();
   }

   // Value
   T a = T();

   // Parse Elements
   for (size_t i = 1; i <= dim(); ++i)
   {
      // Update Value
      a += _at(i) * v._at(i);
   }

   // Return Value
   return a;
}


// Multiply with Scalar and assign
template <typename T> Vector<T>& Vector<T>::operator *=(const T& a)
{
   // Parse Elements
   for (size_t i = 1; i <= dim(); ++i)
   {
      // Multiply and assign Element
      _at(i) *= a;
   }

   // Return Reference
   return *this;
}


// Divide by Scalar
template <typename T> inline const Vector<T> Vector<T>::operator /(const T& a) const
{
   // Divide, assign and return Vector
   return (Vector<T>(*this) /= a);
}


// Divide by Scalar and assign
template <typename T> Vector<T>& Vector<T>::operator /=(const T& a)
{
   // Check Parameter
   if (a == T())
   {
      // Exception
      throw Exception::Parameter();
   }

   // Parse Elements
   for (size_t i = 1; i <= dim(); ++i)
   {
      // Divide and assign Element
      _at(i) /= a;
   }

   // Return Reference
   return *this;
}


// Add Scalar
template <typename T> inline const Vector<T> Vector<T>::operator +(const T& a) const
{
   // Add, assign and return Vector
   return (Vector<T>(*this) += a);
}


// Add Vector
template <typename T> inline const Vector<T> Vector<T>::operator +(const Vector<T>& v) const
{
   // Add, assign and return Vector
   return (Vector<T>(*this) += v);
}


// Add Scalar and assign
template <typename T> Vector<T>& Vector<T>::operator +=(const T& a)
{
   // Parse Elements
   for (size_t i = 1; i <= dim(); ++i)
   {
      // Add and assign Element
      _at(i) += a;
   }

   // Return Reference
   return *this;
}


// Add Vector and assign
template <typename T> Vector<T>& Vector<T>::operator +=(const Vector<T>& v)
{
   // Check Dimension
   if (dim() != v.dim())
   {
      // Exception
      throw Exception::Dimension();
   }

   // Parse Elements
   for (size_t i = 1; i <= dim(); ++i)
   {
      // Add and assign Element
      _at(i) += v._at(i);
   }

   // Return Reference
   return *this;
}


// Subtract Scalar
template <typename T> inline const Vector<T> Vector<T>::operator -(const T& a) const
{
   // Subtract, assign and return Vector
   return (Vector<T>(*this) -= a);
}


// Subtract Vector
template <typename T> inline const Vector<T> Vector<T>::operator -(const Vector<T>& v) const
{
   // Subtract, assign and return Vector
   return (Vector<T>(*this) -= v);
}


// Subtract Scalar and assign
template <typename T> Vector<T>& Vector<T>::operator -=(const T& a)
{
   // Parse Elements
   for (size_t i = 1; i <= dim(); ++i)
   {
      // Subtract and assign Element
      _at(i) -= a;
   }

   // Return Reference
   return *this;
}


// Subtract Vector and assign
template <typename T> Vector<T>& Vector<T>::operator -=(const Vector<T>& v)
{
   // Check Dimension
   if (dim() != v.dim())
   {
      // Exception
      throw Exception::Dimension();
   }

   // Parse Elements
   for (size_t i = 1; i <= dim(); ++i)
   {
      // Subtract and assign Element
      _at(i) -= v._at(i);
   }

   // Return Reference
   return *this;
}


// Compute Cross Product
template <typename T> const Vector<T> Vector<T>::operator ^(const Vector<T>& v) const
{
   // Check Dimensions
   if ((dim() != 3) || (v.dim() != 3))
   {
      // Exception
      throw Exception::Dimension();
   }

   // Vector
   Vector<T> u(3);

   // Compute Cross Product
   u(1) = (*this)(2) * v(3) - (*this)(3) * v(2);
   u(2) = (*this)(3) * v(1) - (*this)(1) * v(3);
   u(3) = (*this)(1) * v(2) - (*this)(2) * v(1);

   // Return Vector
   return u;
}


// Compute Cross Product and assign
template <typename T> inline Vector<T>& Vector<T>::operator ^=(const Vector<T>& v)
{
   // Compute Cross Product, assign and return Reference
   return (*this = *this ^ v);
}


// Compute Angle
template <typename T> const T Vector<T>::operator %(const Vector<T>& v) const
{
   // Compute Norms
   T norm1 = norm();
   T norm2 = v.norm();

   // Check Norms
   if (norm1 == T())
   {
      // Exception
      throw Exception::Failed();
   }
   else if (norm2 == T())
   {
      // Exception
      throw Exception::Parameter();
   }

   // Compute and return Angle
   return acos(*this * v / norm1 / norm2);
}


// Get Element (Index is not checked)
template <typename T> inline T& Vector<T>::operator ()(size_t i)
{
   // Return Element Reference
   return _at(i);
}


// Get Element (Index is not checked)
template <typename T> inline const T& Vector<T>::operator ()(size_t i) const
{
   // Return Element Reference
   return _at(i);
}


// Get Element
template <typename T> inline T& Vector<T>::at(size_t i)
{
   // Return Element Reference
   return const_cast<T&>(const_cast<const Vector<T>&>(*this).at(i));
}


// Get Element
template <typename T> const T& Vector<T>::at(size_t i) const
{
   // Check Index
   if ((i < 1) || (dim() < i))
   {
      // Exception
      throw Exception::Parameter();
   }

   // Return Element Reference
   return _at(i);
}


// Get Dimension
template <typename T> inline size_t Vector<T>::dim(void) const
{
   // Return Dimension
   return _a.size();
}


// Get Epsilon
template <typename T> inline const T Vector<T>::epsilon(void) const
{
   // Return Epsilon
   return _epsilon;
}


// Set Epsilon
template <typename T> inline void Vector<T>::epsilon(const T& epsilon)
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


// Find greatest Element
template <typename T> inline T& Vector<T>::max(void)
{
   // Find and return greatest Element
   return const_cast<T&>(const_cast<const Vector<T>*>(this)->max());
}


// Find greatest Element
template <typename T> const T& Vector<T>::max(void) const
{
   // Index, Value
   size_t i = 1;
   T a = _at(1);

   // Parse Elements
   for (size_t j = 2; j <= dim(); ++j)
   {
      // Compare Elements
      if (_at(i) < _at(j))
      {
         // Update Index
         i = j;
      }
   }

   // Return greatest Element
   return _at(i);
}


// Compute Mean Value
template <typename T> inline const T Vector<T>::mean(void) const
{
   // Compute and return Mean Value
   return (sum() / dim());
}


// Find smallest Element
template <typename T> inline T& Vector<T>::min(void)
{
   // Find and return smallest Element
   return const_cast<T&>(const_cast<const Vector<T>*>(this)->min());
}


// Find smallest Element
template <typename T> const T& Vector<T>::min(void) const
{
   // Index, Value
   size_t i = 1;
   T a = _at(1);

   // Parse Elements
   for (size_t j = 2; j <= dim(); ++j)
   {
      // Compare Elements
      if (_at(j) < _at(i))
      {
         // Update Index
         i = j;
      }
   }

   // Return smallest Element
   return _at(i);
}


// Compute Norm
template <typename T> const T Vector<T>::norm(void) const
{
   // Value
   T a = T();

   // Parse Elements
   for (size_t i = 1; i <= dim(); ++i)
   {
      // Update Value
      a += _at(i) * _at(i);
   }

   // Compute Square-Root and return Value
   return sqrt(a);
}


// Resize
template <typename T> void Vector<T>::resize(size_t dim, const T& a)
{
   // Check Dimension
   if (dim < 1)
   {
      // Exception
      throw Exception::Parameter();
   }

   // Resize
   _a.resize(dim, a);
}


// Compute Sum
template <typename T> const T Vector<T>::sum(void) const
{
   // Sum
   T s = T();

   // Parse Elements
   for (size_t i = 1; i <= dim(); ++i)
   {
      // Update Sum
      s += _at(i);
   }

   // Return Result
   return s;
}


// Swap Elements
template <typename T> void Vector<T>::swap(size_t i, size_t j)
{
   // Check Indices
   if (i != j)
   {
      // Swap Elements
      std::swap(at(i), at(j));
   }
}


// Compute Unit Vector
template <typename T> const Vector<T> Vector<T>::unit(void) const
{
   // Compute Norm
   T norm_ = norm();

   // Check Norm
   if (norm_ == T())
   {
      // Exception
      throw Exception::Failed();
   }

   // Compute and return Unit Vector
   return (*this / norm_);
}


// Get Element (Index is not checked)
template <typename T> inline T& Vector<T>::_at(size_t i)
{
   // Return Element Reference
   return const_cast<T&>(const_cast<const Vector<T>&>(*this)._at(i));
}


// Get Element (Index is not checked)
template <typename T> inline const T& Vector<T>::_at(size_t i) const
{
   // Return Element Reference
   return _a[i - 1];
}


// Check if equal
template <typename T> inline bool Vector<T>::_equal(const T& x, const T& y) const
{
   // Compute Difference
   T d = x - y;

   // Return Result
   return ((-_epsilon <= d) && (d <= _epsilon));
}


// Multiply
template <typename T> inline const Vector<T> operator *(const T& a, const Vector<T>& v)
{
   // Multiply and return Vector
   return (v * a);
}


// Add
template <typename T> inline const Vector<T> operator +(const T& a, const Vector<T>& v)
{
   // Add and return Vector
   return (v + a);
}
