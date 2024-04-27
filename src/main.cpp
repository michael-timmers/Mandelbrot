
#include "appmanager.hpp"

int main(void) {
    AppManager app;
    app.intro();  // just messages

    // check if SDL was initialised correctly.
    if (app.init() == 0) {
        // the rendering loop, pass true for limited number of renders
        // also pass number of loops
        app.run(false, 1);

        // otherwise generate an image
        // app.saveAsPng();
    }

    app.quit();

    return 0;
}