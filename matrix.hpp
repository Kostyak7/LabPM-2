#include <iomanip>
#include <sstream>

#include "matrix.h"


namespace linalg {

    //////////////////////OUT////////////////////////////////////
    template <class T>
    void swap(Matrix<T>& matrix1, Matrix<T>& matrix2) noexcept{
        matrix1.swap(matrix2);
    }
    template <class T>
    bool operator==(const Matrix<T>& matrix1, const Matrix<T>& matrix2) {
        if (&matrix1 == &matrix2) return true;
        if (matrix1.columns() != matrix2.columns() || matrix1.rows() != matrix2.rows()) return false;
        for (size_t i = 0; i < matrix1.rows(); ++i) {
            for (size_t j = 0; j < matrix1.columns(); ++j) {
                if (matrix1(i, j) != matrix2(i, j)) return false;
            }
        }
        return true;
    }
    template <class T1, class T2>
    bool operator==(const Matrix<T1>& matrix1, const Matrix<T2>& matrix2) {
        if (matrix1.columns() != matrix2.columns() || matrix1.rows() != matrix2.rows()) return false;
        for (size_t i = 0; i < matrix1.rows(); ++i) {
            for (size_t j = 0; j < matrix1.columns(); ++j) {
                if (matrix1(i, j) != matrix2(i, j)) return false;
            }
        }
        return true;
    }
    template <class T1, class T2>
    inline bool operator!=(const Matrix<T1>& matrix1, const Matrix<T2>& matrix2) {
        return !(matrix1 == matrix2);
    }

    template <class T, class T2>
    auto operator*(const T2& value, const Matrix<T>& matrix)->Matrix<decltype(T()*T2())> {
        return Matrix<decltype(T()*T2())>(matrix) *= value;
    }
    template <class T, class T2>
    auto operator*(const Matrix<T>& matrix, const T2& value)->Matrix<decltype(T()*T2())> {
        return Matrix<decltype(T()*T2())>(matrix) *= value;
    }
    template <class T, class T2>
    auto operator+(const Matrix<T>& matrix1, const Matrix<T2>& matrix2)->Matrix<decltype(T() + T2())> {
        return Matrix<decltype(T() + T2())>(matrix1) += matrix2;
    }
    template <class T>
    Matrix<T> operator-(const Matrix<T>& matrix) {
        return Matrix<T>((-1) * matrix);
    }
    template <class T, class T2>
    auto operator-(const Matrix<T>& matrix1, const Matrix<T2>& matrix2)->Matrix<decltype(T() - T2())> {
        return Matrix<decltype(T() + T2())>(matrix1) -= matrix2;
    }
    template <class T, class T2>
    auto operator*(const Matrix<T>& matrix1, const Matrix<T2>& matrix2)->Matrix<decltype(T()*T2())> {
        return Matrix<decltype(T() + T2())>(matrix1) *= matrix2;
    }

    namespace {
        template<class T>
        void put_widths(const Matrix<T> &matrix, size_t &w1, size_t& gw) {
            w1 = gw = 0;
            for (size_t i = 0; i < matrix.rows(); ++i) {
                std::stringstream ss;
                ss << matrix(i, 0);
                w1 = (ss.str().size() > w1)? ss.str().size(): w1;
                for (size_t j = 1; j < matrix.rows(); ++j) {
                    ss.str("");
                    ss << matrix(i, j);
                    gw = (ss.str().size() > gw)? ss.str().size(): gw;
                }
            }
        }
    } // namespace

    template <class T> std::ostream& operator<< (std::ostream& out, const Matrix<T>& matrix) {
        if (matrix.empty()) {
            out << "|Empty|";
        } else {
            size_t w1 = 0, gw = 0;
            put_widths(matrix, w1, gw);
            for (size_t i = 0; i < matrix.rows(); ++i) {
                out << '|' << std::setw(w1) << matrix(i, 0);
                for (size_t j = 1; j < matrix.columns(); ++j) {
                    out << ' ' << std::setw(gw) << matrix(i, j);
                }
                out << "|\n";
            }
        }
        return out;
    }

