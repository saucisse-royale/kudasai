#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "RAII.hpp"
#include "VulkanLoader.hpp"

#include <vector>

namespace kds {

class VulkanContext;

class VulkanCommandManager {
public:
    explicit VulkanCommandManager(VulkanContext* vulkanContext) noexcept;
    ~VulkanCommandManager() noexcept;

    void draw() noexcept;

    void createSemaphore() noexcept;
    void createCommandBuffers() noexcept;
    void recordCommandBuffers() noexcept;

    VulkanContext* _vulkanContext{};

    // Command pools are tied to a specific queue family index
    RAII<VkCommandPool> _graphicsCommandPool;
    std::vector<VkCommandBuffer> _graphicsCommandBuffers{};

    RAII<VkSemaphore> _imageAvailableSemaphore;
    RAII<VkSemaphore> _renderFinishedSemaphore;
};

} // namespace kds
