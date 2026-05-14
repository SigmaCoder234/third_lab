#pragma once
#include "IMatrix.h"
#include "../second_lab/src/DynamicArray.h"
#include <stdexcept>

template<class T>
class SparseMatrix : public IMatrix<T> {
private:
    struct Element {
        int row;
        int col;
        T value;
    };
    DynamicArray<Element> elements;
    int rows;
    int cols;
    int count;

    int find_element(int r, int c) const {
        for (int i = 0; i < count; i++) {
            if (elements[i].row == r && elements[i].col == c) return i;
        }
        return -1;
    }

public:
    SparseMatrix(int r = 0, int c = 0) : elements(10), rows(r), cols(c), count(0) {}

    SparseMatrix(const IMatrix<T>& other) : elements(10), rows(other.get_rows()), cols(other.get_cols()), count(0) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                T val = other(i, j);
                if (val != T()) {
                    (*this)(i, j) = val;
                }
            }
        }
    }

    T operator()(int i, int j) const override {
        if (i < 0 || i >= rows || j < 0 || j >= cols) throw std::out_of_range("Index out of range");
        int idx = find_element(i, j);
        if (idx != -1) return elements[idx].value;
        return T();
    }

    T& operator()(int i, int j) override {
        if (i < 0 || i >= rows || j < 0 || j >= cols) throw std::out_of_range("Index out of range");
        int idx = find_element(i, j);
        if (idx != -1) return elements[idx].value;
        
        // Add new element
        if (count == elements.size()) {
            elements.ReSize(elements.size() * 2 + 1);
        }
        elements[count].row = i;
        elements[count].col = j;
        elements[count].value = T();
        count++;
        return elements[count - 1].value;
    }

    int get_rows() const override { return rows; }
    int get_cols() const override { return cols; }

    void swap_rows(int i, int j) override {
        if (i < 0 || i >= rows || j < 0 || j >= rows) throw std::out_of_range("Index out of range");
        if (i == j) return;
        for (int k = 0; k < count; k++) {
            if (elements[k].row == i) elements[k].row = j;
            else if (elements[k].row == j) elements[k].row = i;
        }
    }
};
