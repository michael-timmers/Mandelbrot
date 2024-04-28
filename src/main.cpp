
#include "appmanager.hpp"

int main(void) {
    // pass number of stelps to take
    AppManager app(250);

    // pass true and number of renders for debuging.
    app.run(false, 1);

    // otherwise, only generate an image
    // app.saveAsPng();

    return 0;
}