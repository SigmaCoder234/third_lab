#include <iostream>
#include <chrono>

#include "decompositions/gauss.h"
#include "decompositions/LU.h"
#include "tests/tests.h"
#include "hand_work/hand_work.h"
#include "matrix/matrix.h"

//TODO: сделать сдек дек очередь

void run_tests() {
    std::cout << "============= TESTS STARTED ==========\n";
    auto start = std::chrono::high_resolution_clock::now();
    first_test();
    second_test();
    third_test();
    auto end = std::chrono::high_resolution_clock::now();
    double res  = std::chrono::duration<double>(end - start).count();
    std::cout << "\n============= TESTS ENDED =============\n";
    std::cout << "\nALL TESTS TOOK " << res << " SECONDS\n";
}

void menu() {
    std::cout << "\n============= MENU =============\n";
    std::cout << "1. Create matrix\n";
    std::cout << "2. Create vector\n";
    std::cout << "3. Print matrix\n";
    std::cout << "4. Print Hilbert matrix\n";
    std::cout << "5. Print vector\n";
    std::cout << "6. Choose decompose\n";
    std::cout << "7. Choose math operation";
    std::cout << "0. Quit\n";
    std::cout << "Your choice: ";
}

template <class T>
void run_menu() {
    Matrix<T> A(0), B(0), L(0), U(0), H(0), ANS(0);
    Vector<T> a(0), b(0), ans(0);
    int dim;
    bool work = true;
    int choice;
    while (work) {
        menu();
        choice = safe_input();
        switch (choice) {

            // создание матрицы
            case 1:
                std::cout << "Input matrix dim: ";
                dim = safe_input();
                A = fill_matrix<T>(dim);
                std::cout << "\n Your matrix: \n";
                matrix_print<T>(A);
                break;

            // создание вектора
            case 2: 
                int len;
                std::cout << "Input vector len: ";
                len = safe_input();
                b = fill_vector<T>(len);
                std::cout << "\n Your vector: \n";
                vector_print<T>(b);
                break;

            // вывод матрицы
            case 3:
                if (!A.size()) {
                    std::cout << "Initialize matrix first\n";
                    break;
                }

                matrix_print<T>(A);
                break;

            // создание и вывод матрицы гильберта
            case 4:
                std::cout << "Input matrix dim: ";
                dim = safe_input(); 
                std::cout << "\n";
                H = create_gilbert_matrix<T>(dim);
                std::cout << "\n Your matrix: \n";
                matrix_print<T>(H);   
                break;

            // вывод вектора
            case 5:
                if (!b.size()) {
                    std::cout << "Initialize vector first\n";
                    break;
                }

                vector_print<T>(b);
                break;

            // Декомпозиции
            case 6: {
                std::cout << "Choose decomposition method:\n";
                std::cout << "1. Gauss without pivot\n";
                std::cout << "2. Gauss with pivot\n";
                std::cout << "3. LU decomposition\n";

                int decomposition_choice = safe_input();

                switch(decomposition_choice) {
                    case 1:
                    // гаусс без опорного элемента
                    if (!A.size()) {
                        std::cout << "Initialize matrix first\n";
                        break;
                    }

                    if (!b.size()) {
                        std::cout << "Initialize vector first\n";
                        break;
                    }

                    if (A.size() != b.size()) {
                        std::cout << "different dims\n";
                        break;
                    }

                    ans = gauss_without_pivot<T>(A, b);
                    vector_print<T>(ans);
                    break;

                case 2:
                    // гаусс с опорным элементом
                    if (!A.size()) {
                        std::cout << "Initialize matrix first\n";
                        break;
                    }

                    if (!b.size()) {
                        std::cout << "Initialize vector first\n";
                        break;
                    }

                    if (A.size() != b.size()) {
                        std::cout << "different dims\n";
                        break;
                    }

                    ans = gauss_with_pivot<T>(A, b);
                    vector_print<T>(ans);
                    break;

                case 3:
                    // LU разложение
                    int chc;
                    std::cout << "Solve LU or Decompose LU? (1 for solve, 2 for decompose): ";
                    std::cin >> chc;
                    if (chc == 1) {
                        if (!A.size()) {
                            std::cout << "Initialize matrix first\n";
                            break;
                        }

                        if (!b.size()) {
                            std::cout << "Initialize vector first\n";
                            break;
                        }

                        if (A.size() != b.size()) {
                            std::cout << "different dims\n";
                            break;
                        }

                        else {
                            lu_decomposition<T>(A, L, U);

                            std::cout << "Print LU matrices? (1 for Yes, 0 for No): ";
                            bool print_lu = safe_bool_input();

                            if (print_lu) {
                                std::cout << "L: \n";
                                matrix_print<T>(L);
                                std::cout << "U: \n";
                                matrix_print<T>(U);
                            }
                            ans = solve_lu<T>(L, U, b);
                            std::cout << "LU decomposition and solve completed.\n";
                            vector_print<T>(ans);
                        }
                    }

                    if (chc == 2) {
                        if (!A.size()) {
                            std::cout << "Initialize matrix first\n";
                            break;
                        }

                        lu_decomposition<T>(A, L, U);

                        std::cout << "L: \n";
                        matrix_print<T>(L);
                        std::cout << "U: \n";
                        matrix_print<T>(U);
                    }
                    break;
                }
                break;
            }

            case 7: {
                int choise_math;
                std::cout << "Choose math operation:\n";
                std::cout << "1. Sum of matrices\n";
                std::cout << "2. Subtraction of matrices\n";
                std::cout << "3. Multiplication of matrices\n";
                std::cout << "4. Sum of vectors\n";
                std::cout << "5. Subtraction of vectors\n";
                std::cout << "6. Multiplication of vectors\n";
                choise_math = safe_input();
                switch(choise_math) {
                    case 1:
                        if (!A.size() || !B.size()) {
                            std::cout << "Initialize both matrices first\n";
                            break;
                        }

                        if (A.size() != B.size()) {
                            std::cout << "Matrices must have the same dimensions\n";
                            break;
                        }

                        ANS = A + B;
                        matrix_print<T>(ANS);
                        
                        break;
                    case 2:
                        if (!A.size() || !B.size()) {
                            std::cout << "Initialize both matrices first\n";
                            break;
                        }

                        if (A.size() != B.size()) {
                            std::cout << "Matrices must have the same dimensions\n";
                            break;
                        }

                        ANS = A - B;
                        matrix_print<T>(ANS);
                        
                        break;
                    case 3:
                        if (!A.size() || !B.size()) {
                            std::cout << "Initialize both matrices first\n";
                            break;
                        }

                        if (A.size() != B.size()) {
                            std::cout << "Matrices must have the same dimensions\n";
                            break;
                        }

                        ANS = A * B;
                        matrix_print<T>(ANS);
                        
                        break;
                    case 4:
                        if (!a.size() || !b.size()) {
                            std::cout << "Initialize both vectors first\n";
                            break;
                        }

                        if (a.size() != b.size()) {
                            std::cout << "Vectors must have the same dimensions\n";
                            break;
                        }

                        ans = a + b;
                        vector_print<T>(ans);
                        
                        break;
                    case 5:
                        if (!a.size() || !b.size()) {
                            std::cout << "Initialize both vectors first\n";
                            break;
                        }

                        if (a.size() != b.size()) {
                            std::cout << "Vectors must have the same dimensions\n";
                            break;
                        }

                        ans = a - b;
                        vector_print<T>(ans);
                        
                        break;
                    case 6:
                        if (!a.size() || !b.size()) {
                            std::cout << "Initialize both vectors first\n";
                            break;
                        }

                        if (a.size() != b.size()) {
                            std::cout << "Vectors must have the same dimensions\n";
                            break;
                        }

                        ans = a * b;
                        vector_print<T>(ans);
                        
                        break;
                }
                break;
            }

            // завершение работы
            case 0:
                work = false;
                break;

            default:
                printf("\nInvalid menu option. Please try again.\n");
                break;

        }
    }
}

int main() {
    std::cout << "Выберите тип данных:\n";
    std::cout << "1. int\n";
    std::cout << "2. double\n";
    std::cout << "3. run all tests\n";
    std::cout << "Ваш выбор: ";
    
    int type_choice;
    std::cin >> type_choice;
    
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
            std::cout << "Неверный выбор!\n";
    }
    
    return 0;
}
