#pragma once

#include <vector>

#include "RAII.hpp"
#include "VulkanLoader.hpp"

namespace kds {

	class VulkanContext;
	class VulkanSwapchain {
	public:
		explicit VulkanSwapchain(VulkanContext* VulkanContext) noexcept;
		void create() noexcept;
		void queryCapabilities() noexcept;

		void setImageCount() noexcept;
		void setImageCount(uint32_t imageCount) noexcept;

		VkSurfaceFormatKHR pickSurfaceFormat() noexcept;
		VkPresentModeKHR pickPresentMode() noexcept;

		void setSwapchainExtent(size_t width, size_t height) noexcept;

	private:
		VulkanContext* _vulkanContext{};

		VkSurfaceCapabilitiesKHR _capabilities;
		std::vector<VkSurfaceFormatKHR> _surfaceFormats;
		std::vector<VkPresentModeKHR> _presentModes;

		uint32_t _imageCount{};
		VkExtent2D _swapchainExtent{};

		RAII<VkSwapchainKHR> _swapchain;
		RAII<VkSwapchainKHR> _oldSwapchain;

	};

} // namespace kds
