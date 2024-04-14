
#include "utils.hpp"

int main(void) {
    utils::intro();  // just messages

    // check if every SDL object was initialised correctly.
    if (utils::init() == 0) {
        // the rendering loop, pass true for limited number of renders
        // also pass num    ber of loops
        utils::run(false, 1);

        // otherwise generate an image
        // utils::saveAsPng();
    }

    utils::kill();

    return 0;
}