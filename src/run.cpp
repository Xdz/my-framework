#include "my_window.h"
#include <iostream>

void MyWindow::run()
{
    std::cout << "Running window" << std::endl;
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }
}