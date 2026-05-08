#pragma once
#include "../matrix/matrix.h"

template<class T>
void lu_decomposition(const Matrix<T>& A, Matrix<T>& L, Matrix<T>& U);

template<class T>
Vector<T> forward_sub(const Matrix<T>& L, const Vector<T>& b);

template<class T>
Vector<T> backward_sub(const Matrix<T>& U, const Vector<T>& y);

template<class T>
Vector<T> solve_lu(const Matrix<T>& L,const Matrix<T>& U, const Vector<T>& b);