#include "VulkanLoader.hpp"

#include "VulkanContext.hpp"
#include "VulkanConfig.hpp"
#include "VulkanHelper.hpp"

#include <GLFW/glfw3.h>

#include <algorithm>
#include <cstring>

#include "Window.hpp"

namespace kds {

	void VulkanContext::create(ContextConfig contextConfig, GLFWwindow* window) noexcept {
		_contextConfig = std::move(contextConfig);
		loader::init(_vulkanLibrary);
		_loadLayers();
		_loadExtensions();
		_initInstance();
		_initSurface(window);
		_queryPhysicalDevices();
		_initDevice();
		_vulkanSwapchain.init();

		/*for (size_t i{}; i < 100; ++i) {
			_vulkanSwapchain.recreate();
		}*/
	}

	void VulkanContext::_loadLayers() noexcept {
		auto& instanceConfig = _contextConfig.instanceConfig;

		// All of the following code in this function is for debugging purposes only
		if (!_contextConfig.debugConfig.enabled) {
			return;
		}

		instanceConfig.layerNames.push_back("VK_LAYER_LUNARG_standard_validation");

		uint32_t layerCount{};

		// Query the amount of layers available
		auto result = vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
		KDS_CHECK_RESULT(result, "Failed to enumerate instance layer properties.");

		// Need to define the layers array with the correct size
		std::vector<VkLayerProperties> availableLayers(layerCount);

		if (layerCount < instanceConfig.layerNames.size()) {
			std::cerr << "KDS FATAL: More instance layers are requested than available.\n";
			exit(1);
		}

		// Query all the available layers
		result = vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
		KDS_CHECK_RESULT(result, "Failed to enumerate instance layer properties.");

		// Check if every layer requested is available for debugging purpose to prevent segfault in instance creation
		bool allLayersAvailable = std::all_of(instanceConfig.layerNames.begin(), instanceConfig.layerNames.end(),
			[&availableLayers](std::string const& s) {
				return std::any_of(availableLayers.begin(), availableLayers.end(),
					[&s](VkLayerProperties p) {
						return strcmp(s.c_str(), p.layerName) != 0;
					}
				);
			}
		);

		if (!allLayersAvailable) {
			std::cerr << "KDS FATAL: Some requested layers are unavailable.\n";
			exit(1);
		}
	}

	void VulkanContext::_loadExtensions() noexcept {
		auto& instanceConfig = _contextConfig.instanceConfig;

		if (_contextConfig.debugConfig.enabled) {
			instanceConfig.extensionNames.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		}

		// We need platform specific extensions to link vulkan to the actual window, in this case we abstract that with glfw
		uint32_t surfaceExtensionsCount{};
		auto surfaceExtensions = glfwGetRequiredInstanceExtensions(&surfaceExtensionsCount);

		for (size_t&& i{}; i < surfaceExtensionsCount; ++i) {
			instanceConfig.extensionNames.push_back(surfaceExtensions[i]);
		}
	}

	void VulkanContext::_initSurface(GLFWwindow* window) noexcept {
		if (window == nullptr) {
			std::cerr << "KDS FATAL: NULL window passed to vulkan context\n";
			exit(1);
		}

		auto result = glfwCreateWindowSurface(_instance, window, nullptr, _surface.reset());
		KDS_CHECK_RESULT(result, "Failed to create a window surface.\n");
	}

	void VulkanContext::_initInstance() noexcept {
		VkApplicationInfo appInfo{ _contextConfig.applicationConfig.makeConfig() };
		VkInstanceCreateInfo instanceInfo{ _contextConfig.instanceConfig.makeConfig(&appInfo) };

		auto result = vkCreateInstance(&instanceInfo, nullptr, _instance.reset());
		KDS_CHECK_RESULT(result, "Failed to create a VkInstance");

		loader::loadInstanceLevelFunctions(_vulkanLibrary, _instance);

		if (!_contextConfig.debugConfig.enabled) {
			return;
		}

		// The following code is only related to debugging
		loader::loadInstanceLevelDebugFunctions(_vulkanLibrary, _instance);

		VkDebugReportCallbackCreateInfoEXT debugReportCallbackInfo{ _contextConfig.debugConfig.makeConfig() };
		result = vkCreateDebugReportCallbackEXT(_instance, &debugReportCallbackInfo, nullptr, _debugReportCallback.reset());
		KDS_CHECK_RESULT(result, "Failed to create a debug report callback.")
	}

