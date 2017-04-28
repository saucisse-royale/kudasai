#include "VulkanConfig.hpp"
#include "VulkanContext.hpp"

namespace kds {
VkApplicationInfo ApplicationConfig::makeConfig() noexcept
{
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.apiVersion = VK_API_VERSION_1_0;
    appInfo.applicationVersion = appVersion;
    appInfo.pApplicationName = appName.c_str();
    appInfo.engineVersion = engineVersion;
    appInfo.pEngineName = engineName.c_str();

    return appInfo;
}

VkInstanceCreateInfo InstanceConfig::makeConfig(VkApplicationInfo const* appInfo) noexcept
{
    VkInstanceCreateInfo instanceInfo{};
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pApplicationInfo = appInfo;
    instanceInfo.enabledExtensionCount = extensionNames.size();
    instanceInfo.ppEnabledExtensionNames = extensionNames.data();
    instanceInfo.enabledLayerCount = layerNames.size();
    instanceInfo.ppEnabledLayerNames = layerNames.data();

    return instanceInfo;
}

VkDebugReportCallbackCreateInfoEXT DebugConfig::makeConfig() noexcept
{
    VkDebugReportCallbackCreateInfoEXT debugReportCallbackInfo{};
    debugReportCallbackInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
    debugReportCallbackInfo.pfnCallback = VulkanContext::debugCallback;

    switch (severity) {
    case ERRORS:
        debugReportCallbackInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT;
        break;
    case WARNINGS:
        debugReportCallbackInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
        break;
    case FULL:
        debugReportCallbackInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT | VK_DEBUG_REPORT_INFORMATION_BIT_EXT | VK_DEBUG_REPORT_DEBUG_BIT_EXT;
        break;
    }

    return debugReportCallbackInfo;
}

std::vector<VkDeviceQueueCreateInfo> DeviceQueueConfig::makeConfig(VkPhysicalDevice physicalDevice) noexcept
{
    // The array of CreateInfo structs to return
    std::vector<VkDeviceQueueCreateInfo> deviceQueueInfos{};

    // First query the queue families available in the selected physical device
    uint32_t queueFamilyPropertiesCount;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyPropertiesCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyPropertiesCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyPropertiesCount, queueFamilyProperties.data());

    ++graphicsQueueInfos.count; // add one for the present queue

    // We need to create a CreateInfo Structure for each requested queue family
    for (size_t i{}; i < queueFamiliesCount; ++i) { // queueFamiliesCount == 4
        QueueInfos* currentQueueInfo{ nullptr }; // We can't use a reference here because the init value is determined in the following switch statement

        switch (i) {
        case 0:
            currentQueueInfo = &graphicsQueueInfos;
            break;
        case 1:
            currentQueueInfo = &computeQueueInfos;
            break;
        case 2:
            currentQueueInfo = &transferQueueInfos;
            break;
        case 3:
            currentQueueInfo = &sparseBindingQueueInfos;
            break;
        }

        if (currentQueueInfo->count == 0) {
            continue;
        }

        currentQueueInfo->priorities.resize(currentQueueInfo->count, 1.0f);

        VkDeviceQueueCreateInfo deviceQueueInfo{};
        deviceQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        deviceQueueInfo.queueCount = currentQueueInfo->count;
        deviceQueueInfo.pQueuePriorities = currentQueueInfo->priorities.data();

        // Find the current queue family
        // Small trick to match the increment index to queue family flag, which is 0x1, 0x2, 0x4, 0x8 to avoid massive switch statements
        auto currentQueueFamily{ currentQueueInfo->family };

        // custom search algorithm, only used once
        // it finds the index in the array of available queue families that matches the flag requested by the queue family we want to create
        currentQueueInfo->index = [&] {
            for (size_t&& j{}; j < queueFamilyPropertiesCount; ++j) {
                if ((queueFamilyProperties[j].queueCount > 0) && (queueFamilyProperties[j].queueFlags & currentQueueFamily)) {
                    return j;
                    // Validation layer can complain that queueFamilyIndex is not unique.
                    // Ignore it, Nvidia gpus have 16 queues that can do anything, so the queue family index will always be the same
                }
            }
            std::cerr << "KDS FATAL: Requested queue family is not available on the selected GPU.\n";
            exit(1);
        }();

        deviceQueueInfo.queueFamilyIndex = currentQueueInfo->index;

        deviceQueueInfos.push_back(std::move(deviceQueueInfo));
    }
    return deviceQueueInfos;
}

VkDeviceCreateInfo DeviceConfig::makeConfig(VkPhysicalDevice physicalDevice, std::vector<VkDeviceQueueCreateInfo>& deviceQueueInfos) noexcept
{
    VkDeviceCreateInfo deviceInfo{};
    deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceInfo.queueCreateInfoCount = deviceQueueInfos.size();
    deviceInfo.pQueueCreateInfos = deviceQueueInfos.data();
    deviceInfo.enabledExtensionCount = extensions.size();
    deviceInfo.ppEnabledExtensionNames = extensions.data();
    return deviceInfo;
}
} // namespace kds