    template <class T>
    Matrix<T> trans(const Matrix<T>& matrix) {
        Matrix<T> result(matrix.columns(), matrix.rows());
        for (size_t i = 0; i < matrix.rows(); ++i) {
            for (size_t j = 0; j < matrix.columns(); ++j) {
                result(j, i) = matrix(i, j);
            }
        }
        return result;
    }
    template <class T>
    T det(const Matrix<T>& matrix) {
        if (matrix.empty()) throw EmptyException();
        if (matrix.columns() != matrix.rows()) throw InvalidSizesException();
        if (matrix.rows() == 1) return matrix(0, 0);
        T result = T();
        for (size_t row_0 = 0; row_0 < matrix.columns(); ++row_0) {
            if (matrix(0, row_0) == 0) continue;
            Matrix<T> tmp(matrix.rows() - 1, matrix.columns() - 1);
            for (size_t i = 0; i < matrix.rows() - 1; ++i) {
                for (size_t j = 0; j < matrix.columns() - 1; ++j) {
                    if (j < row_0) tmp(i, j) = matrix(i + 1, j);
                    else tmp(i, j) = matrix(i + 1, j + 1);
                }
            }
            result += det(tmp) * ((row_0 % 2) ? -1 : 1) * matrix(0, row_0);
        }
        return result;
    }

    //////////////////////Vector/////////////////////////////////

    template <class T>
    Matrix<T>::Vector::Vector(T* const _ptr_,  const size_t& _size_) noexcept
    : _ptr(_ptr_), _size(_size_) {}

    template <class T>
    size_t Matrix<T>::Vector::size() const noexcept{
        return _size;
    }

    template <class T>
    const T& Matrix<T>::Vector::operator[](const size_t& _index_) const noexcept{
        return _ptr[_index_];
    }
    template <class T>
    T& Matrix<T>::Vector::operator[](const size_t& _index_) noexcept{
        return _ptr[_index_];
    }
    template <class T>
    const T& Matrix<T>::Vector::at(const size_t &_index_) const {
        if (_index_ > _size) throw OutOfRange();
        return _ptr[_index_];
    }
    template <class T>
    T &Matrix<T>::Vector::at(const size_t &_index_) {
        if (_index_ > _size) throw OutOfRange();
        return _ptr[_index_];
    }

