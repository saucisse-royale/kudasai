#ifndef VULKAN_CONTEXT_HPP
#define VULKAN_CONTEXT_HPP

#include "VulkanLoader.hpp"
#include "VulkanConfig.hpp"
#include "RAII.hpp"

namespace kds {

	class VulkanContext {
	public:
		VulkanContext(ContextConfig contextConfig) noexcept;

	private:
		void _loadLayers() noexcept;
		void _loadExtensions() noexcept;

		void _initInstance() noexcept;
		void _queryPhysicalDevices() noexcept;
		void _initDevice() noexcept;

		RAII<VULKAN_LIBRARY_TYPE> _vulkanLibrary{loader::terminate, _vulkanLibrary};

		VkPhysicalDevice _physicalDevice;
		VkPhysicalDeviceProperties _physicalDeviceProperties;

		ContextConfig _contextConfig;
		RAII<VkInstance> _instance{vkDestroyInstance, _instance, nullptr};
		RAII<VkDevice> _device{vkDestroyDevice, _device, nullptr};

		RAII<VkDebugReportCallbackEXT> _debugReportCallback{vkDestroyDebugReportCallbackEXT, _instance, _debugReportCallback, nullptr};

	public:
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugReportFlagsEXT flags,
			VkDebugReportObjectTypeEXT objType,
			uint64_t obj,
			size_t location,
			int32_t code,
			const char* layerPrefix,
			const char* msg,
			void* userData
		);
	}; // class VulkanContext

} // namespace kds

#endif // VulkanContext.hpp
