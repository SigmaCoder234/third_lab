#include "hand_work.h"

#include <cstdio>
#include <iostream>

template<class T>
void matrix_print(Matrix<T> A) {
    for (int i = 0; i < A.size(); i++) {
        std::cout << "|  ";
        for (int j = 0; j < A.size(); j++) {
            std::cout << A[i][j] << "  |  ";
        }
        std::cout << "\n";
    }
}

template<class T>
void vector_print(Vector<T> b) {
    std::cout << "|  ";
    IEnumerator<T>* it = b.GetEnumerator();
    while (it->MoveNext()) {
        std::cout << it->Current() << "  |  ";
    }
    delete it;
}

template<class T>
Matrix<T> fill_matrix(int dim) {
    Matrix<T> A(dim);

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            std::cout << "A[" << i+1 << "][" << j+1 << "] = ";
            A[i][j] = safe_double_input();
        }
    }

    return A;
}

template<class T>
Vector<T> fill_vector(int len) {
    Vector<T> b(len);

    for (int i = 0; i < len; i++) {
        std::cout << "b[" << i+1 << "] = ";
        b[i] = safe_double_input();
    }

    return b;
}