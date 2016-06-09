#include <iomanip>
#include <iostream>
#include <utility>
#include <cstdio>

int Log() { return 0; }

// clang needs non-void type for template pack
template <typename T, typename... Rest>
int Log(T target, Rest... rest) {
    time_t const now = std::time(nullptr);
    std::tm const * timeinfo = std::localtime(&now);
    std::cout
        << std::setfill('0')
        << "["
        << timeinfo->tm_year + 1900
        << "/"
        << std::setw(2) << timeinfo->tm_mon + 1
        << "/"
        << std::setw(2) << timeinfo->tm_mday
        << " "
        << std::setw(2) << timeinfo->tm_hour
        << ":"
        << std::setw(2) << timeinfo->tm_min
        << ":"
        << std::setw(2) << timeinfo->tm_sec
        << "] "
        << target
        << std::endl;
    return Log(rest...);
}

// clang consexpr needs a literal type for return value
template <typename ... Args>
inline constexpr int log_all(Args ... args) noexcept {
    return Log(args...);
}


int main() {
    // your code goes here
    log_all(1, 0.2, "foo", true);
    return 0;
}
