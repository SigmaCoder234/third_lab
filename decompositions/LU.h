#pragma once
#include "../matrix/matrix.h"

template<class T>
void lu_decomposition(const IMatrix<T>& A, SquareMatrix<T>& L, SquareMatrix<T>& U);

template<class T>
Vector<T> forward_sub(const IMatrix<T>& L, const Vector<T>& b);

template<class T>
Vector<T> backward_sub(const IMatrix<T>& U, const Vector<T>& y);

template<class T>
Vector<T> solve_lu(const IMatrix<T>& L, const IMatrix<T>& U, const Vector<T>& b);

#include "LU.tpp"