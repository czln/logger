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
// template <typename ...Args>
// inline std::string format_string(std::string format, std::string str, Args... args) {
//     constexpr size_t oldlen = BUFSIZ;
//     char buffer[oldlen];  // 默认栈上的缓冲区
//     std::string tmp;

//     size_t newlen = snprintf(&buffer[0], str.size(), format.data(), str.data());
//     newlen++;  // 算上终止符'\0'
//     tmp = format_string(buffer, args...);
//     memmove(buffer, tmp.data(), tmp.size());

//     if (newlen > oldlen) {  // 默认缓冲区不够大，从堆上分配
//         std::vector<char> newbuffer(newlen);
//         snprintf(newbuffer.data(), newlen, format.data(), str.data());
//         return std::string(newbuffer.data());
//     }

//     return buffer;
// }
// template <typename ...Args>
// inline std::string format_string(std::string format, char const* str, Args... args) {
//     constexpr size_t oldlen = BUFSIZ;
//     char buffer[oldlen];  // 默认栈上的缓冲区

//     size_t newlen = snprintf(&buffer[0], oldlen, format.data(), str);
//     newlen++;  // 算上终止符'\0'

//     if (newlen > oldlen) {  // 默认缓冲区不够大，从堆上分配
//         std::vector<char> newbuffer(newlen);
//         snprintf(newbuffer.data(), newlen, format.data(), str);
//         return std::string(newbuffer.data());
//     }

//     return buffer;
// }