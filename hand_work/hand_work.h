#pragma once
#include "../matrix/matrix.h"

int safe_input();
bool safe_bool_input();
double safe_double_input();

template<class T>
void matrix_print(Matrix<T> A);

template<class T>
void vector_print(Vector<T> b);

template<class T>
Matrix<T> fill_matrix(int dim);

template<class T>
Vector<T> fill_vector(int len);

#include "hand_work.tpp"