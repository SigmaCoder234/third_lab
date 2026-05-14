#pragma once
#include "../second_lab/src/DynamicArray.h"

template<class T>
class Vector : public DynamicArray<T> {
public:
    Vector() : DynamicArray<T>() {}
    Vector(int len) : DynamicArray<T>(len) {
        for (int i = 0; i < len; i++) (*this)[i] = T();
    }
    
    Vector(const DynamicArray<T>& other) : DynamicArray<T>(other) {}

    Vector<T>& operator+=(const Vector<T>& other) {
        if (this->size() != other.size()) throw std::invalid_argument("Different dimensions");
        for (int i = 0; i < this->size(); i++) (*this)[i] += other[i];
        return *this;
    }

    Vector<T>& operator-=(const Vector<T>& other) {
        if (this->size() != other.size()) throw std::invalid_argument("Different dimensions");
        for (int i = 0; i < this->size(); i++) (*this)[i] -= other[i];
        return *this;
    }

    Vector<T>& operator*=(const Vector<T>& other) {
        if (this->size() != other.size()) throw std::invalid_argument("Different dimensions");
        for (int i = 0; i < this->size(); i++) (*this)[i] *= other[i];
        return *this;
    }
};

template<class T>
Vector<T> operator+(Vector<T> lhs, const Vector<T>& rhs) {
    lhs += rhs;
    return lhs;
}

template<class T>
Vector<T> operator-(Vector<T> lhs, const Vector<T>& rhs) {
    lhs -= rhs;
    return lhs;
}

template<class T>
Vector<T> operator*(const Vector<T>& lhs, const Vector<T>& rhs) {
    Vector<T> res = lhs;
    res *= rhs;
    return res;
}