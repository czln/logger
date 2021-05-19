#ifndef FORMAT_H
#define FORMAT_H

#include <string>
#include <vector>
#include <cstring>

/** TODO: args can't have string class for now*/
template <typename ...Args>
inline std::string format_string(std::string format, Args... args) {
    constexpr size_t oldlen = BUFSIZ;
    char buffer[oldlen];  // 默认栈上的缓冲区
    size_t newlen = snprintf(&buffer[0], oldlen, format.c_str(), args...);
    newlen++;  // 算上终止符'\0'

    if (newlen > oldlen) {  // 默认缓冲区不够大，从堆上分配
        std::vector<char> newbuffer(newlen);
        snprintf(newbuffer.data(), newlen, format.c_str(), args...);
        return std::string(newbuffer.data());
    }

    return std::string(buffer);
}
template <typename ...Args>
inline std::string format_string(std::string format, std::string str, Args... args) {
    constexpr size_t oldlen = BUFSIZ;
    char buffer[oldlen];  // 默认栈上的缓冲区
    size_t newlen = snprintf(&buffer[0], oldlen, format.c_str(), str.data(), args...);
    newlen++;  // 算上终止符'\0'
    // size_t newlen = snprintf(&buffer[0], oldlen, format.c_str(), args...);

    if (newlen > oldlen) {  // 默认缓冲区不够大，从堆上分配
        std::vector<char> newbuffer(newlen);
        snprintf(newbuffer.data(), newlen, format.c_str(), args...);
        return std::string(newbuffer.data());
    }

    return std::string(buffer);
}

#endif