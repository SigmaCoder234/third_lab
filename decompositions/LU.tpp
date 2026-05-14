#include "../matrix/matrix.h"
#include <stdexcept>
#include <cmath>

// LU разложение
template<class T>
void lu_decomposition(const IMatrix<T> &A, SquareMatrix<T> &L, SquareMatrix<T> &U) {
    if (A.get_rows() != A.get_cols()) throw std::invalid_argument("Matrix must be square");
    int dim = A.get_rows();

    L = SquareMatrix<T>(dim);
    U = SquareMatrix<T>(dim);

    for (int i = 0; i < dim; i++) {
        L(i, i) = 1.0;
    }

    for (int i = 0; i < dim; i++) {

        // Вычисляем строку матрицы U
        for (int j = i; j < dim; j++) {
            double sum = 0;

            for (int k = 0; k < i; k++) {
                sum += L(i, k) * U(k, j);
            }

            U(i, j) = A(i, j) - sum;
        }

        // Проверка диагонального элемента
        if (std::abs(U(i, i)) < 1e-18) {
            throw std::runtime_error("Zero on diagonal");
        }

        // Вычисляем столбец матрицы L
        for (int j = i + 1; j < dim; j++) {
            double sum = 0;

            for (int k = 0; k < i; k++) {
                sum += L(j, k) * U(k, i);
            }

            L(j, i) = (A(j, i) - sum) / U(i, i);
        }
    }
}

// прямое разложение Ly = b
template<class T>
Vector<T> forward_sub(const IMatrix<T> &L, const Vector<T> &b) {
    if (L.get_rows() != L.get_cols() || L.get_rows() != b.size()) throw std::invalid_argument("Dimensions mismatch");
    int dim = L.get_rows();
    Vector<T> y(dim);

    for (int i = 0; i < dim; i++) {
        double sum = 0;

        for (int k = 0; k < i; k++) {
            sum += L(i, k) * y[k];
        }

        y[i] = (b[i] - sum) / L(i, i);
    }

    return y;
}

// обратное разложение Ux = y
template<class T>
Vector<T> backward_sub(const IMatrix<T> &U, const Vector<T> &y) {
    if (U.get_rows() != U.get_cols() || U.get_rows() != y.size()) throw std::invalid_argument("Dimensions mismatch");
    int dim = U.get_rows();
    Vector<T> x(dim);

    for (int i = dim - 1; i >= 0; i--) {
        double sum = 0;

        for (int k = i + 1; k < dim; k++) {
            sum += U(i, k) * x[k];
        }

        if (std::abs(U(i, i)) < 1e-18) {
            throw std::runtime_error("Zero on diagonal in U matrix");
        }

        x[i] = (y[i] - sum) / U(i, i);
    }

    return x;
}

// Решение LU разложения LUx = b
template<class T>
Vector<T> solve_lu(const IMatrix<T>& L, const IMatrix<T>& U, const Vector<T>& b) {
    Vector<T> y = forward_sub(L, b);
    return backward_sub(U, y);
}