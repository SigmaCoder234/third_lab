#pragma once
#include "../matrix/matrix.h"

template<class T>
Vector<T> gauss_with_pivot(Matrix<T> A, Vector<T> b);

template<class T>
Vector<T> gauss_without_pivot(Matrix<T> A, Vector<T> b);