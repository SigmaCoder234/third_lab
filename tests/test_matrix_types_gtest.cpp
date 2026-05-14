#include <gtest/gtest.h>
#include "../matrix/IMatrix.h"
#include "../matrix/RectangularMatrix.h"
#include "../matrix/SquareMatrix.h"
#include "../matrix/DiagonalMatrix.h"
#include "../matrix/SparseMatrix.h"
#include "../matrix/MatrixOperations.h"

// ====== RectangularMatrix Tests ======

TEST(RectangularMatrixTest, CreateAndAccess) {
    RectangularMatrix<int> m(2, 3);
    m(0, 0) = 1; m(0, 1) = 2; m(0, 2) = 3;
    m(1, 0) = 4; m(1, 1) = 5; m(1, 2) = 6;

    EXPECT_EQ(m.get_rows(), 2);
    EXPECT_EQ(m.get_cols(), 3);
    EXPECT_EQ(m(0, 0), 1);
    EXPECT_EQ(m(0, 1), 2);
    EXPECT_EQ(m(1, 2), 6);
}

TEST(RectangularMatrixTest, SwapRows) {
    RectangularMatrix<int> m(2, 2);
    m(0, 0) = 1; m(0, 1) = 2;
    m(1, 0) = 3; m(1, 1) = 4;
    m.swap_rows(0, 1);
    EXPECT_EQ(m(0, 0), 3);
    EXPECT_EQ(m(1, 0), 1);
}

TEST(RectangularMatrixTest, OutOfRange) {
    RectangularMatrix<int> m(2, 2);
    EXPECT_THROW(m(5, 0), std::out_of_range);
    EXPECT_THROW(m(-1, 0), std::out_of_range);
}

// ====== SquareMatrix Tests ======

TEST(SquareMatrixTest, CreateAndSize) {
    SquareMatrix<int> m(3);
    EXPECT_EQ(m.size(), 3);
    EXPECT_EQ(m.get_rows(), 3);
    EXPECT_EQ(m.get_cols(), 3);
}

TEST(SquareMatrixTest, SetAndGet) {
    SquareMatrix<double> m(2);
    m(0, 0) = 1.5; m(0, 1) = 2.5;
    m(1, 0) = 3.5; m(1, 1) = 4.5;
    EXPECT_DOUBLE_EQ(m(0, 0), 1.5);
    EXPECT_DOUBLE_EQ(m(1, 1), 4.5);
}

TEST(SquareMatrixTest, CopyFromIMatrix) {
    SquareMatrix<int> a(2);
    a(0, 0) = 10; a(0, 1) = 20;
    a(1, 0) = 30; a(1, 1) = 40;
    SquareMatrix<int> b(a);
    EXPECT_EQ(b(0, 0), 10);
    EXPECT_EQ(b(1, 1), 40);
}

// ====== DiagonalMatrix Tests ======

TEST(DiagonalMatrixTest, DiagonalAccess) {
    DiagonalMatrix<int> m(3);
    m(0, 0) = 1;
    m(1, 1) = 2;
    m(2, 2) = 3;
    EXPECT_EQ(m(0, 0), 1);
    EXPECT_EQ(m(1, 1), 2);
    EXPECT_EQ(m(2, 2), 3);
}

TEST(DiagonalMatrixTest, NonDiagonalIsZero) {
    DiagonalMatrix<int> m(3);
    m(0, 0) = 5;
    const DiagonalMatrix<int>& cm = m;
    EXPECT_EQ(cm(0, 1), 0);
    EXPECT_EQ(cm(1, 0), 0);
    EXPECT_EQ(cm(2, 0), 0);
}

TEST(DiagonalMatrixTest, CannotModifyNonDiagonal) {
    DiagonalMatrix<int> m(3);
    EXPECT_THROW(m(0, 1) = 5, std::out_of_range);
}

TEST(DiagonalMatrixTest, CannotSwapRows) {
    DiagonalMatrix<int> m(3);
    EXPECT_THROW(m.swap_rows(0, 1), std::logic_error);
}

TEST(DiagonalMatrixTest, SwapSameRowNoThrow) {
    DiagonalMatrix<int> m(3);
    EXPECT_NO_THROW(m.swap_rows(1, 1));
}

