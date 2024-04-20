#ifndef SET_VULKAN_H
#define SET_VULKAN_H

#include <vulkan/vulkan.h>

class SetVulkan
{
private:
    void printErrorCode(VkResult result);
public:
    SetVulkan();
    ~SetVulkan();

    void initVulkan();
    void cleanup();

    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    
};

#endif // SET_VULKAN_H