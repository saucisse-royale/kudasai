#pragma once

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

	struct WindowConfig {
		std::string title{""};
		size_t width{1024};
		size_t height{768};
		bool resizable{true};
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

		enum DeviceQueueType {
			GRAPHICS = 0,
			COMPUTE = 1,
			TRANSFER = 2,
			SPARSE_BINDING = 3
		};

		struct QueueInfos {
			uint32_t count{};
			uint32_t index{};
			std::vector<float> priorities{};
			VkQueueFlagBits family;
		};

		QueueInfos presentQueueInfos{
			.count = 1,
			.priorities = {1.0f},
			.family = VK_QUEUE_GRAPHICS_BIT
		};

		QueueInfos graphicsQueueInfos{
			.count = 1,
			.priorities = {1.0f},
			.family = VK_QUEUE_GRAPHICS_BIT
		};

		QueueInfos computeQueueInfos{.family = VK_QUEUE_COMPUTE_BIT};
		QueueInfos transferQueueInfos{.family = VK_QUEUE_TRANSFER_BIT};
		QueueInfos sparseBindingQueueInfos{.family = VK_QUEUE_SPARSE_BINDING_BIT};

	private:
		uint32_t queueFamiliesCount{4}; // !! DON'T CHANGE THIS
	};

	struct DeviceConfig {
		VkDeviceCreateInfo makeConfig(VkPhysicalDevice physicalDevice, std::vector<VkDeviceQueueCreateInfo> &deviceQueueInfos) noexcept;

		// the name of the device extensions to enable
		std::vector<char const*> extensions{"VK_KHR_swapchain"};

		// NB: devices layers are deprecated and should not be set
	};


	struct ContextConfig {
		ApplicationConfig applicationConfig{};
		WindowConfig windowConfig{};
		InstanceConfig instanceConfig{};
		DebugConfig debugConfig{};
		DeviceQueueConfig deviceQueueConfig{};
		DeviceConfig deviceConfig{};
	};
} // namespace kds
