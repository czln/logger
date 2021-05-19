#include "logger.h"
#include <pthread.h>

logger log;

void * logging(void*) {
    log.error(std::string("not ok"));
    return NULL;
}
class test {
public:
    pthread_t p1;
    pthread_t p2;
    test(){ }
    ~test(){}
    void init();
};
void test::init() {
    std::string a = "string test";
    log.info("%s", a);
    pthread_create(&p1, NULL, logging, NULL);
    pthread_create(&p2, NULL, logging, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
}

/** TODO:   multiple files log share */
int main() {

    log.set_attr(STDOUT | FILES | ERR_MSG, "out.log");
    log.set_color(true);
    // log.set_lvl(WARNING);
    class test t;
    t.init();
    return 0;
}