#include "VulkanCommandManager.hpp"

#include "VulkanHelper.hpp"
#include "VulkanContext.hpp"

#include <limits>
#include <iostream>

namespace kds {
	VulkanCommandManager::VulkanCommandManager(VulkanContext* vulkanContext) noexcept :
		_vulkanContext{vulkanContext},
		_graphicsCommandPool{vkDestroyCommandPool, _vulkanContext->_device, _graphicsCommandPool, nullptr},
		_imageAvailableSemaphore{vkDestroySemaphore, _vulkanContext->_device, _imageAvailableSemaphore, nullptr},
		_renderFinishedSemaphore{vkDestroySemaphore, _vulkanContext->_device, _renderFinishedSemaphore, nullptr}
	{}

	VulkanCommandManager::~VulkanCommandManager() noexcept {
		vkFreeCommandBuffers(_vulkanContext->_device, _graphicsCommandPool, _graphicsCommandBuffers.size(), _graphicsCommandBuffers.data());
	}

	void VulkanCommandManager::draw() noexcept {
		// get next image from swapchain
		uint32_t imageIndex;
		auto result = vkAcquireNextImageKHR(_vulkanContext->_device, _vulkanContext->_vulkanSwapchain._swapchain, std::numeric_limits<uint64_t>::max(), _imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);
		KDS_CHECK_RESULT(result, "Failed to acquire next image from the swapchain.");

		std::array<VkSemaphore, 1> waitSemaphores{};
		waitSemaphores[0] = _imageAvailableSemaphore;

		std::array<VkSemaphore, 1> signalSemaphores{};
		signalSemaphores[0] = _renderFinishedSemaphore;

		std::array<VkPipelineStageFlags, 1> waitStages{};
		waitStages[0] = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;


		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.waitSemaphoreCount = waitSemaphores.size();
		submitInfo.pWaitSemaphores = waitSemaphores.data();
		submitInfo.signalSemaphoreCount = signalSemaphores.size();
		submitInfo.pSignalSemaphores = signalSemaphores.data();
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &_graphicsCommandBuffers[imageIndex];
		submitInfo.pWaitDstStageMask = waitStages.data();

		result = vkQueueSubmit(_vulkanContext->_graphicsQueues[0], 1, &submitInfo, VK_NULL_HANDLE);
		KDS_CHECK_RESULT(result, "Failed to submit buffer to a queue");
		
		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount = signalSemaphores.size();
		presentInfo.pWaitSemaphores = signalSemaphores.data();
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &_vulkanContext->_vulkanSwapchain._swapchain;
		presentInfo.pImageIndices = &imageIndex;

		result = vkQueuePresentKHR(_vulkanContext->_presentQueue, &presentInfo);
		KDS_CHECK_RESULT(result, "Failed to present queue");
	}

	void VulkanCommandManager::createSemaphore() noexcept {
		VkSemaphoreCreateInfo semaphoreInfo{};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		semaphoreInfo.flags = 0;

		auto result = vkCreateSemaphore(_vulkanContext->_device, &semaphoreInfo, nullptr, _imageAvailableSemaphore.reset());
		KDS_CHECK_RESULT(result, "Failed to create semaphores.");
		result = vkCreateSemaphore(_vulkanContext->_device, &semaphoreInfo, nullptr, _renderFinishedSemaphore.reset());
		KDS_CHECK_RESULT(result, "Failed to create semaphores.");
	}

	void VulkanCommandManager::createCommandBuffers() noexcept {
		VkCommandPoolCreateInfo graphicsCommandPoolInfo{};
		graphicsCommandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		graphicsCommandPoolInfo.flags = 0;
		graphicsCommandPoolInfo.queueFamilyIndex = _vulkanContext->_contextConfig.deviceQueueConfig.graphicsQueueInfos.index;

		auto result = vkCreateCommandPool(_vulkanContext->_device, &graphicsCommandPoolInfo, nullptr, _graphicsCommandPool.reset());
		KDS_CHECK_RESULT(result, "Failed to create a command pool.");

		_graphicsCommandBuffers.resize(_vulkanContext->_vulkanSwapchain._swapchainImageViews.size());

		VkCommandBufferAllocateInfo commandBufferInfo{};
		commandBufferInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		commandBufferInfo.commandPool = _graphicsCommandPool;
		commandBufferInfo.commandBufferCount = _graphicsCommandBuffers.size();
		commandBufferInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

		result = vkAllocateCommandBuffers(_vulkanContext->_device, &commandBufferInfo, _graphicsCommandBuffers.data());
		KDS_CHECK_RESULT(result, "Failed to allocater graphics command buffers.");
	}

	void VulkanCommandManager::recordCommandBuffers() noexcept {
		VkCommandBufferBeginInfo cmdBufferBeginInfo{};
		cmdBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		cmdBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

		VkImageSubresourceRange imageSubRessourceRange{};
		imageSubRessourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		imageSubRessourceRange.layerCount = 1;
		imageSubRessourceRange.baseArrayLayer = 0;
		imageSubRessourceRange.levelCount = 1;
		imageSubRessourceRange.baseMipLevel = 0;


		VkClearValue clearValue{0.3f, 0.2f, 0.6f, 0.0f};

		VkResult result{};
		for (size_t i{}; i < _graphicsCommandBuffers.size(); ++i) {
			result = vkBeginCommandBuffer(_graphicsCommandBuffers[i], &cmdBufferBeginInfo);
			KDS_CHECK_RESULT(result, "Failed to begin recording a command buffer.");

			VkRenderPassBeginInfo renderPassBeginInfo{};
			renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassBeginInfo.clearValueCount = 1;
			renderPassBeginInfo.pClearValues = &clearValue;
			renderPassBeginInfo.framebuffer = _vulkanContext->_framebuffers[i];
			renderPassBeginInfo.renderArea.offset = {0,0};
			renderPassBeginInfo.renderArea.extent =  _vulkanContext->_vulkanSwapchain._swapchainExtent;
			renderPassBeginInfo.renderPass = _vulkanContext->_graphicsPipeline._renderPass;

			vkCmdBeginRenderPass(_graphicsCommandBuffers[i], &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
			vkCmdBindPipeline(_graphicsCommandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, _vulkanContext->_graphicsPipeline._pipeline);
			vkCmdDraw(_graphicsCommandBuffers[i], 3, 1, 0, 0);
			vkCmdEndRenderPass(_graphicsCommandBuffers[i]);

			result = vkEndCommandBuffer(_graphicsCommandBuffers[i]);
			KDS_CHECK_RESULT(result, "Failed to end a graphics command buffer");
		}

	}

} // namespace kds
