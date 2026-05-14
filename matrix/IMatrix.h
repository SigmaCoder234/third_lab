#pragma once

template<class T>
class IMatrix {
public:
    virtual ~IMatrix() = default;
    virtual T operator()(int i, int j) const = 0;
    virtual T& operator()(int i, int j) = 0;
    virtual int get_rows() const = 0;
    virtual int get_cols() const = 0;
    virtual void swap_rows(int i, int j) = 0;
};