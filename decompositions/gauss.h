#pragma once
#include "../matrix/matrix.h"

template<class T>
Vector<T> gauss_with_pivot(const IMatrix<T>& A_in, Vector<T> b);

template<class T>
Vector<T> gauss_without_pivot(const IMatrix<T>& A_in, Vector<T> b);

#include "gauss.tpp"