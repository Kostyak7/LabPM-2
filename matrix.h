#pragma once

#include <cstddef>
#include <ostream>
#include <initializer_list>
#include <exception>

#define DEFAULT_TYPE double

namespace linalg {

    template<class T = DEFAULT_TYPE>
    class Matrix {
    public:
        class Vector {
        public:
            Vector() = delete;
            Vector(T *const _ptr_, const size_t &_size_) noexcept;

            size_t size() const noexcept;
            T &operator[](const size_t &_index_) noexcept;
            const T& operator[](const size_t &_index_) const noexcept;
            const T& at(const size_t &_index_) const;
            T &at(const size_t &_index_);
        private:
            T *_ptr = nullptr;
            size_t _size = 0;
        };

        Matrix() noexcept = default;
        explicit Matrix(const size_t &_rows_, const size_t &_columns_ = 1);
        template <class T2> Matrix(const size_t &_rows_, const size_t &_columns_, const T2 &_default_value_);
        Matrix(const Matrix &matrix);
        template <class T2> Matrix(const Matrix<T2> &matrix);
        Matrix(Matrix &&matrix) noexcept;
        template <class T2> Matrix(std::initializer_list<T2> _list_);
        template <class T2> Matrix(std::initializer_list<std::initializer_list<T2>> _list_);
        ~Matrix();

        size_t rows() const noexcept;
        size_t columns() const noexcept;
        size_t capacity() const noexcept;
        bool empty() const noexcept;

        const T& at(const size_t &row, const size_t &column) const;
        T &at(const size_t &row, const size_t &column);
        const T& operator()(const size_t &row, const size_t &column) const noexcept;
        T &operator()(const size_t &row, const size_t &column) noexcept;
        const Vector operator[](const size_t &row) const noexcept;
        Vector operator[](const size_t &row) noexcept;

        Matrix& operator=(const Matrix& matrix);
        template <class T2> Matrix& operator=(const Matrix<T2>& matrix);
        Matrix& operator=(Matrix&& matrix) noexcept;

        template <class T2> Matrix& operator+=(const Matrix<T2>& matrix);
        template <class T2> Matrix& operator-=(const Matrix<T2>& matrix);
        template <class T2> Matrix& operator*=(const Matrix<T2>& matrix);
        template <class T2> Matrix& operator*=(const T2& value);

        void swap(Matrix &matrix) noexcept;
        void reshape(const size_t &_rows_, const size_t &_columns_);
        void reserve(const size_t &_capacity_);
        void shrink_to_fit();
        void clear() noexcept;
    private:
        template <class T2> void copy_constructor_instructions(const Matrix<T2>& matrix);
    private:
        T *m_ptr = nullptr;
        size_t m_columns = 0, m_rows = 0;
        size_t m_capacity = 0;
    };

    struct MyException : public std::runtime_error {
        explicit MyException(const char* message) : runtime_error(message) {}
    };
    struct OutOfRange : public MyException {
        OutOfRange() : MyException("Matrix out of range") {}
    };
    struct EmptyException : public MyException {
        EmptyException() : MyException("Invalid operation on empty matrix") {}
    };
    struct InvalidSizesException : public MyException {
        InvalidSizesException() : MyException("Matrix(cex) has(ve) unsuitable size(s)") {}
    };


    template <class T> void swap(Matrix<T>& matrix1, Matrix<T>& matrix2) noexcept;

    template <class T> bool operator==(const Matrix<T>& matrix1, const Matrix<T>& matrix2);
    template <class T1, class T2> bool operator==(const Matrix<T1>& matrix1, const Matrix<T2>& matrix2);
    template <class T1, class T2> inline bool operator!=(const Matrix<T1>& matrix1, const Matrix<T2>& matrix2);

    template <class T, class T2> auto operator*(const T2& value, const Matrix<T>& matrix)->Matrix<decltype(T()*T2())>;
    template <class T, class T2> auto operator*(const Matrix<T>& matrix, const T2& value)->Matrix<decltype(T()*T2())>;
    template <class T, class T2> auto operator+(const Matrix<T>& matrix1, const Matrix<T2>& matrix2)->Matrix<decltype(T() + T2())>;
    template <class T> Matrix<T> operator-(const Matrix<T>& matrix);
    template <class T, class T2> auto operator-(const Matrix<T>& matrix1, const Matrix<T2>& matrix2)->Matrix<decltype(T() - T2())>;
    template <class T, class T2> auto operator*(const Matrix<T>& matrix1, const Matrix<T2>& matrix2)->Matrix<decltype(T()*T2())>;

    template <class T> Matrix<T> trans(const Matrix<T>& matrix);
    template <class T> T det(const Matrix<T>& matrix);

} //namespace linalg
