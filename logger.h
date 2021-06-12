#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <mutex>
#include <unordered_map>
#include <initializer_list>
#include <ctime>
#include "format.h"
/**
 *  TODO: signal dump i.g. crash handle
 */
typedef int lvl_t;
typedef int attr_t;

static const std::string DEFAULT_COLOR = "\033[0m";

// level
enum {
    INFO,   // default
    DEBUG,
    WARNING,
    ERROR,  // error which would cause the runing function terminate
    FATAL   // which would cause the whole programme terminate
};

//attribute
enum {
    STDOUT = 1, // default
    FILES,
    BOTH,
    ERR_MSG     // enable stderr info if lvl>=ERROR
};

class logger {
private:
    lvl_t   level;
    attr_t  attr;
    bool    has_color;
    std::string timefmt;
    std::string filename;
    std::unordered_map<lvl_t, std::string> map;
    std::unordered_map<lvl_t, std::string> color_map;

public:
    logger(lvl_t lvl=INFO, attr_t att=STDOUT) :
        level(lvl), attr(att) { init(); }
    ~logger() {};

private:
    void init() {
        has_color = false;
        timefmt = "%Y-%m-%d %H:%M:%S";
        map = {{INFO,"info"}, {DEBUG,"debug"}, {WARNING,"warning"},
            {ERROR,"error"}, {FATAL,"fatal"}};
        color_map = {{INFO,"\033[34;1m"}, {DEBUG,"\033[34;1m"}, {WARNING,"\033[35;1m"},
            {ERROR,"\033[31;1m"}, {FATAL,"\033[31;1m"}};

        }
public:
    // set serevarity
    void set_lvl(int lvl) {level = lvl;}
    /**
     *  TODO: absolute path
     *  set output attribute
     */
    void set_attr(attr_t att, std::string file=std::string()) {attr = att; filename = file;} 
    // set level colr on or off
    void set_color(bool arg) { has_color = arg; }
    void set_fmt(std::string str){ timefmt = str; }

    /**
     *  NOTE: even it's a public memthod, it's not supposed to be used directly
     */
    const std::string _out(std::string str, lvl_t lvl, std::string func, std::string file, int line);

/** @warning use this carefully! */
#define _STRING_WITH_COLOR(str)   ((color_map[lvl] + str + DEFAULT_COLOR).data())

/** @a meta template programme*/
#if __cplusplus > 2011
/** @p ##__VA_ARGS__ may not be supported by some compilers
 *  but @p __VA_ARGS__ is supported after c++11
 *  TODO: these defines cause some include path problems @p "format_string()" for @p __PRETTY_FUNCTION__: 
 */
#define info(str, ...) _out(format_string(str, ##__VA_ARGS__), INFO, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define debug(str, ...) _out(format_string(str, ##__VA_ARGS__), DEBUG, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define warning(str, ...) _out(format_string(str, ##__VA_ARGS__), WARNING, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define error(str, ...) _out(format_string(str, ##__VA_ARGS__), ERROR, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define fatal(str, ...) _out(format_string(str, ##__VA_ARGS__), FATAL, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#else
#define info(str) _out(str, INFO, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define debug(str) _out(str, DEBUG, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define warning(str) _out(str, WARNING, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define error(str) _out(str, ERROR, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#define fatal(str) _out(str, FATAL, __PRETTY_FUNCTION__, __FILE__, __LINE__)
#endif
};
/** TODO: extern C*/

extern logger logging;

#endif  // LOGGER_H