

// CUBESIM - MATRIX


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
#include "matrix.hpp"


// Constructor
CubeSim::Matrix3D::Matrix3D(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3) : Matrix(3)
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

   // Initialize
   epsilon(std::numeric_limits<float>::epsilon());
}


// Identity Matrix
const CubeSim::Matrix3D CubeSim::Matrix3D::IDENTITY = Matrix<double>::identity(3);
