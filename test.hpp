#pragma once

#include "base_test.h"
#include "matrix.hpp"


namespace linalg::tests {

    struct Test : public baseTest::BaseTest {
        void run_tests(bool showMore = false);

        void empty_test();
        void columns_rows_test();
        void constructors_test();
        void reshape_test();
        void reserve_test();
        void shrink_to_fit_test();
        void clear_test();
        void operator_bracket_test();
        void assignment_operator_test();
        void add_sub_operators_test();
        void multiply_test();
        void trans_det_test();
        void print_test();

    private:
        template<class T> static size_t get_max_size_value(const Matrix<T> &matrix);
        template <class T1, class T2> void to_line_2_matrix(const std::string& name_1, const Matrix<T1>& matrix1,
                                                            const std::string& name_2, const Matrix<T2>& matrix2);
        template<class T> static
        std::string row_to_string(const Matrix<T> &matrix, const size_t &_row_num_, const size_t &max_size_value);
        template<class T> static
        std::string row_to_string_2(const Matrix<T> &matrix, const size_t &_row_num_, const size_t &max_size_value);
        template<class T> static
        std::string row_to_string_3(const Matrix<T> &matrix, const size_t &_row_num_, const size_t &max_size_value);
        template<class T> static
        std::string row_to_string_4(const Matrix<T> &matrix, const size_t &_row_num_, const size_t &max_size_value);
    };

    template<class T>
    size_t Test::get_max_size_value(const Matrix<T> &matrix) {
        size_t max_size = 0;
        for (size_t i = 0; i < matrix.rows(); ++i) {
            for (size_t j = 0; j < matrix.columns(); ++j) {
                std::stringstream ss;
                ss << matrix(i, j);
                if (ss.str().size() > max_size) {
                    max_size = ss.str().size();
                }
            }
        }
        return max_size;
    }

    template <class T1, class T2>
    void Test::to_line_2_matrix(const std::string& name_1, const Matrix<T1>& matrix1,
                                const std::string& name_2, const Matrix<T2>& matrix2) {
        to_lhalf(name_1);
        to_rhalf(name_2);
        size_t size_1 = get_max_size_value(matrix1), size_2 = get_max_size_value(matrix2);
        for (int i = 0; i < std::max(matrix1.rows(), matrix2.rows()); ++i) {
            to_lhalf(row_to_string(matrix1, i, size_1));
            to_rhalf(row_to_string(matrix2, i, size_2));
        }
        to_line(" ");
    }

    template<class T>
    std::string Test::row_to_string(const Matrix<T> &matrix, const size_t &_row_num_, const size_t &max_size_value) {
        std::stringstream ss;
        for (size_t i = 0; i < matrix.columns(); ++i) {
            std::stringstream vss;
            if (_row_num_ < matrix.rows()) vss << matrix(_row_num_, i);
            else vss << ' ';
            for (size_t j = 0; j < max_size_value - vss.str().size(); ++j) {
                ss << ' ';
            }
            if (_row_num_ < matrix.rows()) ss << matrix(_row_num_, i);
            else ss << ' ';
            if (i != matrix.columns() - 1) ss << ' ';
        }
        return ss.str();
    }

    template<class T>
    std::string Test::row_to_string_2(const Matrix<T> &matrix, const size_t &_row_num_, const size_t &max_size_value) {
        std::stringstream ss;
        for (size_t i = 0; i < matrix.columns(); ++i) {
            std::stringstream vss;
            if (_row_num_ < matrix.rows()) vss << matrix[_row_num_][i];
            else vss << ' ';
            for (size_t j = 0; j < max_size_value - vss.str().size(); ++j) {
                ss << ' ';
            }
            if (_row_num_ < matrix.rows()) ss << matrix[_row_num_][i];
            else ss << ' ';
            if (i != matrix.columns() - 1) ss << ' ';
        }
        return ss.str();
    }

    template<class T>
    std::string Test::row_to_string_3(const Matrix<T> &matrix, const size_t &_row_num_, const size_t &max_size_value) {
        std::stringstream ss;
        for (size_t i = 0; i < matrix.columns(); ++i) {
            std::stringstream vss;
            if (_row_num_ < matrix.rows()) vss << matrix.at(_row_num_,i);
            else vss << ' ';
            for (size_t j = 0; j < max_size_value - vss.str().size(); ++j) {
                ss << ' ';
            }
            if (_row_num_ < matrix.rows()) ss << matrix.at(_row_num_,i);
            else ss << ' ';
            if (i != matrix.columns() - 1) ss << ' ';
        }
        return ss.str();
    }

    template<class T>
    std::string Test::row_to_string_4(const Matrix<T> &matrix, const size_t &_row_num_, const size_t &max_size_value) {
        std::stringstream ss;
        for (size_t i = 0; i < matrix.columns(); ++i) {
            std::stringstream vss;
            if (_row_num_ < matrix.rows()) vss << matrix[_row_num_].at(i);
            else vss << ' ';
            for (size_t j = 0; j < max_size_value - vss.str().size(); ++j) {
                ss << ' ';
            }
            if (_row_num_ < matrix.rows()) ss << matrix[_row_num_].at(i);
            else ss << ' ';
            if (i != matrix.columns() - 1) ss << ' ';
        }
        return ss.str();
    }


} // namespace linalg::tests