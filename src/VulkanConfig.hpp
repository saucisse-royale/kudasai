#ifndef VULKAN_CONFIG_HPP
#define VULKAN_CONFIG_HPP

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>

#include "VulkanLoader.hpp"

namespace kds {
	struct ApplicationConfig {
		VkApplicationInfo makeConfig() noexcept;

		uint32_t appVersion{1};
		std::string appName{"Kudasai"};
		uint32_t engineVersion{1};
		std::string engineName{"Kudasai"};
	};

	struct InstanceConfig {
		VkInstanceCreateInfo makeConfig(VkApplicationInfo const* appInfo) noexcept;

		// The extensions that will be loaded (e.g. surface extensions)
		std::vector<char const*> extensionNames{};

		// Debug validation layers
		std::vector<char const*> layerNames{};
	};

	struct DebugConfig {
		VkDebugReportCallbackCreateInfoEXT makeConfig() noexcept;

		// Defines if the validation layers are enabled or not
		bool enabled{false};

		// Defines the amount of debug messages given by the validation layers
		//    ERRORS: only fatal errors
		//    WARNINGS: errors + warnings
		//    FULL: it will show anything given by the layers, it will flood the screen
		enum {
			WARNINGS,
			ERRORS,
			FULL
		} severity{ERRORS};
	};

	struct DeviceQueueConfig {
		// Returns an array of VkDeviceQueueCreateInfo since multiple queues can be created with the device
		std::vector<VkDeviceQueueCreateInfo> makeConfig(VkPhysicalDevice physicalDevice) noexcept;

		// Contains all the queue priorities for each queue family, 1.0f by default so that every queue have the same priority level
		std::vector<std::vector<float>> queuePriorities{};

		enum DeviceQueueType {
			GRAPHICS,
			COMPUTE,
			TRANSFER,
			SPARSE_BINDING
		};

		// Queue type array which defines what kind of queues will be created, and in which quantity
		// NB: one queue CANNOT have two different queue type flags at the same time
		std::vector<std::pair<DeviceQueueType, size_t>> queueTypes{{GRAPHICS, 1}};
		//std::unordered_map<DeviceQueueType, size_t> queueTypes{{GRAPHICS, 1}}; test
	};

	struct DeviceConfig {
		VkDeviceCreateInfo makeConfig(VkPhysicalDevice physicalDevice, std::vector<VkDeviceQueueCreateInfo> &deviceQueueInfos) noexcept;

		// the name of the device extensions to enable
		std::vector<char const*> extensions{"VK_KHR_swapchain"};

		// NB: devices layers are deprecated and should not be set
	};

	struct ContextConfig {
		ApplicationConfig applicationConfig{};
		InstanceConfig instanceConfig{};
		DebugConfig debugConfig{};
		DeviceQueueConfig deviceQueueConfig{};
		DeviceConfig deviceConfig{};
	};
} // namespace kds

#endif // VulkanConfig.hpp
