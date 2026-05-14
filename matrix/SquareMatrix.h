#pragma once
#include "RectangularMatrix.h"

template<class T>
class SquareMatrix : public RectangularMatrix<T> {
public:
    SquareMatrix(int dim = 0) : RectangularMatrix<T>(dim, dim) {}
    SquareMatrix(const IMatrix<T>& other) : RectangularMatrix<T>(other) {
        if (other.get_rows() != other.get_cols()) throw std::invalid_argument("Matrix is not square");
    }
    int size() const { return this->rows; }
};
