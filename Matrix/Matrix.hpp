#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <utility>

template<class T>
class Matrix
{
public:
    Matrix();
    explicit Matrix(size_t size);
    Matrix(size_t, size_t);
    Matrix(size_t, size_t, const T&);
    Matrix(const std::initializer_list<std::initializer_list<T>>&);
    Matrix(const Matrix<T>&);
    Matrix(Matrix<T>&&) noexcept = default;

    size_t countOfRows() const noexcept;
    size_t countOfColumns() const noexcept;
    std::pair<size_t, size_t> size() const noexcept;

    void swapRows(size_t, size_t);
    void swapColumns(size_t, size_t);

    Matrix<T>& transpose();
    Matrix<T> transposeCopy() const;

    bool isEmpty() const noexcept;
    bool isSquare() const noexcept;

    Matrix<T>& operator=(const Matrix<T>& other);
    Matrix<T>& operator=(Matrix<T>&& other) noexcept;
    Matrix<T>& operator+=(const Matrix<T>& other);
    Matrix<T>& operator-=(const Matrix<T>& other);
    Matrix<T>& operator*=(const Matrix<T>& other);
    Matrix<T>& operator*=(const T& value);
    Matrix<T>& operator/=(const T& value);
    Matrix<T>& operator%=(const T& value);

    Matrix<T> operator+(const Matrix<T>& other) const;
    Matrix<T> operator-(const Matrix<T>& other) const;
    Matrix<T> operator*(const Matrix<T>& other) const;
    Matrix<T> operator*(const T& value) const;
    Matrix<T> operator/(const T& value) const;
    Matrix<T> operator%(const T& value) const;

    T* operator[](size_t);
    const T* operator[](size_t) const;
    T& at(size_t, size_t);
    const T& at(size_t, size_t) const;

    bool operator==(const Matrix<T>&) const;
    bool operator!=(const Matrix<T>&) const;

    template<class TT>
    friend Matrix<TT> operator*(const TT&, const Matrix<TT>&);

    template<class TT>
    friend std::istream& operator>>(std::istream&, const Matrix<TT>&);
    template<class TT>
    friend std::ostream& operator<<(std::ostream&, const Matrix<TT>&);

    template<class TT>
    friend void swap(Matrix<TT>&, Matrix<TT>&) noexcept;

    ~Matrix();

private:
    T** _matrix;
    size_t rowCount, columnCount;

    inline void create(size_t, size_t);
};

template<class T>
void Matrix<T>::create(size_t rowCount, size_t columnCount)
{
    if (rowCount == 0 || columnCount == 0) {
        rowCount = columnCount = 0;
        _matrix = nullptr;
        return;
    }
    _matrix = new T*[rowCount];
    for (size_t i = 0; i < rowCount; ++i) {
        _matrix[i] = new T[columnCount];
    }
}

template<class T>
Matrix<T>::Matrix() : _matrix(nullptr), rowCount(0), columnCount(0)
{
}

template<class T>
Matrix<T>::Matrix(size_t size) : rowCount(size), columnCount(size)
{
    create(size, size);
}

template<class T>
Matrix<T>::Matrix(size_t row_Count, size_t column_Count) : rowCount(row_Count), columnCount(column_Count)
{
    create(row_Count, column_Count);
}

template<class T>
Matrix<T>::Matrix(size_t row_Count, size_t column_Count, const T& value)
    : rowCount(row_Count), columnCount(column_Count)
{
    create(row_Count, column_Count);

    for (size_t i = 0; i < rowCount; ++i) {
        for (size_t j = 0; j < column_Count; ++j) {
            _matrix[i][j] = value;
        }
    }
}

template<class T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>>& il)
{
    rowCount = il.size();
    if (rowCount == 0) {
        _matrix = nullptr;
        rowCount = columnCount = 0;
    }
    else {
        columnCount = il.begin()->size();
        for (auto it = il.begin(); it != il.end(); ++it) {
            if (it->size() != columnCount) {
                throw std::invalid_argument("Incorrect initializer list");
            }
        }

        if (columnCount == 0) {
            _matrix = nullptr;
            rowCount = columnCount = 0;
        }
        else {
            _matrix = new T*[rowCount];
            for (size_t i = 0; i < rowCount; ++i) {
                _matrix[i] = new T[columnCount];

                auto it = (il.begin() + i)->begin();
                for (size_t j = 0; j < columnCount; ++j, ++it) {
                    _matrix[i][j] = *it;
                }
            }
        }
    }
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& other) : rowCount(other.rowCount), columnCount(other.columnCount)
{
    create(rowCount, columnCount);

    for (size_t i = 0; i < rowCount; ++i) {
        for (size_t j = 0; j < columnCount; ++j) {
            _matrix[i][j] = other._matrix[i][j];
        }
    }
}

template<class T>
inline size_t Matrix<T>::countOfRows() const noexcept
{
    return rowCount;
}

