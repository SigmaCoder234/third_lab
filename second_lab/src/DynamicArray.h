#pragma once
#include <stdexcept>
#include "IEnumerable.h"
#include "IEnumerator.h"

template <class T>
class DynamicArray {
private:
    T* data;
    int m_size;
    int m_capacity;
public:

    // constructors
    DynamicArray(const T* items, int count);
    DynamicArray(int size);
    DynamicArray(const DynamicArray& dynamic_array);

    // destructor
    ~DynamicArray();

    // decomposers
    const T& Get(int index) const;
    int size() const;

    // operations
    void Set(int index, const T& value);
    void ReSize(int newSize);

    DynamicArray() : data(nullptr), m_size(0), m_capacity(0) {}

    // operators
    // Возвращает ссылку, позволяет изменять элемент
    T& operator[](int index) {
        if (index < 0 || index >= m_size) 
            throw std::out_of_range("Index out of range");
        return data[index];
    }

    // Константная версия для чтения из константных массивов
    const T& operator[](int index) const {
        if (index < 0 || index >= m_size) 
            throw std::out_of_range("Index out of range");
        return data[index];
    }

    DynamicArray& operator=(const DynamicArray& other) {
    if (this != &other) { // защита от a = a
        delete[] data;    // удаляем старое
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        data = new T[m_capacity]; // выделяем новое
        for (int i = 0; i < m_size; i++)
            data[i] = other.data[i];
        }
        return *this;
    }

    // Iterator
    class ArrayEnumerator : public IEnumerator<T> {
    private:
        const DynamicArray<T>* array; // Указатель на массив, который мы перебираем // Лучше ссылку
        int current_index;            // Текущая позиция "закладки"

    public:
        // Конструктор итератора
        ArrayEnumerator(const DynamicArray<T>* arr) {
            this->array = arr;
            this->current_index = -1; // Начинаем до первого элемента
        }

        bool MoveNext() override {
            current_index++;
            return current_index < array -> size();
        }

        const T& Current() const override {
            return array -> Get(current_index);
        }

        void Reset() override {
            this -> current_index = -1;
        }
    };

    IEnumerator<T>* GetEnumerator() const { return new ArrayEnumerator(this); }
};

template <class T>
DynamicArray<T>::DynamicArray(const T* items, int count) {
    if (count < 0) {
        throw std::invalid_argument("Size cannot be negative");
    }

    this -> m_size = count;

    if (m_size > 0) {
        m_capacity = m_size;
    }

    else m_capacity = 1;

    data = new T[m_capacity];
    for (int i = 0; i < m_size; i++) {
        data[i] = items[i];
    }
}

template<class T>
DynamicArray<T>::DynamicArray(int m_size) {
    if (m_size < 0) {
        throw std::invalid_argument("Size cannot be negative");
    }
    this->m_size = m_size;

    if (m_size > 0) {
        m_capacity = m_size;
    }

    else m_capacity = 1;

    data = new T[m_capacity]{};
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray& dynamic_array) {
    this->m_size = dynamic_array.m_size;
    this->m_capacity = dynamic_array.m_capacity;

    data = new T[m_capacity];
    for (int i = 0; i < m_size; i++)
        data[i] = dynamic_array.data[i];
}

template<class T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template<class T>
const T& DynamicArray<T>::Get(int index) const {
    if (index < 0 || index >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template<class T>
int DynamicArray<T>::size() const {
    return m_size;
}

template<class T>
void DynamicArray<T>::Set(int index, const T& value) {
    if (index < 0 || index >= m_size) {
        throw std::out_of_range("Index out of range");
    }

    data[index] = value;
}

template<class T>
void DynamicArray<T>::ReSize(int newSize) {
    if (newSize < 0)
        throw std::invalid_argument("Size cannot be negative");

    if (newSize <= m_capacity) {
        m_size = newSize;
        return;
    }

    int newCapacity = m_capacity;

    while (newCapacity < newSize)
        newCapacity *= 2;

    T* newData = new T[newCapacity];

    for (int i = 0; i < m_size; i++)
        newData[i] = data[i];

    delete[] data;
    data = newData;
    m_size = newSize;
}