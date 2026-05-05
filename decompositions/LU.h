#pragma once
#include "../matrix/matrix.h"

void lu_decomposition(const Matrix<double>& A, Matrix<double>& L, Matrix<double>& U);

Vector<double> forward_sub(const Matrix<double>& L, const Vector<double>& b);
Vector<double> backward_sub(const Matrix<double>& U, const Vector<double>& y);

Vector<double> solve_lu(const Matrix<double>& L,const Matrix<double>& U, const Vector<double>& b);