	void VulkanContext::_queryPhysicalDevices() noexcept {
		uint32_t physicalDevicesCount;
		auto result = vkEnumeratePhysicalDevices(_instance, &physicalDevicesCount, nullptr);
		KDS_CHECK_RESULT(result, "Failed to enumerate physical devices");

		if (physicalDevicesCount == 0) {
			std::cerr << "KDS FATAL: No GPU found\n";
			exit(1);
		}

		std::vector<VkPhysicalDevice> availablePhysicalDevices(physicalDevicesCount);
		result = vkEnumeratePhysicalDevices(_instance, &physicalDevicesCount, availablePhysicalDevices.data());
		KDS_CHECK_RESULT(result, "Failed to enumerate physical devices");

		vkGetPhysicalDeviceProperties(availablePhysicalDevices[0], &_physicalDeviceProperties);

		// Pick the first one for now, improve later
		_physicalDevice = availablePhysicalDevices[0];

		if (_contextConfig.debugConfig.enabled) {
			std::cout << "Physical device picked: " << _physicalDeviceProperties.deviceName << '\n';
		}
	}

	void VulkanContext::_initDevice() noexcept {
		auto& deviceQueueConfig = _contextConfig.deviceQueueConfig;
		std::vector<VkDeviceQueueCreateInfo> deviceQueueInfos = deviceQueueConfig.makeConfig(_physicalDevice);
		VkDeviceCreateInfo deviceInfo{ _contextConfig.deviceConfig.makeConfig(_physicalDevice, deviceQueueInfos) };

		auto result = vkCreateDevice(_physicalDevice, &deviceInfo, nullptr, _device.reset());
		KDS_CHECK_RESULT(result, "Failed to create a logical device\n");
		loader::loadDeviceLevelFunctions(_vulkanLibrary, _device);

		// Resize all the queues
		_graphicsQueues.resize(deviceQueueConfig.graphicsQueueInfos.count);
		_computeQueues.resize(deviceQueueConfig.computeQueueInfos.count);
		_transferQueues.resize(deviceQueueConfig.transferQueueInfos.count);
		_sparseBindingQueues.resize(deviceQueueConfig.sparseBindingQueueInfos.count);


		// Retrieve every created queue from the created device
		for (size_t i{}; i < deviceQueueConfig.graphicsQueueInfos.count; ++i) {
			vkGetDeviceQueue(_device, deviceQueueConfig.graphicsQueueInfos.index, i, &_graphicsQueues[i]);
		}

		for (size_t i{}; i < deviceQueueConfig.computeQueueInfos.count; ++i) {
			vkGetDeviceQueue(_device, deviceQueueConfig.computeQueueInfos.index, i, &_computeQueues[i]);
		}

		for (size_t i{}; i < deviceQueueConfig.transferQueueInfos.count; ++i) {
			vkGetDeviceQueue(_device, deviceQueueConfig.transferQueueInfos.index, i, &_transferQueues[i]);
		}

		for (size_t i{}; i < deviceQueueConfig.sparseBindingQueueInfos.count; ++i) {
			vkGetDeviceQueue(_device, deviceQueueConfig.sparseBindingQueueInfos.index, i, &_sparseBindingQueues[i]);
		}

		// Check presenting support for the created queues
		VkBool32 surfaceSupported{};
		result = vkGetPhysicalDeviceSurfaceSupportKHR(_physicalDevice, 0, _surface, &surfaceSupported);
		KDS_CHECK_RESULT(result, "Failed to get physical device surface support\n");

		if (surfaceSupported != VK_TRUE) {
			std::cerr << "KDS FATAL: created surface that does not support graphics queue.\n";
			exit(1);
		}

	}

	VKAPI_ATTR VkBool32 VKAPI_CALL VulkanContext::debugCallback(
		VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t obj,
		size_t location,
		int32_t code,
		const char* layerPrefix,
		const char* msg,
		void* userData)
	{
		std::clog << layerPrefix << ": " << msg << '\n';
		return true;
	}

} // namespace kds
