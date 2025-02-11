#include "path_app.h"

int main() {
    auto app = new core::app();
    app->run();
    delete app;
    return 0;
}