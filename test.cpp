#include "logger.h"

int main() {
    logging.set_color(true);
    logging.debug("this would not display");
    logging.info("%s", "test");
    return 0;
}