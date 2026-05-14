#include "../matrix/matrix.h"
#include <cmath>
#include <stdexcept>

template<class T>
Vector<T> gauss_with_pivot(const IMatrix<T>& A_in, Vector<T> b) {
    if (A_in.get_rows() != A_in.get_cols()) throw std::invalid_argument("Matrix must be square");
    SquareMatrix<T> A(A_in);
    int len = A.get_rows();

    // прямой ход
    for (int i = 0; i < len; i++) {
        int max_index = i;
        double max_val = std::abs(A(i, i));

        for (int j = i + 1; j < len; j++) {
            if (std::abs(A(j, i)) > max_val) {
                max_val = std::abs(A(j, i));
                max_index = j;
            }
        }

        A.swap_rows(i, max_index);
        std::swap(b[i], b[max_index]);

        if (std::abs(A(i, i)) < 1e-18) {
            throw std::runtime_error("Zero pivot encountered: Matrix is singular");
        }

        for (int k = i + 1; k < len; k++) {
            double ratio = A(k, i) / A(i, i);

            for (int j = i; j < len; j++) {
                A(k, j) -= ratio * A(i, j);
            }

            b[k] -= ratio * b[i];

        }
    }

    Vector<T> x(len);

    for (int i = len - 1; i >= 0; i--) {
        double sum = 0;

        for (int j = i + 1; j < len; j++) {
            sum += A(i, j) * x[j];
        }

        if (std::abs(A(i, i)) < 1e-18) {
            throw std::runtime_error("Zero on diagonal during back substitution");
        }

        x[i] = (b[i] - sum) / A(i, i);
    }

    return x;
}

template<class T>
Vector<T> gauss_without_pivot(const IMatrix<T>& A_in, Vector<T> b) {
    if (A_in.get_rows() != A_in.get_cols()) throw std::invalid_argument("Matrix must be square");
    SquareMatrix<T> A(A_in);
    int len = A.get_rows();

    // прямой ход
    for (int i = 0; i < len; i++) {
        if (std::abs(A(i, i)) < 1e-18) {
            throw std::runtime_error("Zero pivot encountered: Matrix is singular");
        }

        for (int k = i + 1; k < len; k++) {
            double ratio = A(k, i) / A(i, i);

            for (int j = i; j < len; j++) {
                A(k, j) -= ratio * A(i, j);
            }

            b[k] -= ratio * b[i];

        }
    }

    // ищем корни обратным ходом
    Vector<T> x(len);

    for (int i = len - 1; i >= 0; i--) {
        double sum = 0;

        for (int j = i + 1; j < len; j++) {
            sum += A(i, j) * x[j];
        }

        if (std::abs(A(i, i)) < 1e-18) {
            throw std::runtime_error("Zero on diagonal during back substitution");
        }

        x[i] = (b[i] - sum) / A(i, i);
    }

    return x;
}