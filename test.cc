#include <iostream>

#include "test.hpp"


namespace linalg::tests {
    ///////////////////////////TEST////////////////////////////////

    void Test::run_tests(bool showMore) {
        START_MYTESTS(
                MYTEST("Test empty()", empty_test(), showMore, false)
                MYTEST("Test columns()/rows()", columns_rows_test(), showMore, false)
                MYTEST("Test constructors", constructors_test(), showMore, false)
                MYTEST("Test reshape()", reshape_test(), showMore, false)
                MYTEST("Test reserve()", reserve_test(), showMore, false)
                MYTEST("Test shrink_to_fit()", shrink_to_fit_test(), showMore, false)
                MYTEST("Test clear()", clear_test(), showMore, false)
                MYTEST("Test operators [],()", operator_bracket_test(), showMore, false)
                MYTEST("Test operator =", assignment_operator_test(), showMore, false)
                MYTEST("Test operators +,-,+=,-=", add_sub_operators_test(), showMore, false)
                MYTEST("Test operator *", multiply_test(), showMore, false)
                MYTEST("Test det & trans", trans_det_test(), showMore, false)
                MYTEST("Test operator <<", print_test(), showMore, false)
        )
    }

    void Test::empty_test() {
        Matrix matrix1, matrix2(1, 1);
        to_line("Empty matrix", matrix1.empty(), 1);
        to_line("Non-Empty matrix", matrix2.empty(), 0);
    }
    void Test::columns_rows_test() {
        Matrix matrix(22, 13);
        to_line("Columns", matrix.columns(), 13);
        to_line("Rows", matrix.rows(), 22);
    }
    void Test::constructors_test() {
        Matrix m;
        to_line("Default: is empty", m.empty(), 1);
        to_line("Default: capacity", m.capacity(), 0);
        to_line(" ");

        to_line("Matrix m1(3)", false);
        Matrix m1(3);
        to_line("Param_1: columns ", m1.columns(), 1);
        to_line("Param_1: rows    ", m1.rows(), 3);
        to_line("Param_1: capacity", m1.capacity(), 3);
        to_line(" ");

        to_line("Matrix m2(5, 6)", false);
        Matrix m2(5, 6);
        to_line("Param_2: columns ", m2.columns(), 6);
        to_line("Param_2: rows    ", m2.rows(), 5);
        to_line("Param_2: capacity", m2.capacity(), 30);
        to_line(" ");

        to_line("Matrix m3(10, 11, 2)", false);
        Matrix m3(10, 11, 2);
        to_line("Param_3: columns ", m3.columns(), 11);
        to_line("Param_3: rows    ", m3.rows(), 10);
        to_line("Param_3: capacity", m3.capacity(), 110);
        to_line("Param_3: value   ", m3(5, 6), 2);
        to_line(" ");

        m1(1, 0) = 3;
        to_line("m1[1][0] = 3", false);
        to_line("Matrix m4(m1)", false);
        Matrix m4(m1);
        to_line("Copy   : columns ", m4.columns(), 1);
        to_line("Copy   : rows    ", m4.rows(), 3);
        to_line("Copy   : capacity", m4.capacity(), 3);
        to_line("Copy   : value   ", m4(1, 0), 3);
        to_line(" ");

        to_line("Matrix m5(std::move(m1))", false);
        Matrix m5(std::move(m1));
        to_line("Move   : columns ", m5.columns(), 1);
        to_line("Move   : rows    ", m5.rows(), 3);
        to_line("Move   : capacity", m5.capacity(), 3);
        to_line("Move   : value   ", m5(1, 0), 3);
        to_line(" ");

        Matrix m6 = {{1, 2, 3, 4}};
        size_t max_ = get_max_size_value(m6);
        to_line("{{1, 2, 3, 4}}");
        for (size_t i = 0; i < m6.rows(); ++i) {
            to_line(row_to_string(m6, i, max_));
        }
        to_line("List 1 : columns ", m6.columns(), 4);
        to_line("List 1 : rows    ", m6.rows(), 1);
        to_line("List 1 : capacity", m6.capacity(), 4);
        to_line(" ");

        Matrix m71 = {1, 2, 3, 4};
        Matrix<int> m72 = {{1},
                           {2},
                           {3},
                           {4}};
        to_line_2_matrix("{1, 2, 3, 4}", m71, "{{1}, {2}, {3}, {4}}", m72);
        to_line("List L : columns ", m71.columns(), 1);
        to_line("List L : rows    ", m71.rows(), 4);
        to_line("List L : capacity", m71.capacity(), 4);
        to_line("List R : columns ", m72.columns(), 1);
        to_line("List R : rows    ", m72.rows(), 4);
        to_line("List R : capacity", m72.capacity(), 4);
        to_line(" ");

        Matrix m8 = {{1, 2},
                     {3, 4},
                     {5, 6}};
        max_ = get_max_size_value(m8);
        to_line("{{1, 2}, {3, 4}, {5, 6}}");
        for (size_t i = 0; i < m8.rows(); ++i) {
            to_line(row_to_string(m8, i, max_));
        }
        to_line("List 2 : columns ", m8.columns(), 2);
        to_line("List 2 : rows    ", m8.rows(), 3);
        to_line("List 2 : capacity", m8.capacity(), 6);
        to_line(" ");

        Matrix m9 = {{1},
                     {2, 3},
                     {5, 6, 7}};
        max_ = get_max_size_value(m9);
        to_line("{{1}, {2, 3}, {5, 6, 7}}");
        for (size_t i = 0; i < m9.rows(); ++i) {
            to_line(row_to_string(m9, i, max_));
        }
        to_line("List 3 : columns ", m9.columns(), 3);
        to_line("List 3 : rows    ", m9.rows(), 3);
        to_line("List 3 : capacity", m9.capacity(), 9);
        to_line(" ");

        Matrix<double> m_d = {1.24, 3.99, 4.51};
        Matrix<int> m_i = m_d;
        to_line_2_matrix("Matrix<double> m_d", m_d, "Matrix<int> m_i = m_d", m_i);
    }
    void Test::reshape_test() {
        Matrix m1(2, 3, 1), m2(m1);
        m2.reshape(3, 2);
        to_line_2_matrix("Before", m1, "After reshape(3,2)", m2);
        res = m2.rows() != 3 || m2.columns() != 2 || m2.rows() * m2.columns() != m1.rows() * m1.columns();

        std::string isCatch = "nothing happened";
        try {
            m2.reshape(10, 100);
        } catch (InvalidSizesException &e) {
            isCatch = e.what();
        }
        catch (...) {
            unknown = true;
            isCatch = "Some went wrong";
        }
        to_line("Try reshape(10, 100)", isCatch);
        res = res || isCatch != "Matrix(cex) has(ve) unsuitable size(s)";
    }
    void Test::reserve_test() {
        Matrix matrix(2, 3);
        to_line("Before", false);
        to_line("Columns ", matrix.columns(), 3);
        to_line("Rows    ", matrix.rows(), 2);
        to_line("Capacity", matrix.capacity(), 6);

        matrix.reserve(1);
        to_line("After reserve(1)", false);
        to_line("Columns ", matrix.columns(), 3);
        to_line("Rows    ", matrix.rows(), 2);
        to_line("Capacity", matrix.capacity(), 6);

        matrix.reserve(10);
        to_line("After reserve(10)", false);
        to_line("Columns ", matrix.columns(), 3);
        to_line("Rows    ", matrix.rows(), 2);
        to_line("Capacity", matrix.capacity(), 10);
    }
    void Test::shrink_to_fit_test() {
        Matrix matrix(2, 3);
        to_line("Before", false);
        to_line("Columns ", matrix.columns(), 3);
        to_line("Rows    ", matrix.rows(), 2);
        to_line("Capacity", matrix.capacity(), 6);

        matrix.reserve(10);
        to_line("After reserve(10)", false);
        to_line("Columns ", matrix.columns(), 3);
        to_line("Rows    ", matrix.rows(), 2);
        to_line("Capacity", matrix.capacity(), 10);

        matrix.shrink_to_fit();
        to_line("After shrink_to_fit()", false);
        to_line("Columns ", matrix.columns(), 3);
        to_line("Rows    ", matrix.rows(), 2);
        to_line("Capacity", matrix.capacity(), 6);

        matrix.shrink_to_fit();
        to_line("After shrink_to_fit()", false);
        to_line("Columns ", matrix.columns(), 3);
        to_line("Rows    ", matrix.rows(), 2);
        to_line("Capacity", matrix.capacity(), 6);
    }
    void Test::clear_test() {
        Matrix matrix(2, 3);
        to_line("Before", false);
        to_line("Columns ", matrix.columns(), 3);
        to_line("Rows    ", matrix.rows(), 2);
        to_line("Capacity", matrix.capacity(), 6);

        matrix.clear();
        to_line("After clear()", false);
        to_line("Columns ", matrix.columns(), 0);
        to_line("Rows    ", matrix.rows(), 0);
        to_line("Capacity", matrix.capacity(), 6);
    }
    void Test::operator_bracket_test() {
        Matrix m(2, 3, 1);
        for (int i = 0; i < m.rows(); ++i) {
            for (int j = 0; j < m.columns(); ++j) {
                m[i][j] = (i + 1) * 10 + j + 1;
                res = res || m[i][j] != m(i, j);
            }
        }
        to_lhalf("[]");
        to_rhalf("()");
        size_t size_ = get_max_size_value(m);
        for (int i = 0; i < m.rows(); ++i) {
            to_lhalf(row_to_string_2(m, i, size_));
            to_rhalf(row_to_string(m, i, size_));
        }
        to_line("Vector size", m[0].size(), m.columns());
        to_line(" ");
        to_lhalf("at()");
        to_rhalf("[].at()");
        for (int i = 0; i < m.rows(); ++i) {
            to_lhalf(row_to_string_3(m, i, size_));
            to_rhalf(row_to_string_4(m, i, size_));
        }
        to_line(" ");

        std::string isCatch = "nothing happened";
        try {
            m.at(10, 10);
        } catch (OutOfRange &e) {
            isCatch = e.what();
        } catch (...) {
            unknown = true;
            isCatch = "Some went wrong";
        }
        to_line("at(10, 10) ", isCatch);
        res = res || isCatch != "Matrix out of range";

        isCatch = "nothing happened";
        try {
            m[0].at(10);
        } catch (OutOfRange &e) {
            isCatch = e.what();
        } catch (...) {
            unknown = true;
            isCatch = "Some went wrong";
        }
        to_line("[0].at(10) ", isCatch);
        res = res || isCatch != "Matrix out of range";
    }
    void Test::assignment_operator_test() {
        Matrix<int> m1(2, 3, 3), m2, m3;
        m1.reserve(10);
        to_line("Origin matrix reserve(10)", false);
        to_line("Origin: capacity", m1.capacity(), 10);
        m2 = m1;
        to_line("Origin<int>");
        size_t size_1 = get_max_size_value(m1);
        for (int i = 0; i < m1.rows(); ++i) {
            for (int j = 0; j < m1.columns(); ++j) {
                res = res || m1(i, j) != m2(i, j);
            }
            to_line(row_to_string_2(m1, i, size_1));
        }
        m3 = std::move(m1);
        for (int i = 0; i < m2.rows(); ++i) {
            for (int j = 0; j < m2.columns(); ++j) {
                res = res || m2(i, j) != m3(i, j);
            }
        }
        to_line_2_matrix("Copy =", m2, "Move =", m3);
        to_line("Copy =: capacity", m2.capacity(), 6);
        to_line("Move =: capacity", m3.capacity(), 10);
        to_line(" ");

        Matrix m4 = {{3.14, 2.718, 0.577}, {1.69, 1.44}};
        to_line_2_matrix("m4<double>", m4, "Origin = m4", m1 = m4);
    }
    void Test::add_sub_operators_test() {
        Matrix<int> m1 = {{1, 2, 3},
                     {4, 5, 6}};
        Matrix<int> m2 = {{6, 5, 4},
                     {3, 2, 1}};
        to_line_2_matrix("m1", m1, "m2", m2);
        to_line_2_matrix("m1 + m2", m1 + m2, "m1 - m2", m1 - m2);
        to_line_2_matrix(" m1 += m2", m1 += m2, "m2 -= m1", m2 -= m1);

        Matrix<double> m3 = {{1.23, 43.1, -3.},
                             {90.9, 0.69, 2.1}};
        to_line_2_matrix(" -m1", -m1, "m3", m3);
        to_line_2_matrix(" m1 + m3", m1 + m3, "m2 += m3", m2 += m3);

        std::string isCatch = "nothing happened";
        try {
            m1 + Matrix<int>{1, 2, 3};
        } catch (InvalidSizesException &e) {
            isCatch = e.what();
        }
        catch (...) {
            unknown = true;
            isCatch = "Some went wrong";
        }
        to_line("{1, 2, 3} + m1", isCatch);
        res = res || isCatch != "Matrix(cex) has(ve) unsuitable size(s)";
    }
    void Test::multiply_test() {
        Matrix<int> m1 = {{4, -3, 1, 0}};
        Matrix<int> m2 = {1, 2, 3, 4};
        to_line_2_matrix("m1", m1, "m2", m2);
        to_line_2_matrix("m1 *= -3", m1 *= -3, "2 * m2", 2 * m2);

        Matrix<int> exp_m(1, 1, -3);
        Matrix<int> m3 = m1 * m2;
        to_line_2_matrix("m1 * m2", m3, "Expected", exp_m);
        res = res || m3 != exp_m;

        exp_m = Matrix<int>{{-12, 9,  -3,  0},
                            {-24, 18, -6,  0},
                            {-36, 27, -9,  0},
                            {-48, 36, -12, 0}};
        m3 = m2 * m1;
        to_line_2_matrix("m2 * m1", m3, "Expected", exp_m);
        res = res || m3 != exp_m;

        m3 = m1 * Matrix<int>{{1},
                              {0, 1},
                              {0, 0, 1},
                              {0, 0, 0, 1}};
        to_line_2_matrix("m1 * E", m3, "Expected", m1);
        res = res || m3 != m1;

        std::string isCatch = "nothing happened";
        try {
            m1 * Matrix<int>{1, 2};
        } catch (InvalidSizesException &e) {
            isCatch = e.what();
        } catch (...) {
            unknown = true;
            isCatch = "Some went wrong";
        }
        to_line("m1 * {1, 2}", isCatch);
        res = res || isCatch != "Matrix(cex) has(ve) unsuitable size(s)";

        isCatch = "nothing happened";
        try {
            m1 * Matrix<int>();
        } catch (EmptyException &e) {
            isCatch = e.what();
        } catch (...) {
            unknown = true;
            isCatch = "Some went wrong";
        }
        to_line("Empty matrix * m1", isCatch);
        res = res || isCatch != "Invalid operation on empty matrix";
        to_line(" ");

        exp_m = Matrix<int>{{-3, 2, 0, 0}};
        to_line_2_matrix("m1 *= 0.333", m1 *= 0.333, "Expected", exp_m);
        res = res || m1 != exp_m;

        Matrix exp_d_m = {1.79, 3.58, 5.37, 7.16};
        Matrix m4 = m2 * 1.79;
        to_line_2_matrix("m2 * 1.79", m4, "Expected", exp_d_m);
        res = res || m4 != exp_d_m;
    }
    void Test::trans_det_test() {
        Matrix m = {{1, -2, 3},
                    {4, 8,  6},
                    {7, 8,  9}};
        Matrix exp_m = {{1,  4, 7},
                        {-2, 8, 8},
                        {3,  6, 9}};
        Matrix m2 = trans(m);
        to_line_2_matrix("m", m, "trans(m)", m2);
        res = res || m2 != exp_m;

        to_line("det(m)", det(m), -60);
        to_line("det(trans(m))", det(trans(m)), -60);

        std::string isCatch = "nothing happened";
        try {
            det(Matrix(2, 3, 1));
        } catch (InvalidSizesException &e) {
            isCatch = e.what();
        } catch (...) {
            unknown = true;
            isCatch = "Some went wrong";
        }
        to_line("det({1,1,1},{1,1,1})", isCatch);
        res = res || isCatch != "Matrix(cex) has(ve) unsuitable size(s)";

        isCatch = "nothing happened";
        try {
            det(Matrix());
        } catch (EmptyException &e) {
            isCatch = e.what();
        } catch (...) {
            unknown = true;
            isCatch = "Some went wrong";
        }
        to_line("det(Empty matrix)", isCatch);
        res = res || isCatch != "Invalid operation on empty matrix";
    }
    void Test::print_test() {
        Matrix m1 = {1, -20, 41123, 1, -23234};
        ss << "  m1\n" << m1 << "\n";

        Matrix m2 = {{1,    -20, 410123},
                     {1,    -232},
                     {1242, -124}};
        ss << "  m2\n" << m2 << "\n";
    }

} // namespace linalg::tests