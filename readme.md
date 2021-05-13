# logger
this is a simple c++ logger tool which is thread safe (sice std::iostream is thread safe), and support std::string in C like format
## requirements
c++11, and since a macro `##__VA_ARGS__` is used, I know gcc and clang supports it, while for others, I don't know for sure.
to use this just initialize an instance of the class.
## severity
there're 5 severity levels, including: info, debug, warning, error and fatal
the default serverity level is `INFO`, to change it, you can change the parameter `lvl` with function `void set_attr(attr_t att, std::string, file=std::string())`, or specify it when construct the class.
## output
the default output is stdout
only, and you can output to a file at the same time. just set the parameter `attr = STDOUT | FILES` and specify your `filename`.
and there're 5 levels of output function, like `logger::info()`.
only the function's level is higher (like error is higher than info),
there will be an output.
## error message
it's also a flag bit in `attr`, you can have it like `STDOUT | FILES | ERR_MSG`, and if you're using function whose level is higher than `warning`( warning itself is not included), than the log will add the error message after the string you specify
## format
### string format
the C like format is supported, for example
``` c
std::string str = "std::string"; // or const char str[]="c like string";
logger log;
log.info("this is what I add: %s.\n", str);
```

``` c
const char str[] = "c like string";
std::string fmt = "this is what I add: %s.\n";
logger log;
log.info(fmt, str);
```
### time format
you can also set your own time format like strftime:
`setfmt("%Y-%m-%D %H:%M:%S")`