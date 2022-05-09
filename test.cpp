#include "logger.h"

int main() {
    logging.debug("this would not display");
    logging.info("%s", "test");
    return 0;
}