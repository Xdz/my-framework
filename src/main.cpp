#include "my_window.h"
#include <iostream>


int main() {
    MyWindow window;
    window.initGLFW();
    window.run();
    window.cleanup();
    return 0;
}