#include "my_window.h"
#include <iostream>

void callback(int error, const char* description)
{
    std::cout << "Error number is : " << error << std::endl;
    std::cout << "Error: " << description << std::endl;
}

MyWindow::MyWindow()
{
    window = nullptr;
}

void MyWindow::initGLFW()
{
    int major, minor;
    glfwGetVersion(&major, &minor, nullptr);
    std::cout << "GLFW Version: " << major << "." << minor << std::endl;
    if (major < 3 && minor < 4)
    {
        std::cout<<"GLFW Version must at lease be 3.4\n";
    }
    glfwSetErrorCallback(callback);
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WIN32);
    glfwInitHint(GLFW_ANGLE_PLATFORM_TYPE, GLFW_ANGLE_PLATFORM_TYPE_VULKAN);

    int status = glfwInit();
    if(status == GLFW_FALSE)
    {
        std::cout << "GLFW initialization failed\n";
        return;
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(1200, 800, "Vulkan", nullptr, nullptr);
}


