#include "set_vulkan.h"
#include <fmt/core.h>
#include <fmt/format.h>

void SetVulkan::printErrorCode(VkResult result)
{
    if (result != VK_SUCCESS)
    {
        fmt::print("Error code: {}\n", static_cast<uint32_t>(result));
    }
}

SetVulkan::SetVulkan()
{
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

static void createInstance(VkInstance& instance)
{
    uint32_t apiVersion = 0;
    vkEnumerateInstanceVersion(&apiVersion);
    fmt::print("Vulkan API version:{}.{}.{}\n", VK_VERSION_MAJOR(apiVersion), VK_VERSION_MINOR(apiVersion), VK_VERSION_PATCH(apiVersion));

    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = nullptr;
    appInfo.pApplicationName = "learn_vulkan";
    appInfo.applicationVersion = 01;
    appInfo.pEngineName = nullptr;
    appInfo.engineVersion = 0;
    appInfo.apiVersion = apiVersion;


    VkInstanceCreateInfo instanceCreateInfo = {};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pNext = nullptr;
    instanceCreateInfo.flags = 0;
    instanceCreateInfo.pApplicationInfo = &appInfo;
    instanceCreateInfo.enabledLayerCount = 0;
    instanceCreateInfo.ppEnabledLayerNames = nullptr;
    instanceCreateInfo.enabledExtensionCount = 0;
    instanceCreateInfo.ppEnabledExtensionNames = nullptr;

    vkCreateInstance(&instanceCreateInfo, nullptr, &instance);

}

void SetVulkan::initVulkan()
{
    createInstance(instance);
}