#pragma once

#include "VulkanLoader.hpp"
#include "VulkanConfig.hpp"
#include "RAII.hpp"
#include "VulkanSwapchain.hpp"
#include "VulkanGraphicsPipeline.hpp"
#include "VulkanCommandManager.hpp"

#include <GLFW/glfw3.h>


#include <memory>


namespace kds {
	class VulkanContext {
	public:
		void create(ContextConfig contextConfig, GLFWwindow* window) noexcept;

		void _loadLayers() noexcept;
		void _loadExtensions() noexcept;
		void _initSurface(GLFWwindow* window) noexcept;
		void _initInstance() noexcept;
		void _queryPhysicalDevices() noexcept;
		void _initDevice() noexcept;
		void _initFramebuffer() noexcept;

		RAII<VULKAN_LIBRARY_TYPE> _vulkanLibrary{loader::terminate, _vulkanLibrary};

		VkPhysicalDevice _physicalDevice;
		VkPhysicalDeviceProperties _physicalDeviceProperties;

		ContextConfig _contextConfig;
		RAII<VkInstance> _instance{vkDestroyInstance, _instance, nullptr};

		RAII<VkDevice> _device{vkDestroyDevice, _device, nullptr};
		VkQueue _presentQueue{};
		std::vector<VkQueue> _graphicsQueues{};
		std::vector<VkQueue> _computeQueues{};
		std::vector<VkQueue> _transferQueues{};
		std::vector<VkQueue> _sparseBindingQueues{};

		RAII<VkSurfaceKHR> _surface{vkDestroySurfaceKHR, _instance, _surface, nullptr};

		VulkanSwapchain _vulkanSwapchain{this};
		std::vector<RAII<VkFramebuffer>> _framebuffers{};

		VulkanGraphicsPipeline _graphicsPipeline{this};

		VulkanCommandManager _commandManager{this};

		RAII<VkDebugReportCallbackEXT> _debugReportCallback{vkDestroyDebugReportCallbackEXT, _instance, _debugReportCallback, nullptr};

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
