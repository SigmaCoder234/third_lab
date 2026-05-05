#pragma once
#include "../matrix/matrix.h"

void matrix_print(Matrix<double> A);
void vector_print(Vector<double> b);

int safe_input();
bool safe_bool_input();

Matrix<double> fill_matrix(int dim);
Vector<double> fill_vector(int len);