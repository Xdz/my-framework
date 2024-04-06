#include "my_window.h"
#include <iostream>
void MyWindow::cleanup()
{
    glfwDestroyWindow(window);
    std::cout << "Destroying window" << std::endl;
    glfwTerminate();
    std::cout << "GLFW Terminated" << std::endl;
}

