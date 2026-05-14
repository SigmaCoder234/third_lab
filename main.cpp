#include <iostream>
#include <chrono>

#include "decompositions/gauss.h"
#include "decompositions/LU.h"
#include "tests/tests.h"
#include "hand_work/hand_work.h"
#include "matrix/IMatrix.h"
#include "matrix/matrix.h"
#include "matrix/Vector.h"
#include "matrix/MatrixOperations.h"

void run_tests() {
    std::cout << "============= PERFORMANCE TESTS ==========\n";
    auto start = std::chrono::high_resolution_clock::now();
    first_test();
    second_test();
    third_test();
    auto end = std::chrono::high_resolution_clock::now();
    double res  = std::chrono::duration<double>(end - start).count();
    std::cout << "\nPERFORMANCE TESTS TOOK " << res << " SECONDS\n";

    std::cout << "\n============= GTEST UNIT TESTS ==========\n";
    int gtest_result = system("run_gtests.exe");
    if (gtest_result != 0) {
        gtest_result = system(".\\build\\run_gtests.exe");
    }
    std::cout << "\n============= ALL TESTS ENDED =============\n";
}

void menu() {
    std::cout << "\n============= MENU =============\n";
    std::cout << "1. Create matrix\n";
    std::cout << "2. Create vector\n";
    std::cout << "3. Print matrix\n";
    std::cout << "4. Print vector\n";
    std::cout << "5. Create and print Hilbert matrix\n";
    std::cout << "6. Choose decompose\n";
    std::cout << "7. Choose math operation\n";
    std::cout << "0. Quit\n";
    std::cout << "Your choice: ";
}

template <class T>
IMatrix<T>** get_matrix_ptr(IMatrix<T>* &A, IMatrix<T>* &B, const std::string& prompt = "Which matrix? (1 for A, 2 for B): ") {
    std::cout << prompt;
    int choice = safe_input();
    if (choice == 1) return &A;
    if (choice == 2) return &B;
    std::cout << "Invalid choice\n";
    return nullptr;
}

template <class T>
Vector<T>* get_vector_ptr(Vector<T>& a, Vector<T>& b, const std::string& prompt = "Which vector? (1 for a, 2 for b): ") {
    std::cout << prompt;
    int choice = safe_input();
    if (choice == 1) return &a;
    if (choice == 2) return &b;
    std::cout << "Invalid choice\n";
    return nullptr;
}

template <class T>
IMatrix<T>* create_matrix_interactive() {
    std::cout << "Select matrix type:\n";
    std::cout << "1. Square Matrix\n";
    std::cout << "2. Rectangular Matrix\n";
    std::cout << "3. Diagonal Matrix\n";
    std::cout << "4. Sparse Matrix\n";
    std::cout << "Your choice: ";
    int choice = safe_input();

    int rows, cols;
    switch(choice) {
        case 1: {
            std::cout << "Input matrix size (N for NxN): ";
            rows = safe_input();
            return new SquareMatrix<T>(rows);
        }
        case 2: {
            std::cout << "Input rows: ";
            rows = safe_input();
            std::cout << "Input cols: ";
            cols = safe_input();
            return new RectangularMatrix<T>(rows, cols);
        }
        case 3: {
            std::cout << "Input matrix size (N for NxN diagonal): ";
            rows = safe_input();
            return new DiagonalMatrix<T>(rows);
        }
        case 4: {
            std::cout << "Input rows: ";
            rows = safe_input();
            std::cout << "Input cols: ";
            cols = safe_input();
            return new SparseMatrix<T>(rows, cols);
        }
        default:
            std::cout << "Invalid choice, defaulting to Square Matrix.\n";
            std::cout << "Input matrix size (N for NxN): ";
            rows = safe_input();
            return new SquareMatrix<T>(rows);
    }
}

template <class T>
void handle_gauss(IMatrix<T>* A, IMatrix<T>* B, Vector<T>& a, Vector<T>& b, Vector<T>& ans, Vector<T> (*gauss_func)(const IMatrix<T>&, Vector<T>)) {
    std::cout << "Choose matrix for decompose: (1 for A and 2 for B)\n";
    int choice = safe_input();
    IMatrix<T>* m = (choice == 1 ? A : (choice == 2 ? B : nullptr));
    
    if (!m) { std::cout << "Invalid choice or matrix not initialized\n"; return; }
    if (m->get_rows() == 0) { std::cout << "Initialize matrix first\n"; return; }

    Vector<T>* v = get_vector_ptr(a, b, "Choose vector for decompose: (1 for a and 2 for b)\n");
    if (!v) return;
    if (v->size() == 0) { std::cout << "Initialize vector first\n"; return; }

    if (m->get_rows() != v->size()) {
        std::cout << "different dims\n";
        return;
    }

    ans = gauss_func(*m, *v);
    std::cout << "Result: \n";
    vector_print<T>(ans);
}