// ====== SparseMatrix Tests ======

TEST(SparseMatrixTest, DefaultIsZero) {
    SparseMatrix<int> m(10, 10);
    EXPECT_EQ(m(0, 0), 0);
    EXPECT_EQ(m(5, 5), 0);
    EXPECT_EQ(m(9, 9), 0);
}

TEST(SparseMatrixTest, SetAndGet) {
    SparseMatrix<int> m(100, 100);
    m(10, 20) = 50;
    m(99, 99) = 100;
    EXPECT_EQ(m(10, 20), 50);
    EXPECT_EQ(m(99, 99), 100);
    EXPECT_EQ(m(0, 0), 0);
}

TEST(SparseMatrixTest, SwapRows) {
    SparseMatrix<int> m(3, 3);
    m(0, 0) = 1;
    m(1, 1) = 2;
    m.swap_rows(0, 1);
    EXPECT_EQ(m(1, 0), 1);
    EXPECT_EQ(m(0, 1), 2);
}

TEST(SparseMatrixTest, OutOfRange) {
    SparseMatrix<int> m(5, 5);
    EXPECT_THROW(m(10, 0), std::out_of_range);
}

// ====== Cross-type Math Operations ======

TEST(MatrixOpsTest, AddSquareAndDiagonal) {
    SquareMatrix<int> A(2);
    A(0, 0) = 1; A(0, 1) = 2;
    A(1, 0) = 3; A(1, 1) = 4;

    DiagonalMatrix<int> D(2);
    D(0, 0) = 10;
    D(1, 1) = 20;

    RectangularMatrix<int> sum = A + D;
    EXPECT_EQ(sum(0, 0), 11);
    EXPECT_EQ(sum(0, 1), 2);
    EXPECT_EQ(sum(1, 0), 3);
    EXPECT_EQ(sum(1, 1), 24);
}

TEST(MatrixOpsTest, SubtractMatrices) {
    SquareMatrix<int> A(2);
    A(0, 0) = 10; A(0, 1) = 20;
    A(1, 0) = 30; A(1, 1) = 40;

    SquareMatrix<int> B(2);
    B(0, 0) = 1; B(0, 1) = 2;
    B(1, 0) = 3; B(1, 1) = 4;

    RectangularMatrix<int> diff = A - B;
    EXPECT_EQ(diff(0, 0), 9);
    EXPECT_EQ(diff(0, 1), 18);
    EXPECT_EQ(diff(1, 0), 27);
    EXPECT_EQ(diff(1, 1), 36);
}

TEST(MatrixOpsTest, MultiplySquareByDiagonal) {
    SquareMatrix<int> A(2);
    A(0, 0) = 1; A(0, 1) = 2;
    A(1, 0) = 3; A(1, 1) = 4;

    DiagonalMatrix<int> D(2);
    D(0, 0) = 10;
    D(1, 1) = 20;

    // [1 2] * [10 0 ] = [10 40]
    // [3 4]   [0  20]   [30 80]
    RectangularMatrix<int> prod = A * D;
    EXPECT_EQ(prod(0, 0), 10);
    EXPECT_EQ(prod(0, 1), 40);
    EXPECT_EQ(prod(1, 0), 30);
    EXPECT_EQ(prod(1, 1), 80);
}

TEST(MatrixOpsTest, DimensionMismatchThrows) {
    RectangularMatrix<int> A(2, 3);
    RectangularMatrix<int> B(2, 2);
    EXPECT_THROW(A + B, std::invalid_argument);
}

TEST(MatrixOpsTest, MultiplyDimensionMismatchThrows) {
    RectangularMatrix<int> A(2, 3);
    RectangularMatrix<int> B(2, 2);
    EXPECT_THROW(A * B, std::invalid_argument);
}

TEST(MatrixOpsTest, MatrixByVector) {
    SquareMatrix<int> A(2);
    A(0, 0) = 1; A(0, 1) = 2;
    A(1, 0) = 3; A(1, 1) = 4;

    Vector<int> v(2);
    v[0] = 5; v[1] = 6;

    Vector<int> res = matrix_by_vector(A, v);
    EXPECT_EQ(res[0], 17); // 1*5 + 2*6
    EXPECT_EQ(res[1], 39); // 3*5 + 4*6
}