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

    uint32_t instanceExtensionCount;
    std::vector<VkExtensionProperties> instanceExtensions;

    uint32_t physicalDeviceCount;
    std::vector<VkPhysicalDevice> physicalDevices;

    uint32_t queueFamilyPropertyCount;
    std::vector<VkQueueFamilyProperties> queueFamilyProperties;

    uint32_t deviceExtensionCount;
    std::vector<VkExtensionProperties> deviceExtensions;

    VkResult getVulkanVersion();
    VkResult getAviableLayers();
    VkResult getAviableInstanceExtensions();
    VkResult getAviableDeviceExtensions();

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
    VkPhysicalDeviceProperties physicalDeviceProperties;
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;

};

#endif // SET_VULKAN_H