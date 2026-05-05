#pragma once
#include "../second_lab/src/DynamicArray.h"

//TODO: C-7.1.3 несколько режимов хранения. Делаем Разреженную матрицу, при заполнении 10% распаковка в обычную 

//TODO: матрица и вектор работают со всеми типами данных
//TODO: начинать операторы с += *= -=, а из них + - *

template<class T>
class Matrix {
private:
    DynamicArray<T> data;
    int dim;
public:
    Matrix() : data(0), dim(0) {}
    Matrix(int size) : data(size * size), dim(size) {}

    // operators
    Matrix<T>& operator+=(const Matrix<T>& other);
    Matrix<T>& operator-=(const Matrix<T>& other);
    Matrix<T>& operator*=(const Matrix<T>& other);

    T* operator[](int i) {
        return &data[i * dim]; 
    }
    
    // Константная версия
    const T* operator[](int i) const {
        return &data[i * dim];
    } 

    int size() const { return dim; }

    IEnumerator<T>* GetEnumerator() const { return data.GetEnumerator(); }

    void swap_rows(int i, int j) {
        if (i < 0 || i >= dim || j < 0 || j >= dim)
            throw std::out_of_range("Index out of range");
        
        for (int k = 0; k < dim; k++)
            std::swap(data[i * dim + k], data[j * dim + k]);
    }
        
};

//TODO: сделать мат операции для векторов
template<class T>
class Vector : public DynamicArray<T> {
public:
    Vector() : DynamicArray<T>() {}

    Vector(int len) : DynamicArray<T>(len) {}

    Vector<T>& operator+=(const Vector<T>& other);
    Vector<T>& operator-=(const Vector<T>& other);
    Vector<T>& operator*=(const Vector<T>& other);
};

// ==== МАТРИЦЫ ====
template<class T>
Matrix<T> operator+(Matrix<T> lhs, const Matrix<T>& rhs);

template<class T>
Matrix<T> operator-(Matrix<T> lhs, const Matrix<T>& rhs);

template<class T>
Matrix<T> operator*(Matrix<T> lhs, const Matrix<T>& rhs);

// ==== ВЕКТОРА ====
template<class T>
Vector<T> operator+(Vector<T> lhs, const Vector<T>& rhs);

template<class T>
Vector<T> operator-(Vector<T> lhs, const Vector<T>& rhs);

template<class T>
Vector<T> operator*(Vector<T> lhs, const Vector<T>& rhs);

// ==== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ====
template<class T>
Matrix<T> create_matrix(int dim);

template<class T>
Matrix<T> create_gilbert_matrix(int dim);

template<class T>
Vector<T> create_vector(int len);

template<class T>
Vector<T> matrix_by_vector(const Matrix<T>& A, const Vector<T>& b);
#include "matrix.tpp"