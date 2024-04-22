#include "set_vulkan.h"
#include <vector>
#include <fmt/core.h>
#include <fmt/format.h>


SetVulkan::SetVulkan()
{
    layerCount = 0;
    extensionCount = 0;
    apiVersion = 0;
    instance = VK_NULL_HANDLE;
    physicalDevice = VK_NULL_HANDLE;
    device = VK_NULL_HANDLE;
    graphicsQueue = VK_NULL_HANDLE;
    presentQueue = VK_NULL_HANDLE;
}


SetVulkan::~SetVulkan()
{
    vkDestroyInstance(instance, nullptr);
}

VkResult SetVulkan::getVulkanVersion()
{
    VkResult result;
    result = vkEnumerateInstanceVersion(&apiVersion);
    return result;
}

VkResult SetVulkan::getAviableLayers()
{
    VkResult result;
    result = vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    availableLayers.resize(layerCount);
    result = vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
    return result;
}

VkResult SetVulkan::getAviableExtensions()
{
    VkResult result;
    result = vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    availableExtensions.resize(extensionCount);
    result = vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());
    return result;
}

VkBool32 debugReportCallback(
        VkDebugReportFlagsEXT        flags,
        VkDebugReportObjectTypeEXT   objectType,
        uint64_t                     object,
        size_t                       location,
        int32_t                      messageCode,
        const char*                  pLayerPrefix,
        const char*                  pMessage,
    void* pUserData)
{
    if (objectType == VK_DEBUG_REPORT_OBJECT_TYPE_INSTANCE_EXT)
    {
        fmt::print("Instance error: {}\n", pMessage);
    }

    return VK_FALSE;
}

VkResult SetVulkan::createInstance()
{
    VkResult result;

    //print Vulkan API version
    getVulkanVersion();
    fmt::print("Vulkan API version: {}.{}.{}\n", VK_API_VERSION_MAJOR(apiVersion), VK_API_VERSION_MINOR(apiVersion), VK_API_VERSION_PATCH(apiVersion));

    //check available layers
    getAviableLayers();

    //check available extensions
    getAviableExtensions();

    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = nullptr;
    appInfo.pApplicationName = "learn_vulkan";
    appInfo.applicationVersion = 01;
    appInfo.pEngineName = nullptr;
    appInfo.engineVersion = 0;
    appInfo.apiVersion = apiVersion;

    PFN_vkDebugReportCallbackEXT pCallback = debugReportCallback;
    
    VkDebugReportCallbackCreateInfoEXT debugCreateInfo = {};
    debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    debugCreateInfo.pNext = nullptr;
    debugCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
    debugCreateInfo.pfnCallback = &debugReportCallback;
    debugCreateInfo.pUserData = nullptr;

    std::vector<const char*> layerNames;
    std::vector<const char*> extensionNames;
    for(auto i: availableLayers)
    {
        //fmt::print("Available layer: {}\n", i.layerName);
        layerNames.push_back(i.layerName);
    }
    for (auto i: availableExtensions)
    {
        //fmt::print("Available extension: {}\n", i.extensionName);
        extensionNames.push_back(i.extensionName);
    } 

    VkInstanceCreateInfo instanceCreateInfo = {};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pNext = &debugCreateInfo;
    instanceCreateInfo.flags = 0;
    instanceCreateInfo.pApplicationInfo = &appInfo;
    instanceCreateInfo.enabledLayerCount = layerCount;
    instanceCreateInfo.ppEnabledLayerNames = layerNames.data();
    instanceCreateInfo.enabledExtensionCount = extensionCount;
    instanceCreateInfo.ppEnabledExtensionNames = extensionNames.data();

    fmt::print("Creating instance...\n");
    result = vkCreateInstance(&instanceCreateInfo, nullptr, &instance);
    fmt::print("Create instance result: {}\n", (uint32_t)result);

    return result;
}

VkResult SetVulkan::selectPhysicalDevice()
{
    VkResult result;
    result = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);
    physicalDevices.resize(physicalDeviceCount);
    result = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices.data());
    //#TODO: select the best physical device
    return result;
}

void SetVulkan::initVulkan()
{
    createInstance();
    selectPhysicalDevice();
    createLogicalDevice();
}

void SetVulkan::cleanup()
{
    vkDestroyInstance(instance, nullptr);
}