#include "VulkanSwapchain.hpp"
#include "VulkanHelper.hpp"
#include "VulkanContext.hpp"

#include <algorithm>

namespace kds {

	VulkanSwapchain::VulkanSwapchain(VulkanContext* vulkanContext) noexcept :
		_vulkanContext{vulkanContext},
		_swapchain{vkDestroySwapchainKHR, _vulkanContext->_device, _swapchain, nullptr},
		_oldSwapchain{vkDestroySwapchainKHR, _vulkanContext->_device, _oldSwapchain, nullptr}
	{}

	void VulkanSwapchain::queryCapabilities() noexcept {
		auto& physicalDevice = _vulkanContext->_physicalDevice;
		auto& surface = _vulkanContext->_surface;
		auto result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &_capabilities);
		KDS_CHECK_RESULT(result, "Failed to get physical device surface capabilities\n");

		uint32_t surfaceFormatsCount{};
		result = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &surfaceFormatsCount, nullptr);
		KDS_CHECK_RESULT(result, "Failed to get physical device surface formats\n");

		_surfaceFormats.resize(surfaceFormatsCount);
		result = vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &surfaceFormatsCount, _surfaceFormats.data());
		KDS_CHECK_RESULT(result, "Failed to get physical device surface formats\n");

		uint32_t presentModesCount{};
		result = vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModesCount, nullptr);
		KDS_CHECK_RESULT(result, "Failed to get physical device surface present modes\n");

		_presentModes.resize(presentModesCount);
		result = vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModesCount, _presentModes.data());
		KDS_CHECK_RESULT(result, "Failed to get physical device surface present modes\n");
	}

	void VulkanSwapchain::setImageCount(uint32_t imageCount) noexcept {
		if (imageCount > _capabilities.maxImageCount) {
			std::cerr << "KDS ERROR: Tried to set swapchain image count higher than what is supported, default count is set...\n";
			setImageCount();
			return;
		} else if (imageCount < _capabilities.minImageCount) {
			std::cerr << "KDS ERROR: Tried to set swapchain image count lower than what is supported, default count is set...\n";
			setImageCount();
			return;
		}

		_imageCount = imageCount;
	}

	void VulkanSwapchain::setImageCount() noexcept {
		uint32_t imageCount{_capabilities.minImageCount + 1};
		if (_capabilities.maxImageCount > 0 && imageCount > _capabilities.maxImageCount) {
			imageCount = _capabilities.maxImageCount;
		}

		_imageCount = imageCount;
	}

	VkSurfaceFormatKHR VulkanSwapchain::pickSurfaceFormat() noexcept {
		if (_surfaceFormats.size() == 0) {
			std::cerr << "KDS FATAL: No surface formats found, try to query swapchain capabilities first\n";
			exit(1);
		}

		// Formats may be undefined, default initialize it then
		if (_surfaceFormats.size() == 1 && _surfaceFormats[0].format == VK_FORMAT_UNDEFINED) {
			return {VK_FORMAT_R8G8B8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
		}

		// Currently seeking only for R8G8B8A8 color space
		for (auto const& surfaceFormat : _surfaceFormats) {
			if (surfaceFormat.format == VK_FORMAT_R8G8B8A8_UNORM) {
				return surfaceFormat;
			}
		}

		// Default initialization if the requested format is not found
		return _surfaceFormats[0];
	}

	VkPresentModeKHR VulkanSwapchain::pickPresentMode() noexcept {
		if (_presentModes.size() == 0) {
			std::cerr << "KDS FATAL: No present modes found, try to query available present modes first\n";
			exit(1);
		}

		for (auto&& presentMode : _presentModes) {
			if (presentMode & VK_PRESENT_MODE_MAILBOX_KHR) {
				return presentMode;
			}
		}

		for (auto&& presentMode : _presentModes) {
			if (presentMode & VK_PRESENT_MODE_FIFO_KHR) {
				return presentMode;
			}
		}

		return _presentModes[0];;
	}

	void VulkanSwapchain::setSwapchainExtent(size_t width, size_t height) noexcept {
		size_t maxWidth{_capabilities.maxImageExtent.width}, minWidth{_capabilities.minImageExtent.width};
		size_t maxHeight{_capabilities.maxImageExtent.height}, minHeight{_capabilities.minImageExtent.height};

		// Resize the swapchain if the requested extend does not fit
		if (width > maxWidth) {
			width = maxWidth;
		} else if (width < minWidth) {
			width = minWidth;
		}

		if (height > maxHeight) {
			height = maxHeight;
		} else if (height < minHeight) {
			height = minHeight;
		}

		_swapchainExtent.width = width;
		_swapchainExtent.height = height;
	}

	void VulkanSwapchain::create() noexcept {
		queryCapabilities();
		setImageCount();
		setSwapchainExtent(_vulkanContext->_contextConfig.windowConfig.width, _vulkanContext->_contextConfig.windowConfig.height);


		auto& surface = _vulkanContext->_surface;

		auto& deviceQueueConfig = _vulkanContext->_contextConfig.deviceQueueConfig;
		std::vector<uint32_t> indices{};
		indices.push_back(deviceQueueConfig.graphicsQueueInfos.index);

		// We want only UNIQUE indices in the array
		if (std::find(indices.begin(), indices.end(), deviceQueueConfig.computeQueueInfos.index) == indices.end()) {
			indices.push_back(deviceQueueConfig.computeQueueInfos.index);
		}

		if (std::find(indices.begin(), indices.end(), deviceQueueConfig.transferQueueInfos.index) == indices.end()) {
			indices.push_back(deviceQueueConfig.transferQueueInfos.index);
		}

		if (std::find(indices.begin(), indices.end(), deviceQueueConfig.sparseBindingQueueInfos.index) == indices.end()) {
			indices.push_back(deviceQueueConfig.sparseBindingQueueInfos.index);
		}


		VkSwapchainCreateInfoKHR swapchainInfo{};
		swapchainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		swapchainInfo.surface = surface;
		swapchainInfo.minImageCount = _capabilities.minImageCount;

		auto surfaceFormat = pickSurfaceFormat();
		swapchainInfo.imageFormat = surfaceFormat.format;
		swapchainInfo.imageColorSpace = surfaceFormat.colorSpace;
		swapchainInfo.imageExtent = _swapchainExtent;
		swapchainInfo.imageArrayLayers = 1;
		swapchainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
		swapchainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		swapchainInfo.presentMode = pickPresentMode();
		swapchainInfo.clipped = VK_TRUE;
		swapchainInfo.oldSwapchain = _oldSwapchain;
		swapchainInfo.preTransform = _capabilities.currentTransform;

		if (indices.size() == 1) {
			swapchainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		} else {
			swapchainInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			swapchainInfo.queueFamilyIndexCount = indices.size();
			swapchainInfo.pQueueFamilyIndices = indices.data();
		}
		
		_oldSwapchain = _swapchain;
		auto result = vkCreateSwapchainKHR(_vulkanContext->_device, &swapchainInfo, nullptr, _swapchain.reset());
		KDS_CHECK_RESULT(result, "Failed to create a swapchain.");
	}

} // namespace kds