    //////////////////////Matrix/////////////////////////////////
    template <class T>
    Matrix<T>::Matrix(const size_t& _rows_, const size_t& _columns_) {
        if (_rows_ == 0 || _columns_ == 0) return;
        T *tmp_ptr = reinterpret_cast<T *>(operator new(sizeof(T) * _rows_ * _columns_));
        T *cur_ptr = tmp_ptr;
        try {
            for (;cur_ptr != tmp_ptr + _rows_ * _columns_; ++cur_ptr) {
                new(cur_ptr) T();
            }
        } catch (...) {
            for (; cur_ptr >= tmp_ptr; --cur_ptr) {
                cur_ptr->~T();
            }
            delete reinterpret_cast<void *>(tmp_ptr);
            throw;
        }
        m_ptr = tmp_ptr;
        m_capacity = _rows_ * _columns_;
        m_rows = _rows_;
        m_columns = _columns_;
    }
    template <class T> template<class T2>
    Matrix<T>::Matrix(const size_t& _rows_, const size_t& _columns_, const T2& _default_value_) {
        if (_rows_ == 0 || _columns_ == 0) return;
        T *tmp_ptr = reinterpret_cast<T *>(operator new(sizeof(T) * _rows_ * _columns_));
        T *cur_ptr = tmp_ptr;
        try {
            for (;cur_ptr != tmp_ptr + _rows_ * _columns_; ++cur_ptr) {
                new(cur_ptr) T(_default_value_);
            }
        } catch (...) {
            for (; cur_ptr >= tmp_ptr; --cur_ptr) {
                cur_ptr->~T();
            }
            delete reinterpret_cast<void *>(tmp_ptr);
            throw;
        }
        m_ptr = tmp_ptr;
        m_capacity = _rows_ * _columns_;
        m_rows = _rows_;
        m_columns = _columns_;
    }
    template <class T>
    Matrix<T>::Matrix(const Matrix<T>& matrix) {
        copy_constructor_instructions(matrix);
    }
    template <class T> template <class T2>
    Matrix<T>::Matrix(const Matrix<T2>& matrix) {
        copy_constructor_instructions(matrix);
    }
    template <class T>
    Matrix<T>::Matrix(Matrix<T>&& matrix) noexcept {
        swap(matrix);
    }
    template <class T> template <class T2>
    Matrix<T>::Matrix(std::initializer_list<T2> _list_) {
        if (_list_.size() == 0) return;
        T *tmp_ptr = reinterpret_cast<T *>(operator new(sizeof(T) * _list_.size()));
        T *cur_ptr = tmp_ptr;
        try {
            using lst_it_t2 = typename std::initializer_list<T2>::iterator;
            for (lst_it_t2 it = _list_.begin(); it != _list_.end(); ++it, ++cur_ptr) {
                new(cur_ptr) T(*it);
            }
        } catch (...) {
            for (; cur_ptr >= tmp_ptr; --cur_ptr) {
                cur_ptr->~T();
            }
            delete reinterpret_cast<void *>(tmp_ptr);
            throw;
        }
        m_ptr = tmp_ptr;
        m_capacity = _list_.size();
        m_rows = _list_.size();
        m_columns = 1;
    }
    template <class T> template <class T2>
    Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T2>> _list_) {
        if (_list_.size() == 0) return;
        size_t max_size_columns = 0;
        for (auto lst: _list_){
            if (max_size_columns < lst.size()) max_size_columns = lst.size();
        }
        T *tmp_ptr = reinterpret_cast<T *>(operator new(sizeof(T) * _list_.size() * max_size_columns));
        long i = 0, j;
        try {
            for (auto lst: _list_) {
                j = 0;
                for (auto el: lst) {
                    new(tmp_ptr + i * max_size_columns + j) T(el);
                    ++j;
                }
                for (; j < max_size_columns; ++j) {
                    new(tmp_ptr + i * max_size_columns + j) T();
                }
                ++i;
            }
        } catch (...) {
            i = i * max_size_columns + j;
            for (; i >= 0; --i) {
                (tmp_ptr + i)->~T();
            }
            delete reinterpret_cast<void *>(tmp_ptr);
            throw;
        }
        m_ptr = tmp_ptr;
        m_capacity = _list_.size() * max_size_columns;
        m_rows = _list_.size();
        m_columns = max_size_columns;
    }
    template <class T>
    Matrix<T>::~Matrix() {
        if (!empty()) {
            for (T *cur_ptr = m_ptr + m_columns * m_rows - 1; cur_ptr >= m_ptr; --cur_ptr) {
                cur_ptr->~T();
            }
        }
        delete reinterpret_cast<void*>(m_ptr);
    }

    template <class T>
    size_t Matrix<T>::rows() const noexcept{
        return m_rows;
    }
    template <class T>
    size_t Matrix<T>::columns() const noexcept{
        return m_columns;
    }
    template <class T>
    size_t Matrix<T>::capacity() const noexcept{
        return m_capacity;
    }
    template <class T>
    bool Matrix<T>::empty() const noexcept{
        return m_columns == 0 || m_rows == 0;
    }

    template <class T>
    const T& Matrix<T>::at(const size_t &row, const size_t &column) const {
        if (row * m_columns + column > m_columns * m_rows) throw OutOfRange();
        return (*this)(row, column);
    }
    template <class T>
    T &Matrix<T>::at(const size_t &row, const size_t &column) {
        if (row * m_columns + column > m_columns * m_rows) throw OutOfRange();
        return (*this)(row, column);
    }
    template <class T>
    const T& Matrix<T>::operator()(const size_t& row, const size_t& column) const noexcept{
        return m_ptr[row * m_columns + column];
    }
    template <class T>
    T& Matrix<T>::operator()(const size_t& row, const size_t& column) noexcept{
        return m_ptr[row * m_columns + column];
    }
    template <class T>
    const typename Matrix<T>::Vector Matrix<T>::operator[](const size_t &row) const noexcept{
        return Vector(m_ptr + m_columns * row, m_columns);
    }
    template <class T>
    typename Matrix<T>::Vector Matrix<T>::operator[](const size_t &row) noexcept{
        return Vector(m_ptr + m_columns * row, m_columns);
    }

    template <class T>
    Matrix<T>& Matrix<T>::operator=(const Matrix& matrix) {
        if (this == &matrix) return *this;
        return operator=<T>(matrix);
    }
    template <class T> template <class T2>
    Matrix<T>& Matrix<T>::operator=(const Matrix<T2>& matrix) {
        if (matrix.columns() * matrix.rows() > m_capacity) return *this = Matrix(matrix);
        for (size_t i =0; i < matrix.rows(); ++i) {
            for (size_t j =0; j < matrix.columns(); ++j) {
                (*this)(i, j) = T(matrix(i, j));
            }
        }
        m_rows = matrix.rows();
        m_columns = matrix.columns();
        return *this;
    }
    template <class T>
    Matrix<T>& Matrix<T>::operator=(Matrix&& matrix) noexcept{
        if (this == &matrix) return *this;
        swap(matrix);
        return *this;
    }

    template <class T> template <class T2>
    Matrix<T>& Matrix<T>::operator+=(const Matrix<T2>& matrix) {
        if (matrix.empty() || empty()) throw EmptyException();
        if (matrix.columns() != m_columns || matrix.rows() != m_rows) throw InvalidSizesException();
        for (size_t i = 0; i < m_rows; ++i) {
            for (size_t j = 0; j < m_columns; ++j) {
                (*this)(i, j) += matrix(i, j);
            }
        }
        return *this;
    }
    template <class T> template <class T2>
    Matrix<T>& Matrix<T>::operator-=(const Matrix<T2>& matrix) {
        return *this += -matrix;
    }
    template <class T> template <class T2>
    Matrix<T>& Matrix<T>::operator*=(const Matrix<T2>& matrix) {
        if (matrix.empty() || empty()) throw EmptyException();
        if (m_columns != matrix.rows()) throw InvalidSizesException();
        Matrix tmp_matrix(m_rows, matrix.columns());
        for (size_t i = 0; i < m_rows; ++i) {
            for (size_t j = 0; j < matrix.columns(); ++j) {
                for (size_t num = 0; num< m_columns; ++num) {
                    tmp_matrix(i, j) += (*this)(i, num) * matrix(num, j);
                }
            }
        }
        return *this = std::move(tmp_matrix);
    }
    template <class T> template <class T2>
    Matrix<T>& Matrix<T>::operator*=(const T2& value) {
        if (empty()) throw EmptyException();
        for (size_t i = 0; i <m_rows; ++i) {
            for (size_t j = 0; j < m_columns; ++j) {
                (*this)(i, j) *= value;
            }
        }
        return *this;
    }

    template <class T>
    void Matrix<T>::swap(Matrix<T>& matrix) noexcept{
        std::swap(m_ptr, matrix.m_ptr);
        std::swap(m_rows, matrix.m_rows);
        std::swap(m_columns, matrix.m_columns);
        std::swap(m_capacity, matrix.m_capacity);
    }
    template <class T>
    void Matrix<T>::reshape(const size_t& _rows_, const size_t& _columns_) {
        if (_rows_ == m_rows && _columns_ == m_columns) return;
        if (_rows_*_columns_ != m_rows * m_columns) throw InvalidSizesException();
        m_rows = _rows_;
        m_columns = _columns_;
    }
    template <class T>
    void Matrix<T>::reserve(const size_t& _capacity_) {
        if (m_capacity >= _capacity_) return;
        T *tmp_ptr = reinterpret_cast<T *>(operator new(sizeof(T) * _capacity_));
        T *cur_ptr = tmp_ptr;
        try {
            while(cur_ptr != tmp_ptr + _capacity_) {
                new(cur_ptr) T();
                ++cur_ptr;
            }
        } catch (...) {
            for (; cur_ptr >= tmp_ptr; --cur_ptr) {
                cur_ptr->~T();
            }
            delete reinterpret_cast<void *>(tmp_ptr);
            throw;
        }
        for (size_t i = 0; i < m_rows; ++i) {
            for (size_t j = 0; j < m_columns; ++j) {
                tmp_ptr[i * m_columns + j] = m_ptr[i * m_columns + j];
            }
        }
        if (!empty()) {
            for (T *del_ptr = m_ptr + m_columns * m_rows - 1; del_ptr >= m_ptr; --del_ptr) {
                cur_ptr->~T();
            }
        }
        m_ptr = tmp_ptr;
        m_capacity = _capacity_;
    }
    template <class T>
    void Matrix<T>::shrink_to_fit() {
        if (m_capacity == m_columns * m_rows) return;
        *this = Matrix<T>(*this);
    }
    template <class T>
    void Matrix<T>::clear() noexcept{
        if (!empty()) {
            for (T *cur_ptr = m_ptr + m_columns * m_rows - 1; cur_ptr >= m_ptr; --cur_ptr) {
                cur_ptr->~T();
            }
        }
        m_columns = m_rows = 0;
    }

    template <class T> template <class T2>
    void Matrix<T>::copy_constructor_instructions(const Matrix<T2>& matrix) {
        if (matrix.empty()) return;
        T *tmp_ptr = reinterpret_cast<T*>(operator new(sizeof(T) * matrix.rows() * matrix.columns()));
        size_t i, j;
        try {
            for (i = 0; i < matrix.rows(); ++i) {
                for (j = 0; j < matrix.columns(); ++j) {
                    new(tmp_ptr + i * matrix.columns() + j) T(matrix(i, j));
                }
            }
        } catch (...) {
            for (T* cur_ptr = tmp_ptr + i * matrix.columns() + j; cur_ptr >= tmp_ptr; --cur_ptr) {
                cur_ptr->~T();
            }
            delete reinterpret_cast<void *>(tmp_ptr);
            throw;
        }
        m_ptr = tmp_ptr;
        m_capacity = matrix.rows() * matrix.columns();
        m_rows = matrix.rows();
        m_columns = matrix.columns();
    }
} // namespace linalg
