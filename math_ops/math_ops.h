#pragma once
#include "../matrix/matrix.h"

double vector_norm(const Vector<double>& y);

Vector<double> vector_sub(const Vector<double>& a, const Vector<double>& b);

double rel_error(const Vector<double>& x_exact, const Vector<double>& x_approx);

double calc_res(const IMatrix<double>& A, const Vector<double>& x_approx, const Vector<double>& b);