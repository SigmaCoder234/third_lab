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
    std::cout << "6. Decompose matrix with gauss\n";
    std::cout << "7. Decompose matrix with gauss with pivot\n";
    std::cout << "8. Decompose matrix with LU\n";
    std::cout << "9. Run all tests\n";
    std::cout << "0. Quit\n";
    std::cout << "Your choice: ";
}

int main() {
    Matrix<double> A(0), L(0), U(0), H(0);
    Vector<double> b(0), ans(0);
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
                A = fill_matrix(dim);
                std::cout << "\n Your matrix: \n";
                matrix_print(A);
                break;

            // создание вектора
            case 2: 
                int len;
                std::cout << "Input vector len: ";
                len = safe_input();
                b = fill_vector(len);
                std::cout << "\n Your vector: \n";
                vector_print(b);
                break;

            // вывод матрицы
            case 3:
                if (!A.size()) {
                    std::cout << "Initialize matrix first\n";
                    break;
                }

                matrix_print(A);
                break;

            // создание и вывод матрицы гильберта
            case 4:
                std::cout << "Input matrix dim: ";
                dim = safe_input(); 
                std::cout << "\n";
                H = create_gilbert_matrix<double>(dim);
                std::cout << "\n Your matrix: \n";
                matrix_print(H);   
                break;

            // вывод вектора
            case 5:
                if (!b.size()) {
                    std::cout << "Initialize vector first\n";
                    break;
                }

                vector_print(b);
                break;

            // гаусс без опорного элемента
            case 6:
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

                ans = gauss_without_pivot(A, b);
                vector_print(ans);
                break;

            // гаусс с опорным элементом
            case 7:
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

                ans = gauss_with_pivot(A, b);
                vector_print(ans);
                break;

            // LU разложение
            case 8:
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
                        lu_decomposition(A, L, U);

                        std::cout << "Print LU matrices? (1 for Yes, 0 for No): ";
                        bool print_lu = safe_bool_input();

                        if (print_lu) {
                            std::cout << "L: \n";
                            matrix_print(L);
                            std::cout << "U: \n";
                            matrix_print(U);
                        }
                        ans = solve_lu(L, U, b);
                        std::cout << "LU decomposition and solve completed.\n";
                        vector_print(ans);
                    }
                }

                if (chc == 2) {
                    if (!A.size()) {
                        std::cout << "Initialize matrix first\n";
                        break;
                    }

                    lu_decomposition(A, L, U);

                    std::cout << "L: \n";
                    matrix_print(L);
                    std::cout << "U: \n";
                    matrix_print(U);
                }
                break;

            // тесты
            case 9:
                run_tests();
                break;

            // завершение работы
            case 0:
                work = false;
                break;

            default:
                printf("\nInvalid menu option. Please try again.\n");
                break;

        }
    }
    return 0;
}