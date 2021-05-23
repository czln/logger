#include "logger.h"
#include <cstdio>
#include <cstdlib>
const std::string logger::_out(std::string str, lvl_t lvl, std::string func, std::string file, int line) {
    if (level > lvl)
        return std::string();
    if (level<0 || !attr) {
        std::cout << "log failed to initialize\n";
        return std::string();
    }
    if (lvl > WARNING) {
        if (errno) {
            str = str + ": " + std::string(strerror(errno));
            errno = 0;
        }
    }
    time_t raw_time = time(NULL);
    struct tm *now;
    char buf[128];
    now = localtime(&raw_time);
    strftime(buf, 128, timefmt.data(), now);
    if (attr & FILES && !filename.empty()) {
        std::fstream fo;
        /** TODO: if file is too big, shall open another file or rewrite it */
        fo.open(filename, std::ios::app);
        if (!fo.is_open()) {
            std::cerr << "cannot open file " << filename
            << std::endl;
            return std::string();
        }
        // fo << dt <<'[' << getpid() << "](" << map[lvl] <<") " << '\"'
        // << str << "\": function " << func << "() in file: "
        // << file << " at " << line << std::endl;
        fo << format_string("%s %s:%d: %s: %s\n[%d:%ul]: %s\n",
            buf, file.data(), line, map[lvl].data(), str.data(),
            getpid(), pthread_self(), func.data());
        fo.close();
    }
    if (attr & STDOUT) {
        if (has_color)
            std::cout << format_string("%s %s:%d: %s: %s\n[%d:%ul]: %s\n",
            buf, file.data(), line, _STRING_WITH_COLOR(map[lvl]), str.data(),
            getpid(), pthread_self(), _STRING_WITH_COLOR(func.data()));
        else
            std::cout << format_string("%s %s:%d: %s: %s\n[%d:%ul]: %s\n",
            buf, file.data(), line, map[lvl].data(), str.data(),
            getpid(), pthread_self(), func.data());
    }
    return std::string();
}


logger logging(INFO);