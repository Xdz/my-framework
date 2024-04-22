#ifndef SET_VULKAN_H
#define SET_VULKAN_H

#include <vulkan/vulkan.h>
#include <vector>

class SetVulkan
{
private:
    uint32_t apiVersion;

    uint32_t layerCount;
    std::vector<VkLayerProperties> availableLayers;

    uint32_t extensionCount;
    std::vector<VkExtensionProperties> availableExtensions;

    uint32_t physicalDeviceCount;
    std::vector<VkPhysicalDevice> physicalDevices;

    VkResult getVulkanVersion();
    VkResult getAviableLayers();
    VkResult getAviableExtensions();

    VkResult createInstance();
    VkResult selectPhysicalDevice();
    VkResult createLogicalDevice();

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