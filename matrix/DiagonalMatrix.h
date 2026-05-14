#pragma once
#include "IMatrix.h"
#include "../second_lab/src/DynamicArray.h"
#include <stdexcept>

template<class T>
class DiagonalMatrix : public IMatrix<T> {
private:
    DynamicArray<T> data;
    int dim;
public:
    DiagonalMatrix(int d = 0) : data(d), dim(d) {
        for (int i = 0; i < dim; i++) data[i] = T();
    }

    DiagonalMatrix(const IMatrix<T>& other) : data(other.get_rows()), dim(other.get_rows()) {
        if (other.get_rows() != other.get_cols()) throw std::invalid_argument("Matrix is not square");
        for (int i = 0; i < dim; i++) {
            data[i] = other(i, i);
            // Optionally check if other elements are zero, but here we just take the diagonal
        }
    }

    T operator()(int i, int j) const override {
        if (i < 0 || i >= dim || j < 0 || j >= dim) throw std::out_of_range("Index out of range");
        if (i == j) return data[i];
        return T();
    }

    T& operator()(int i, int j) override {
        if (i < 0 || i >= dim || j < 0 || j >= dim) throw std::out_of_range("Index out of range");
        if (i == j) return data[i];
        throw std::out_of_range("Cannot modify non-diagonal element in DiagonalMatrix");
    }

    int get_rows() const override { return dim; }
    int get_cols() const override { return dim; }

    void swap_rows(int i, int j) override {
        if (i == j) return;
        throw std::logic_error("Cannot swap rows in a DiagonalMatrix without breaking its structure");
    }
};
