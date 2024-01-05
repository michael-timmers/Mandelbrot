
#include "utils.hpp"

int main(void) {
    utils::intro();  // just messages

    // check if every SDL object was initialised correctly.
    if (utils::init() == 0) {
        // the rendering loop, pass true for average rendering time
        // also pass number of loops to get average
        utils::run(false, 50);
    }

    utils::kill();

    return 0;
}