#include <random>

static std::mt19937 generator(1337);

template<class T>
Matrix<T> create_matrix(int dim) {
    Matrix<T> A(dim);
    std::uniform_real_distribution<double> dis(-1.0, 1.0);
    for (int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j++) {
            A[i][j] = dis(generator);
        }
    }

    return A;
}

template<class T>
Matrix<T> create_gilbert_matrix(int dim) {
    Matrix<T> gilbert(dim);

    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            gilbert[i][j] = 1.0 / (i + j + 1);

    return gilbert;
}

template<class T>
Vector<T> create_vector(int len) {
    Vector<T> b(len);
    std::uniform_real_distribution<double> dis(-1.0, 1.0);

    for (int i = 0; i < len; i++) {
        b[i] = dis(generator);
    }

    return b;
}

template<class T>
Vector<T> matrix_by_vector(const Matrix<T>& A, const Vector<T>& b) {
    int dim = A.size();
    Vector<T> result(dim);

    for (int i = 0; i < dim; i++) {
        IEnumerator<T>* it = b.GetEnumerator();
        int j = 0;
        while (it->MoveNext()) {
            result[i] = result[i] + (A[i][j] * it->Current());
            j++;
        }
        delete it;
    }

    return result;
}

// ==== ПЕРЕГРУЗКА ОПЕРАТОРОВ ДЛЯ МАТРИЦ ====

// ===== СЛОЖЕНИЕ =====

template<class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other) {
    if (this->size() != other.size()) {
        throw std::invalid_argument("Матрицы должны быть одного размера для сложения!");
    }
    
    IEnumerator<T>* it = other.GetEnumerator();
    int k = 0; // Линейный индекс (от 0 до dim*dim - 1)
    while (it->MoveNext()) {
        this->data[k] += it->Current(); // Обращаемся напрямую к внутреннему массиву матрицы
        k++;
    }
    
    delete it;
    // Возвращаем ссылку на саму себя (чтобы можно было делать a += b += c)
    return *this; 
}

template<class T>
Matrix<T> operator+(Matrix<T> lhs, const Matrix<T>& rhs) {
    lhs += rhs; // Прибавляем к копии правую матрицу
    return lhs; // Возвращаем результат
}

// ===== ВЫЧИТАНИЕ =====

template<class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other) {
    if (this->size() != other.size()) {
        throw std::invalid_argument("Матрицы должны быть одного размера для вычитания!");
    }
    
    IEnumerator<T>* it = other.GetEnumerator();
    int k = 0; // Линейный индекс (от 0 до dim*dim - 1)
    while (it->MoveNext()) {
        this->data[k] -= it->Current(); // Вычитаем прочитанное значение
        k++;
    }
    
    delete it;
    
    // Возвращаем ссылку на саму себя (чтобы можно было делать a -= b -= c)
    return *this; 
}

template<class T>
Matrix<T> operator-(Matrix<T> lhs, const Matrix<T>& rhs) {
    lhs -= rhs; // Вычитаем из копии правую матрицу
    return lhs; // Возвращаем результат
}

// ===== УМНОЖЕНИЕ =====

template<class T>
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    if (lhs.size() != rhs.size()) throw std::invalid_argument("Разные размеры");
    int dim = lhs.size();
    Matrix<T> result(dim);
    
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            T sum = 0;
            for (int k = 0; k < dim; k++) {
                sum += lhs[i][k] * rhs[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}

template<class T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other) {
    *this = (*this) * other; // Умножаем и присваиваем результат себе
    return *this;
}

// ==== ПЕРЕГРУЗКА ОПЕРАТОРОВ ДЛЯ ВЕКТОРОВ ====

// ===== СЛОЖЕНИЕ =====

template<class T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& other) {
    if (this->size() != other.size()) {
        throw std::invalid_argument("Матрицы должны быть одного размера для сложения!");
    }
    
    IEnumerator<T>* it = other.GetEnumerator();
    int k = 0; // Линейный индекс (от 0 до dim-1)
    while (it->MoveNext()) {
        (*this)[k] += it->Current(); // Обращаемся напрямую к внутреннему массиву матрицы
        k++;
    }
    
    delete it;
    // Возвращаем ссылку на саму себя (чтобы можно было делать a += b += c)
    return *this; 
}

template<class T>
Vector<T> operator+(Vector<T> lhs, const Vector<T>& rhs) {
    lhs += rhs; // Прибавляем к копии правую матрицу
    return lhs; // Возвращаем результат
}

// ===== ВЫЧИТАНИЕ =====

template<class T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& other) {
    if (this->size() != other.size()) {
        throw std::invalid_argument("Матрицы должны быть одного размера для вычитания!");
    }
    
    IEnumerator<T>* it = other.GetEnumerator();
    int k = 0; // Линейный индекс (от 0 до dim-1)
    while (it->MoveNext()) {
        (*this)[k] -= it->Current(); // Вычитаем прочитанное значение
        k++;
    }
    
    delete it;
    
    // Возвращаем ссылку на саму себя (чтобы можно было делать a -= b -= c)
    return *this; 
}

template<class T>
Vector<T> operator-(Vector<T> lhs, const Vector<T>& rhs) {
    lhs -= rhs; // Вычитаем из копии правую матрицу
    return lhs; // Возвращаем результат
}

// ===== УМНОЖЕНИЕ =====

template<class T>
Vector<T> operator*(const Vector<T>& lhs, const Vector<T>& rhs) {
    if (lhs.size() != rhs.size()) throw std::invalid_argument("Разные размеры");
    int len = lhs.size();
    Vector<T> result(len);
    
    for (int i = 0; i < len; i++) {
        result[i] = lhs[i] * rhs[i];
    }
    return result;
}

template<class T>
Vector<T>& Vector<T>::operator*=(const Vector<T>& other) {
    *this = (*this) * other; // Умножаем и присваиваем результат себе
    return *this;
}