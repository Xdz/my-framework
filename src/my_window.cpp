#include "my_window.h"
#include <iostream>
#include <vector>
#include <cstring>

//GLFW error callback
void callback(int error, const char* description)
{
    std::cout << "Error number is : " << std::hex << error << std::endl;
    std::cout << "Error: " << description << std::endl;
}

//check Vulkan support
static void checkVulkanSupport()
{
    //check Vulkan support
    if (glfwVulkanSupported() == GLFW_FALSE)
    {
        std::cout << "Vulkan not supported\n";
        return;
    }

    uint32_t extensionCount = 0;
    const char** ppExtensions = glfwGetRequiredInstanceExtensions(&extensionCount);
    for (auto i = 0; i < extensionCount; i++)
    {
        if (strcmp(ppExtensions[i], "VK_KHR_surface"))
        {
            std::cout << "VK_KHR_surface supported\n";
        }
    }

}


MyWindow::MyWindow()
{
    window = nullptr;
}

void MyWindow::initGLFW()
{
    //check glfw version
    int major, minor;
    glfwGetVersion(&major, &minor, nullptr);
    std::cout << "GLFW Version: " << major << "." << minor << std::endl;
    if (major < 3 && minor < 4)
    {
        std::cout << "GLFW Version must at lease be 3.4\n";
    }
    glfwSetErrorCallback(callback);

    //initialize glfw
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WIN32);
    glfwInitHint(GLFW_ANGLE_PLATFORM_TYPE, GLFW_ANGLE_PLATFORM_TYPE_VULKAN);

    int status = glfwInit();
    if (status == GLFW_FALSE)
    {
        std::cout << "GLFW initialization failed\n";
        return;
    }

    checkVulkanSupport();

    //create window
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(1200, 800, "Vulkan", nullptr, nullptr);
}

void MyWindow::run()
{
    std::cout << "Running window" << std::endl;
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }
}

void MyWindow::cleanup()
{
    glfwDestroyWindow(window);
    std::cout << "Destroying window" << std::endl;
    glfwTerminate();
    std::cout << "GLFW Terminated" << std::endl;
}

MyWindow::~MyWindow()
{
}
