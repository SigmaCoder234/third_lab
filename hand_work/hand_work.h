#pragma once
#include "../matrix/matrix.h"

#include <string>

int safe_input();
bool safe_bool_input();
double safe_double_input();

template<class T>
void matrix_print(const IMatrix<T>& A);

template<class T>
void vector_print(Vector<T> b);

template<class T>
SquareMatrix<T> fill_matrix(int dim, const std::string& name = "A");

template<class T>
void fill_matrix_values(IMatrix<T>& m, const std::string& name = "A");

template<class T>
Vector<T> fill_vector(int len, const std::string& name = "b");

#include "hand_work.tpp"