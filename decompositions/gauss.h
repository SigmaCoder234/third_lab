#pragma once
#include "../matrix/matrix.h"

Vector<double> gauss_with_pivot(Matrix<double> A, Vector<double> b);
Vector<double> gauss_without_pivot(Matrix<double> A, Vector<double> b);