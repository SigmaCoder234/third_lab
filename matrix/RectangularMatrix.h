#pragma once
#include "IMatrix.h"
#include "../second_lab/src/DynamicArray.h"
#include <stdexcept>

template<class T>
class RectangularMatrix : public IMatrix<T> {
protected:
    DynamicArray<T> data;
    int rows;
    int cols;
public:
    RectangularMatrix(int r = 0, int c = 0) : data(r * c), rows(r), cols(c) {
        for (int i = 0; i < r * c; i++) data[i] = T();
    }

    RectangularMatrix(const IMatrix<T>& other) : data(other.get_rows() * other.get_cols()), rows(other.get_rows()), cols(other.get_cols()) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i * cols + j] = other(i, j);
            }
        }
    }

    T operator()(int i, int j) const override {
        if (i < 0 || i >= rows || j < 0 || j >= cols) throw std::out_of_range("Index out of range");
        return data[i * cols + j];
    }

    T& operator()(int i, int j) override {
        if (i < 0 || i >= rows || j < 0 || j >= cols) throw std::out_of_range("Index out of range");
        return data[i * cols + j];
    }

    int get_rows() const override { return rows; }
    int get_cols() const override { return cols; }

    void swap_rows(int i, int j) override {
        if (i < 0 || i >= rows || j < 0 || j >= rows) throw std::out_of_range("Index out of range");
        for (int k = 0; k < cols; k++) {
            std::swap(data[i * cols + k], data[j * cols + k]);
        }
    }

    RectangularMatrix<T>& operator+=(const IMatrix<T>& other) {
        if (rows != other.get_rows() || cols != other.get_cols()) throw std::invalid_argument("Different dimensions");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                (*this)(i, j) += other(i, j);
            }
        }
        return *this;
    }

    RectangularMatrix<T>& operator-=(const IMatrix<T>& other) {
        if (rows != other.get_rows() || cols != other.get_cols()) throw std::invalid_argument("Different dimensions");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                (*this)(i, j) -= other(i, j);
            }
        }
        return *this;
    }

    RectangularMatrix<T>& operator*=(const IMatrix<T>& other) {
        if (cols != other.get_rows()) throw std::invalid_argument("Incompatible dimensions for multiplication");
        RectangularMatrix<T> result(rows, other.get_cols());
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.get_cols(); j++) {
                T sum = T();
                for (int k = 0; k < cols; k++) {
                    sum += (*this)(i, k) * other(k, j);
                }
                result(i, j) = sum;
            }
        }
        *this = result;
        return *this;
    }
};