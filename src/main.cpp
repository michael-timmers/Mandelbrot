
#include "utils.hpp"

int main(void) {
    utils::intro();  // just messages

    // check if every SDL object was initialised correctly.
    if (utils::init() == 0) {
        // the rendering loop, pass true for average rendering time
        // aslo pass number of loops to get average
        utils::run(true, 20);
    }

    utils::kill();

    return 0;
}