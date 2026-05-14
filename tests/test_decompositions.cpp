#include <gtest/gtest.h>
#include "../matrix/matrix.h"
#include "../decompositions/gauss.h"
#include "../decompositions/LU.h"
#include "../math_ops/math_ops.h"

// Система 2x2:
// 2x + y = 5
// x - y = -2
// Ответ: x = 1, y = 3

TEST(DecompositionsTest, GaussWithPivot) {
    SquareMatrix<double> A(2);
    A(0, 0) = 2; A(0, 1) = 1;
    A(1, 0) = 1; A(1, 1) = -1;
    
    Vector<double> b(2);
    b[0] = 5; b[1] = -2;
    
    Vector<double> x = gauss_with_pivot<double>(A, b);
    
    EXPECT_NEAR(x[0], 1.0, 1e-9);
    EXPECT_NEAR(x[1], 3.0, 1e-9);
}

TEST(DecompositionsTest, GaussWithoutPivot) {
    SquareMatrix<double> A(2);
    A(0, 0) = 2; A(0, 1) = 1;
    A(1, 0) = 1; A(1, 1) = -1;
    
    Vector<double> b(2);
    b[0] = 5; b[1] = -2;
    
    Vector<double> x = gauss_without_pivot<double>(A, b);
    
    EXPECT_NEAR(x[0], 1.0, 1e-9);
    EXPECT_NEAR(x[1], 3.0, 1e-9);
}

TEST(DecompositionsTest, LUDecomposition) {
    SquareMatrix<double> A(2);
    A(0, 0) = 2; A(0, 1) = 1;
    A(1, 0) = 1; A(1, 1) = -1;
    
    Vector<double> b(2);
    b[0] = 5; b[1] = -2;
    
    SquareMatrix<double> L(2), U(2);
    lu_decomposition<double>(A, L, U);
    
    // Check if L * U = A
    auto LU = L * U;
    EXPECT_NEAR(LU(0, 0), A(0, 0), 1e-9);
    EXPECT_NEAR(LU(0, 1), A(0, 1), 1e-9);
    EXPECT_NEAR(LU(1, 0), A(1, 0), 1e-9);
    EXPECT_NEAR(LU(1, 1), A(1, 1), 1e-9);
    
    Vector<double> x = solve_lu<double>(L, U, b);
    EXPECT_NEAR(x[0], 1.0, 1e-9);
    EXPECT_NEAR(x[1], 3.0, 1e-9);
}

TEST(DecompositionsTest, SparseMatrixLU) {
    SparseMatrix<double> A(2, 2);
    A(0, 0) = 2; A(0, 1) = 1;
    A(1, 0) = 1; A(1, 1) = -1;
    
    Vector<double> b(2);
    b[0] = 5; b[1] = -2;
    
    SquareMatrix<double> L(2), U(2);
    lu_decomposition<double>(A, L, U);
    
    Vector<double> x = solve_lu<double>(L, U, b);
    EXPECT_NEAR(x[0], 1.0, 1e-9);
    EXPECT_NEAR(x[1], 3.0, 1e-9);
}