template<class T>
inline size_t Matrix<T>::countOfColumns() const noexcept
{
    return columnCount;
}

template<class T>
inline std::pair<size_t, size_t> Matrix<T>::size() const noexcept
{
    return std::pair<size_t, size_t>(rowCount, columnCount);
}

template<class T>
void Matrix<T>::swapRows(size_t str_i1, size_t str_i2)
{
    if (str_i1 >= rowCount || str_i2 >= rowCount) {
        return;
    }
    std::swap(_matrix[str_i1], _matrix[str_i2]);
}

template<class T>
void Matrix<T>::swapColumns(size_t col_i1, size_t col_i2)
{
    if (col_i1 >= columnCount || col_i2 >= columnCount) {
        return;
    }
    for (size_t i = 0; i < rowCount; ++i) {
        std::swap(_matrix[i][col_i1], _matrix[i][col_i2]);
    }
}

template<class T>
Matrix<T>& Matrix<T>::transpose()
{
    Matrix<T> tmp(columnCount, rowCount);

    for (size_t i = 0; i < rowCount; ++i) {
        for (size_t j = 0; j < columnCount; ++j) {
            tmp._matrix[j][i] = _matrix[i][j];
        }
    }

    return *this = std::move(tmp);
}

template<class T>
Matrix<T> Matrix<T>::transposeCopy() const
{
    Matrix<T> tmp(columnCount, rowCount);

    for (size_t i = 0; i < rowCount; ++i) {
        for (size_t j = 0; j < columnCount; ++j) {
            tmp._matrix[j][i] = _matrix[i][j];
        }
    }

    return tmp;
}

template<class T>
inline bool Matrix<T>::isEmpty() const noexcept
{
    return rowCount == 0;
}

