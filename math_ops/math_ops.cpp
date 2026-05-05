#include <cmath>
#include <stddef.h>
#include "math_ops.h"
#include "../matrix/matrix.h"

// норма вектора
double vector_norm(const Vector<double> &y) {
    double norm = 0;

    IEnumerator<double>* it = y.GetEnumerator();
    while (it->MoveNext()) {
        norm += it->Current() * it->Current();
    }
    delete it;

    return std::sqrt(norm);
}

// вычитание векторов
Vector<double> vector_sub(const Vector<double> &a, const Vector<double> &b) {
    size_t len = a.size();
    Vector<double> res(len);

    IEnumerator<double>* it_a = a.GetEnumerator();
    IEnumerator<double>* it_b = b.GetEnumerator();
    size_t i = 0;

    while (it_a->MoveNext() && it_b->MoveNext()) {
        res[i++] = it_a->Current() - it_b->Current();
    }
    delete it_a;
    delete it_b;

    return res;
}

// относительная погрешность
double rel_error(const Vector<double> &x_exact, const Vector<double> &x_approx) {
    double res = vector_norm(vector_sub(x_exact, x_approx)) / vector_norm(x_exact);

    return res;
}

// норма невязки
double calc_res(const Matrix<double> &A, const Vector<double> &x_approx, const Vector<double> &b) {
    return vector_norm(vector_sub(matrix_by_vector(A, x_approx), b));
}