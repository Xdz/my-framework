#ifndef MY_WINDOW_H
#define MY_WINDOW_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class MyWindow
{
public:
    GLFWwindow* window;
    MyWindow();
    ~MyWindow();
    void initGLFW();
    void run();
    void cleanup();
};

#endif // MY_WINDOW_H