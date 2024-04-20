#include "my_window.h"
#include "set_vulkan.h"
#include <iostream>


int main() {
    MyWindow window;
    SetVulkan set_vulkan;
    window.initGLFW();
    set_vulkan.initVulkan();
    window.run();
    set_vulkan.cleanup();
    window.cleanup();
    return 0;
}