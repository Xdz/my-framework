# 设置GLFW

## 包含 glfw 头文件

包含 GLFW/glfw3.h 即可,在包含头文件前也可以添加对应的宏来保证 GLFW 头文件条件编译其中与 Vulkan相关的代码. 

## 初始化GLFW

使用 glfwInit()函数即可初始化glfw,但是在初始化之前可以调用glfwHintxxx() 来对初始化进行设定.


## 设置窗口

使用 glfwCreateWindow()即可初始化窗口,同样可以在 创建窗口之前调用带有hint字样的函数来进行设置.

## 设置Vulkan

与OpenGL不同,Vulkan没得上下文(context),因此GLFW特地提供了对Vulkan的VK_KHR_surface的支持

## 销毁窗口和glfw

使用 glfwDestroyWindow() 和 glfwTerminate() 来结束一个窗口和终止GLFW库.