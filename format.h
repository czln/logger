#ifndef FORMAT_H
#define FORMAT_H

#include <string>
#include <vector>
#include <cstring>

/** TODO: args can't have string class for now*/
template <typename ...Args>
inline std::string format_string(std::string format, Args... args) {
    char buffer[BUFSIZ];
    size_t newlen = snprintf(&buffer[0], BUFSIZ-1, format.data(), args...);
    return std::string(buffer);
}
#endif //FORMAT_H