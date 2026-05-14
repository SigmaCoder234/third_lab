#include <cstdio>
#include <iostream>
#include <string>

template<class T>
void matrix_print(const IMatrix<T>& A) {
    int rows = A.get_rows();
    int cols = A.get_cols();
    for (int i = 0; i < rows; i++) {
        std::cout << "|  ";
        for (int j = 0; j < cols; j++) {
            std::cout << A(i, j) << "  |  ";
        }
        std::cout << "\n";
    }
}

template<class T>
void vector_print(Vector<T> b) {
    std::cout << "|  ";
    for (int i = 0; i < b.size(); i++) {
        std::cout << b[i] << "  |  ";
    }
    std::cout << "\n";
}

template<class T>
SquareMatrix<T> fill_matrix(int dim, const std::string& name) {
    SquareMatrix<T> A(dim);

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            std::cout << name << "[" << i+1 << "][" << j+1 << "] = ";
            A(i, j) = safe_double_input();
        }
    }

    return A;
}
template<class T>
void fill_matrix_values(IMatrix<T>& A, const std::string& name) {
    int rows = A.get_rows();
    int cols = A.get_cols();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            try {
                std::cout << name << "[" << i+1 << "][" << j+1 << "] = ";
                A(i, j) = (T)safe_double_input();
            } catch (const std::exception& e) {
                // For DiagonalMatrix it might throw if non-diagonal is accessed
                // In that case we just skip or set to 0 (though it should already be 0)
                // Actually, IMatrix user should know which elements to fill.
                // But for general fill, we might want to skip non-modifiable elements.
            }
        }
    }
}

template<class T>
Vector<T> fill_vector(int len, const std::string& name) {
    Vector<T> b(len);

    for (int i = 0; i < len; i++) {
        std::cout << name << "[" << i+1 << "] = ";
        b[i] = safe_double_input();
    }

    return b;
}