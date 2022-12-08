#pragma once

#include <sstream>


namespace baseTest {

    class BaseTest {
    public:
        enum Result : int {OK = 0, RE = 2, WA = 1};

        BaseTest() = default;
    protected:
        std::stringstream ss;
        const int status_field_width = 7;
        const int name_field_width = 26;
        const int base_field_width = 54;
        const int field_width = base_field_width + name_field_width + status_field_width + 3;
        bool left_is_open = false;

        void print_name(const std::string& name);
        static int print_result(int _result_);
        static inline std::string tf(bool TrueFalse);
        std::string _line() const;
        template<class T1, class T2> bool to_line(const std::string& name, const T1 &value, const T2& expected_ans);
        bool to_line(const std::string& name, const std::string& test_info, bool _result_);
        void to_line(const std::string& name, const std::string& test_info);
        void to_line(const std::string& test_info, bool isCenter= true);
        void to_lhalf(const std::string& test_info);
        void to_rhalf(const std::string& test_info);

        void print_details(bool showMore);
        void pc(const size_t& num, char c = ' ');

        int res = Result::OK;
        bool unknown = false;
    };

    template<class T1, class T2> bool BaseTest::to_line(const std::string& name, const T1 &value, const T2& expected_ans) {
        std::stringstream vss;
        vss << value << " == " << expected_ans;
        return to_line(name, vss.str(), value == expected_ans);
    }

} // namespace baseTest

#ifndef START_MYTESTS
#define START_MYTESTS(tests) { \
    std::cout << _line();               \
    std::cout << "Run tests:\n";        \
    int result = 0;                     \
    bool unknown_in_all = false;        \
    tests                               \
    if (!result) std::cout << "\nAll tests was complete!\n";\
    else std::cout << "\nProblem in " << result << " tests\n";\
    if (unknown_in_all) std::cout << "There are unknown results\n";\
    std::cout << _line() << "\n";       \
}
#endif

#ifndef MYTEST
#define MYTEST(name, test, show_more_all, show_more) {       \
    print_name(name);                           \
    res = Result::OK;                           \
    unknown = false;                       \
    ss << _line();                              \
    try {test;}                                 \
    catch(...) {unknown = true; }               \
    ss << _line() << "\n";                      \
    res += unknown;                             \
    print_result(res);                          \
    print_details(show_more_all || show_more);                 \
    result += (unknown_in_all = unknown_in_all || res == Result::RE, bool(res)); \
    }
#endif