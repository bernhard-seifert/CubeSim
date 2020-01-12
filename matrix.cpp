

// CUBESIM - MATRIX


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
