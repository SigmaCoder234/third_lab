#pragma once
#include "IMatrix.h"
#include "RectangularMatrix.h"
#include "Vector.h"
#include "SquareMatrix.h"
#include <cstdlib>

template<class T>
RectangularMatrix<T> operator+(const IMatrix<T>& lhs, const IMatrix<T>& rhs) {
    if (lhs.get_rows() != rhs.get_rows() || lhs.get_cols() != rhs.get_cols())
        throw std::invalid_argument("Different dimensions");
    RectangularMatrix<T> res(lhs.get_rows(), lhs.get_cols());
    for (int i = 0; i < lhs.get_rows(); i++) {
        for (int j = 0; j < lhs.get_cols(); j++) {
            res(i, j) = lhs(i, j) + rhs(i, j);
        }
    }
    return res;
}

template<class T>
RectangularMatrix<T> operator-(const IMatrix<T>& lhs, const IMatrix<T>& rhs) {
    if (lhs.get_rows() != rhs.get_rows() || lhs.get_cols() != rhs.get_cols())
        throw std::invalid_argument("Different dimensions");
    RectangularMatrix<T> res(lhs.get_rows(), lhs.get_cols());
    for (int i = 0; i < lhs.get_rows(); i++) {
        for (int j = 0; j < lhs.get_cols(); j++) {
            res(i, j) = lhs(i, j) - rhs(i, j);
        }
    }
    return res;
}

template<class T>
RectangularMatrix<T> operator*(const IMatrix<T>& lhs, const IMatrix<T>& rhs) {
    if (lhs.get_cols() != rhs.get_rows())
        throw std::invalid_argument("Incompatible dimensions for multiplication");
    RectangularMatrix<T> res(lhs.get_rows(), rhs.get_cols());
    for (int i = 0; i < lhs.get_rows(); i++) {
        for (int j = 0; j < rhs.get_cols(); j++) {
            T sum = T();
            for (int k = 0; k < lhs.get_cols(); k++) {
                sum += lhs(i, k) * rhs(k, j);
            }
            res(i, j) = sum;
        }
    }
    return res;
}

template<class T>
Vector<T> matrix_by_vector(const IMatrix<T>& A, const Vector<T>& b) {
    if (A.get_cols() != b.size()) throw std::invalid_argument("Incompatible dimensions");
    Vector<T> res(A.get_rows());
    for (int i = 0; i < A.get_rows(); i++) {
        T sum = T();
        for (int j = 0; j < A.get_cols(); j++) {
            sum += A(i, j) * b[j];
        }
        res[i] = sum;
    }
    return res;
}

template<class T>
SquareMatrix<T> create_matrix(int dim) {
    SquareMatrix<T> res(dim);
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            res(i, j) = (T)(rand() % 100) / 10.0;
        }
    }
    return res;
}

template<class T>
SquareMatrix<T> create_gilbert_matrix(int dim) {
    SquareMatrix<T> res(dim);
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            res(i, j) = 1.0 / (i + j + 1);
        }
    }
    return res;
}

template<class T>
Vector<T> create_vector(int len) {
    Vector<T> res(len);
    for (int i = 0; i < len; i++) {
        res[i] = (T)(rand() % 100) / 10.0;
    }
    return res;
}
