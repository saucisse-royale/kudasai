#pragma once

#include <vector>

#include "RAII.hpp"
#include "VulkanLoader.hpp"

namespace kds {

	class VulkanContext;
	class VulkanSwapchain {
	public:
		explicit VulkanSwapchain(VulkanContext* VulkanContext) noexcept;
		void init() noexcept;
		void create() noexcept;
		void recreate() noexcept;
		void queryCapabilities() noexcept;

		void setImageCount() noexcept;
		void setImageCount(uint32_t imageCount) noexcept;

		VkSurfaceFormatKHR pickSurfaceFormat() noexcept;
		VkPresentModeKHR pickPresentMode() noexcept;

		void setSwapchainExtent(size_t width, size_t height) noexcept;

		void retrieveImages() noexcept;
		void createImageViews() noexcept;

	private:
		VulkanContext* _vulkanContext{};

		VkSurfaceCapabilitiesKHR _capabilities;
		std::vector<VkSurfaceFormatKHR> _surfaceFormats;
		std::vector<VkPresentModeKHR> _presentModes;

		uint32_t _imageCount{};
		VkExtent2D _swapchainExtent{};

		RAII<VkSwapchainKHR> _swapchain;
		std::vector<VkImage> _swapchainImages{};
		std::vector<RAII<VkImageView>> _swapchainImageViews{};
	};

} // namespace kds