template <class T>
void run_menu() {
    IMatrix<T>* A = nullptr;
    IMatrix<T>* B = nullptr;
    IMatrix<T>* ANS = nullptr;
    
    SquareMatrix<T> L(0), U(0), H(0);
    Vector<T> a(0), b(0), ans(0);
    
    int rows, cols, chc;
    bool work = true;
    int choice;
    
    while (work) {
        menu();
        choice = safe_input();
        switch (choice) {
            case 1: {
                IMatrix<T>** m_ptr = get_matrix_ptr(A, B, "Which matrix you want to initialize? (1 for A and 2 for B)\n");
                if (m_ptr) {
                    if (*m_ptr) delete *m_ptr;
                    *m_ptr = create_matrix_interactive<T>();
                    fill_matrix_values(**m_ptr, (m_ptr == &A ? "A" : "B"));
                    
                    std::cout << "\n Your matrix: \n";
                    matrix_print<T>(**m_ptr);
                }
                break;
            }

            case 2: {
                Vector<T>* v = get_vector_ptr(a, b, "Which vector you want to initialize? (1 for a and 2 for b)\n");
                if (v) {
                    std::cout << "Input vector dim: ";
                    int dim = safe_input();
                    *v = fill_vector<T>(dim, (v == &a ? "a" : "b"));
                    std::cout << "\n Your vector: \n";
                    vector_print<T>(*v);
                }
                break;
            }

            case 3: {
                std::cout << "Which matrix you want to print? (1 for A, 2 for B, 3 for ANS): ";
                int p_chc = safe_input();
                IMatrix<T>* m = nullptr;
                if (p_chc == 1) m = A;
                else if (p_chc == 2) m = B;
                else if (p_chc == 3) m = ANS;
                
                if (m) {
                    if (m->get_rows() == 0) {
                        std::cout << "Matrix is empty\n";
                    } else {
                        std::cout << "\n Your matrix: \n";
                        matrix_print<T>(*m);
                    }
                } else {
                    std::cout << "Matrix not initialized\n";
                }
                break;
            }

            case 4: {
                Vector<T>* v = get_vector_ptr(a, b, "Which vector you want to print? (1 for a and 2 for b)\n");
                if (v) {
                    if (v->size() == 0) {
                        std::cout << "Initialize vector first\n";
                    } else {
                        std::cout << "\n Your vector: \n";
                        vector_print<T>(*v);
                    }
                }
                break;
            }

            case 5:
                std::cout << "Input matrix dim: ";
                rows = safe_input(); 
                std::cout << "\n";
                H = create_gilbert_matrix<T>(rows);
                std::cout << "\n Your matrix: \n";
                matrix_print<T>(H);   
                break;

            case 6: {
                std::cout << "Choose decomposition method:\n";
                std::cout << "1. Gauss without pivot\n";
                std::cout << "2. Gauss with pivot\n";
                std::cout << "3. LU decomposition\n";

                int decomposition_choice = safe_input();

                switch(decomposition_choice) {
                    case 1:
                        handle_gauss<T>(A, B, a, b, ans, gauss_without_pivot<T>);
                        break;
                    case 2:
                        handle_gauss<T>(A, B, a, b, ans, gauss_with_pivot<T>);
                        break;
                    case 3: {
                        std::cout << "Solve LU or Decompose LU? (1 for solve, 2 for decompose): ";
                        chc = safe_input();

                        IMatrix<T>** m_ptr = get_matrix_ptr(A, B, "Choose matrix: (1 for A and 2 for B)\n");
                        if (!m_ptr || !*m_ptr) break;

                        if (chc == 1) { // Solve
                            Vector<T>* v = get_vector_ptr(a, b, "Choose vector: (1 for a and 2 for b)\n");
                            if (!v || v->size() == 0) break;
                            if ((*m_ptr)->get_rows() != v->size()) {
                                std::cout << "different dims\n";
                                break;
                            }
                            lu_decomposition<T>(**m_ptr, L, U);
                            ans = solve_lu<T>(L, U, *v);
                            std::cout << "Result: \n";
                            vector_print<T>(ans);
                        } else if (chc == 2) { // Decompose
                            lu_decomposition<T>(**m_ptr, L, U);
                            std::cout << "L: \n"; matrix_print<T>(L);
                            std::cout << "U: \n"; matrix_print<T>(U);
                        }
                        break;
                    }
                }
                break;
            }

            case 7: {
                std::cout << "Choose math operation:\n";
                std::cout << "1. Sum of matrices (A + B)\n";
                std::cout << "2. Subtraction of matrices (A - B)\n";
                std::cout << "3. Multiplication of matrices (A * B)\n";
                std::cout << "4. Sum of vectors (a + b)\n";
                std::cout << "5. Subtraction of vectors (a - b)\n";
                std::cout << "6. Multiplication of vectors (a * b)\n";
                int math_choice = safe_input();
                
                try {
                    switch(math_choice) {
                        case 1:
                            if (!A || !B) throw std::runtime_error("Initialize both matrices");
                            if (ANS) delete ANS;
                            ANS = new RectangularMatrix<T>(*A + *B);
                            matrix_print<T>(*ANS);
                            break;
                        case 2:
                            if (!A || !B) throw std::runtime_error("Initialize both matrices");
                            if (ANS) delete ANS;
                            ANS = new RectangularMatrix<T>(*A - *B);
                            matrix_print<T>(*ANS);
                            break;
                        case 3:
                            if (!A || !B) throw std::runtime_error("Initialize both matrices");
                            if (ANS) delete ANS;
                            ANS = new RectangularMatrix<T>(*A * *B);
                            matrix_print<T>(*ANS);
                            break;
                        case 4:
                            ans = a + b;
                            vector_print<T>(ans);
                            break;
                        case 5:
                            ans = a - b;
                            vector_print<T>(ans);
                            break;
                        case 6:
                            ans = a * b;
                            vector_print<T>(ans);
                            break;
                    }
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;
            }

            case 0:
                work = false;
                break;
        }
    }
    if (A) delete A;
    if (B) delete B;
    if (ANS) delete ANS;
}

int main() {
    std::cout << "Choose data type or run tests:\n";
    std::cout << "1. int\n";
    std::cout << "2. double\n";
    std::cout << "3. run all tests\n";
    std::cout << "Your choice: ";
    
    int type_choice;
    if (!(std::cin >> type_choice)) return 0;
    
    switch (type_choice) {
        case 1:
            run_menu<int>();
            break;
        case 2:
            run_menu<double>();
            break;
        case 3:
            run_tests();
            break;
        default:
            std::cout << "Invalid choice!\n";
    }
    
    return 0;
}