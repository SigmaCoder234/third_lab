#include "hand_work.h"

#include <cstdio>
#include <iostream>

void matrix_print(Matrix<double> A) {
    for (int i = 0; i < A.size(); i++) {
        std::cout << "|  ";
        for (int j = 0; j < A.size(); j++) {
            std::cout << A[i][j] << "  |  ";
        }
        std::cout << "\n";
    }
}

void vector_print(Vector<double> b) {
    std::cout << "|  ";
    IEnumerator<double>* it = b.GetEnumerator();
    while (it->MoveNext()) {
        std::cout << it->Current() << "  |  ";
    }
    delete it;
}

// функция для безопасного ввода int начений
int safe_input() {
    int value;
    int res;
    while (true) {
        res = scanf("%d", &value);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (res == 1) {
            break;
        }

        else {
            printf("Invalid input. Please try again: ");
        }
    }
    return value;
}

// функция для безопасного ввода double начений
double safe_double_input() {
    double value;
    double res;
    while (true) {
        res = scanf("%lf", &value);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (res == 1.0) {
            break;
        }

        else {
            printf("Invalid input. Please try again: ");
        }
    }
    return value;
}

// Функция для безопасного ввода bool значений (y/n или 1/0)
bool safe_bool_input() {
    int value;
    int res;
    while (true) {
        res = scanf("%d", &value);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (res == 1 && (value == 0 || value == 1)) {
            break;
        }

        else {
            printf("Invalid input. Please enter 1 (Yes) or 0 (No): ");
        }
    }
    return value == 1;
}

Matrix<double> fill_matrix(int dim) {
    Matrix<double> A(dim);

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            std::cout << "A[" << i+1 << "][" << j+1 << "] = ";
            A[i][j] = safe_double_input();
        }
    }

    return A;
}

Vector<double> fill_vector(int len) {
    Vector<double> b(len);

    for (int i = 0; i < len; i++) {
        std::cout << "b[" << i+1 << "] = ";
        b[i] = safe_double_input();
    }

    return b;
}