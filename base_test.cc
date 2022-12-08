#include <iostream>

#include "base_test.h"

namespace baseTest {
    ///////////////////////////BASE TEST////////////////////////////////

    void BaseTest::print_name(const std::string& name) {
        ss.clear();
        ss.str("");
        std::stringstream vss;
        vss << "   " << name;
        for (int i = 0; i < name_field_width - name.size(); ++i) {
            vss << ' ';
        }
        for (int i = 0; i < field_width - name_field_width - 6; ++i) {
            vss << '-';
        }
        vss << ' ';
        std::cout << vss.str();
    }
    int BaseTest::print_result(int _result_) {
        if (_result_ == Result::OK) std::cout << "OK\n";
        else if (_result_ == Result::RE) std::cout << "RE\n";
        else if (_result_ == Result::WA) std::cout << "WA\n";
        else std::cout << "??\n";
        return _result_;
    }
    inline std::string BaseTest::tf(bool TrueFalse) {
        return ((TrueFalse)? "True ": "False");
    }
    std::string BaseTest::_line() const {
        return std::string(field_width, '_') + "\n";
    }
    bool BaseTest::to_line(const std::string& name, const std::string& test_info, bool _result_) {
        if (left_is_open) to_rhalf(" ");
        ss << '|';
        pc(name_field_width - name.size());
        ss << name << ":   " << test_info;

        pc(base_field_width - test_info.size() - 3 + 1);
        ss << tf(_result_) << " |\n";

        return res = res || !_result_;
    }
    void BaseTest::to_line(const std::string& name, const std::string& test_info) {
        if (left_is_open) to_rhalf(" ");
        if (left_is_open) to_rhalf(" ");
        ss << '|';
        pc(name_field_width - name.size());
        ss << name << ":   " << test_info;
        pc(base_field_width  + status_field_width - test_info.size() - 3);
        ss << "|\n";
    }
    void BaseTest::to_line(const std::string& test_info, bool isCenter) {
        if (left_is_open) to_rhalf(" ");
        ss << '|';
        if (isCenter) {
            size_t l_num = (field_width - 2 - test_info.size()) / 2;
            pc(l_num);
            ss << test_info;
            pc(field_width - 2 - test_info.size() - l_num);
        } else {
            ss << "   " << test_info;
            pc(field_width - test_info.size() - 5);
        }
        ss << "|\n";
    }
    void BaseTest::to_lhalf(const std::string& test_info) {
        if (left_is_open) to_rhalf(" ");
        left_is_open = true;
        ss << "|";
        size_t l_num = ((field_width - 2)/2 - test_info.size()) / 2;
        pc(l_num);
        ss << test_info;
        pc(field_width / 2 - l_num - test_info.size() - 1);
    }
    void BaseTest::to_rhalf(const std::string& test_info) {
        if (!left_is_open) to_lhalf(" ");
        size_t l_num = ((field_width - 2)/2 - test_info.size()) / 2;
        pc(l_num);
        ss << test_info;
        pc(field_width / 2 - l_num - test_info.size() - 1);
        ss << "|\n";
        left_is_open = false;
    }

    void BaseTest::print_details(bool showMore) {
        if (showMore) std::cout << ss.str();
        ss.clear();
        ss.str("");
    }
    void BaseTest::pc(const size_t& num, char c) {
        for (int i = 0; i < num; ++i) {
            ss << c;
        }
    }

} // namespace baseTest