template<class T>
inline bool Matrix<T>::isSquare() const noexcept
{
    return rowCount == columnCount;
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
{
    if (this != &other) {
        if (rowCount != other.rowCount || columnCount != other.columnCount) {
            this->~Matrix();
            rowCount = other.rowCount;
            columnCount = other.columnCount;
            create(rowCount, columnCount);
        }

        for (size_t i = 0; i < rowCount; ++i) {
            for (size_t j = 0; j < columnCount; ++j) {
                _matrix[i][j] = other._matrix[i][j];
            }
        }
    }

    return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) noexcept
{
    this->~Matrix();

    rowCount = other.rowCount;
    other.rowCount = 0;
    columnCount = other.columnCount;
    other.columnCount = 0;

    _matrix = nullptr;
    std::swap(_matrix, other._matrix);

    return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other)
{
    if (rowCount != other.rowCount || columnCount != other.columnCount) {
        throw std::invalid_argument("Incorrect operator+= argument");
    }

    for (size_t i = 0; i < rowCount; ++i) {
        for (size_t j = 0; j < columnCount; ++j) {
            _matrix[i][j] += other._matrix[i][j];
        }
    }

    return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other)
{
    if (rowCount != other.rowCount || columnCount != other.columnCount) {
        throw std::invalid_argument("Incorrect operator-= argument");
    }

    for (size_t i = 0; i < rowCount; ++i) {
        for (size_t j = 0; j < columnCount; ++j) {
            _matrix[i][j] -= other._matrix[i][j];
        }
    }

    return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other)
{
    return *this = std::move(*this * other);
}

template<class T>
Matrix<T>& Matrix<T>::operator*=(const T& value)
{
    for (size_t i = 0; i < rowCount; ++i) {
        for (size_t j = 0; j < columnCount; ++j) {
            _matrix[i][j] *= value;
        }
    }

    return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator/=(const T& value)
{
    for (size_t i = 0; i < rowCount; ++i) {
        for (size_t j = 0; j < columnCount; ++j) {
            _matrix[i][j] /= value;
        }
    }

    return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator%=(const T& value)
{
    for (size_t i = 0; i < rowCount; ++i) {
        for (size_t j = 0; j < columnCount; ++j) {
            _matrix[i][j] %= value;
        }
    }

    return *this;
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const
{
    if (rowCount != other.rowCount || columnCount != other.columnCount) {
        throw std::invalid_argument("Incorrect operator+ argument");
    }

    Matrix<T> result(*this);

    for (size_t i = 0; i < rowCount; ++i) {
        for (size_t j = 0; j < columnCount; ++j) {
            result._matrix[i][j] += other._matrix[i][j];
        }
    }

    return result;
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const
{
    if (rowCount != other.rowCount || columnCount != other.columnCount) {
        throw std::invalid_argument("Incorrect operator- argument");
    }

    Matrix<T> result(*this);

    for (size_t i = 0; i < rowCount; ++i) {
        for (size_t j = 0; j < columnCount; ++j) {
            result._matrix[i][j] -= other._matrix[i][j];
        }
    }

    return result;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const
{
    if (columnCount != other.rowCount) {
        throw std::invalid_argument("Incorrect matrix multiplication argument");
    }

    Matrix<T> result(rowCount, other.columnCount);

    for (size_t i = 0; i < rowCount; ++i) {
        for (size_t j = 0; j < result.columnCount; ++j) {
            result._matrix[i][j] = _matrix[i][0] * other._matrix[0][j];
            for (size_t k = 1; k < columnCount; ++k) {
                result._matrix[i][j] += _matrix[i][k] * other._matrix[k][j];
            }
        }
    }
    return result;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const T& value) const
{
    Matrix<T> result(*this);
    for (size_t i = 0; i < rowCount; ++i) {
        for (size_t j = 0; j < columnCount; ++j) {
            result._matrix[i][j] *= value;
        }
    }

    return result;
}

template<class T>
Matrix<T> Matrix<T>::operator/(const T& value) const
{
    Matrix<T> result(*this);
    for (size_t i = 0; i < rowCount; ++i) {
        for (size_t j = 0; j < columnCount; ++j) {
            result._matrix[i][j] /= value;
        }
    }

    return result;
}

template<class T>
Matrix<T> Matrix<T>::operator%(const T& value) const
{
    Matrix<T> result(*this);
    for (size_t i = 0; i < rowCount; ++i) {
        for (size_t j = 0; j < columnCount; ++j) {
            result._matrix[i][j] %= value;
        }
    }

    return result;
}

template<class T>
T* Matrix<T>::operator[](size_t i)
{
    return _matrix[i];
}

template<class T>
const T* Matrix<T>::operator[](size_t i) const
{
    return _matrix[i];
}

template<class T>
T& Matrix<T>::at(size_t i, size_t j)
{
    if (i >= rowCount || j >= columnCount) {
        throw std::out_of_range("incorrect indexes of matrix");
    }

    return _matrix[i][j];
}

template<class T>
const T& Matrix<T>::at(size_t i, size_t j) const
{
    if (i >= rowCount || j >= columnCount) {
        throw std::out_of_range("incorrect indexes of matrix");
    }

    return _matrix[i][j];
}

template<class T>
bool Matrix<T>::operator==(const Matrix<T>& other) const
{
    if (rowCount != other.rowCount || columnCount != other.columnCount) {
        return false;
    }

    for (size_t i = 0; i < rowCount; ++i) {
        for (size_t j = 0; j < columnCount; ++j) {
            if (_matrix[i][j] != other._matrix[i][j]) {
                return false;
            }
        }
    }

    return true;
}

template<class T>
bool Matrix<T>::operator!=(const Matrix<T>& other) const
{
    if (rowCount != other.rowCount || columnCount != other.columnCount) {
        return true;
    }

    for (size_t i = 0; i < rowCount; ++i) {
        for (size_t j = 0; j < columnCount; ++j) {
            if (_matrix[i][j] != other._matrix[i][j]) {
                return true;
            }
        }
    }

    return false;
}

template<class T>
Matrix<T> operator*(const T& value, const Matrix<T>& matrix)
{
    Matrix<T> result(matrix);

    for (size_t i = 0; i < result.rowCount; ++i) {
        for (size_t j = 0; j < result.columnCount; ++j) {
            result._matrix[i][j] = value * result._matrix[i][j];
        }
    }

    return result;
}

template<class T>
std::istream& operator>>(std::istream& ist, const Matrix<T>& matrix)
{
    for (size_t i = 0; i < matrix.rowCount; ++i) {
        for (size_t j = 0; j < matrix.columnCount; ++j) {
            ist >> matrix._matrix[i][j];
        }
    }
    return ist;
}

template<class T>
std::ostream& operator<<(std::ostream& ost, const Matrix<T>& matrix)
{
    if (matrix.rowCount == 0) {
        return ost;
    }

    for (size_t i = 0; i < matrix.rowCount - 1; ++i) {
        for (size_t j = 0; j < matrix.columnCount - 1; ++j) {
            ost << matrix._matrix[i][j] << " ";
        }
        ost << matrix._matrix[i][matrix.columnCount - 1] << std::endl;
    }
    for (size_t j = 0; j < matrix.columnCount - 1; ++j) {
        ost << matrix._matrix[matrix.rowCount - 1][j] << " ";
    }
    ost << matrix._matrix[matrix.rowCount - 1][matrix.columnCount - 1];

    return ost;
}

template<class T>
void swap(Matrix<T>& lhs, Matrix<T>& rhs) noexcept
{
    std::swap(lhs.rowCount, rhs.rowCount);
    std::swap(lhs.columnCount, rhs.columnCount);
    std::swap(lhs._matrix, rhs._matrix);
}

template<class T>
Matrix<T>::~Matrix()
{
    for (size_t i = 0; i < rowCount; ++i) {
        delete[] _matrix[i];
    }
    delete[] _matrix;
}

#endif // MATRIX_HPP